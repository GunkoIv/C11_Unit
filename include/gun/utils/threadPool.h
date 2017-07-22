#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <string>
#include <future>
#include <deque>
#include <queue>

#include "logger.h"
#include "profiler.h"

namespace sml {

    class ThreadPool {
        
    struct Deferred_t {};

    public:

        ThreadPool(Deferred_t)
            : maxThreads_(0) 
            , numberOfLaunchedThreads_(0)
            , launchedCalculation_{}
            , waitingCalculation_{}
        {}

        static constexpr Deferred_t Deferred{};

        ThreadPool(int maxThreads = 1)
            : maxThreads_((maxThreads > 0) ? (maxThreads) : (std::thread::hardware_concurrency()))
            , numberOfLaunchedThreads_(0)
            , launchedCalculation_{}
            , waitingCalculation_{}
        {}

        ~ThreadPool() {
            waitAllTask();
        }
        
        using Task = std::function<void()>; 

        void addTask(Task&& task) {
            LOGOUT_DEBUG("Start add task in ThreadPool!");
            if (launchedCalculation_.size() < maxThreads_) {
                LOGOUT_DEBUG(ToString("We can add task because pool size: ", launchedCalculation_.size()));
                launchedCalculation_.emplace_back(std::async(std::launch::async, std::move(task)));
                LOGOUT_DEBUG(ToString("We launch task"));
                launchedCalculation_.back().wait_for(std::chrono::nanoseconds(0)); // launch calculation
                LOGOUT_DEBUG(ToString("We wait a bit launched task"));
            } else {
                LOGOUT_DEBUG(ToString("We can NOT!!! add task because pool size: ", launchedCalculation_.size()));
                waitingCalculation_.emplace(std::move(task));
            }
        }

        void waitAllTask(unsigned int timeWaitOneTaskMs = 1) {
            while (!waitingCalculation_.empty()) {
                if (maxThreads_ < 1) {
                    auto &task = waitingCalculation_.front();
                    task();
                    waitingCalculation_.pop();
                } else if (launchedCalculation_.size() < maxThreads_) {
                    auto &task = waitingCalculation_.front();
                    launchedCalculation_.emplace_back(std::async(std::launch::async, std::move(task)));
                    waitingCalculation_.pop();
                } else {
                    for (auto oneTask = std::begin(launchedCalculation_); oneTask != std::end(launchedCalculation_); ++oneTask) {
                        const auto status = oneTask->wait_for(std::chrono::milliseconds(timeWaitOneTaskMs));
                        if (status == std::future_status::ready) {
                            oneTask->get();
                            launchedCalculation_.erase(oneTask);
                            break;
                        }
                    }
                }
            }
            for (auto &process : launchedCalculation_) {
                if (process.valid()) {
                    process.get();
                }
            }
        }

    private:

        unsigned int maxThreads_;
        int numberOfLaunchedThreads_;
        std::deque<std::future<void>> launchedCalculation_;
        std::queue<std::packaged_task<void()>> waitingCalculation_;
    };

    void test();

} //namespace sml

#endif //THREAD_POOL_H_
