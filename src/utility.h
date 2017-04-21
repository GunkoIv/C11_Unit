// Кодировка utf-8.
#ifndef UTILITY_H_
#define UTILITY_H_

#include "logger.h"
#include <string>
#include <google/protobuf/text_format.h>
#include "profiler.h"
#include <chrono>

namespace sml {

    std::string protoMessageToString(const google::protobuf::Message &message);

    std::string split(const std::vector<std::string> &container, const std::string &delimiter);
    
    template<typename ...Args>
    std::string split(const std::string &delimiter, Args&& ...args) {
        const std::vector<std::string> vectorOfInputtingStrings{args...};
        return split(vectorOfInputtingStrings, delimiter);
    }

    class Timer {
    protected:

        using InnerTags = std::vector<std::string>;

        Timer(std::function<void(Timer& timer)> callback) 
            : start_()
            , end_()
            , endCallback_(callback)
            , tags_{}
            , isTimerEnd_(false)
        {}

        std::chrono::time_point<std::chrono::system_clock> start_;
        std::chrono::time_point<std::chrono::system_clock> end_;
        const std::function<void(Timer& timer)> endCallback_;
        InnerTags tags_;
        bool isTimerEnd_;

    public:
        
        using EndCallback = std::function<void(Timer& timer)>;

        Timer(const std::string &tag, EndCallback callback = nullptr) 
            : start_(std::chrono::system_clock::now())
            , end_()
            , endCallback_(callback)
            , tags_{tag}
            , isTimerEnd_(false)
        {}

        Timer(std::initializer_list<std::string> &tags, EndCallback callback = nullptr) 
            : start_(std::chrono::system_clock::now())
            , end_()
            , endCallback_(callback)
            , tags_(tags)
            , isTimerEnd_(false)
        {}
        
        void stop() {
            if(isTimerEnd_ != true) {
                end_ = std::chrono::system_clock::now();
                isTimerEnd_ = true;
                endCallback_(*this);
            }
        }
        
        template<typename Result = std::chrono::microseconds>
        auto getDuration() const -> decltype(std::chrono::duration_cast<Result>(end_-start_).count()) {
            if(isTimerEnd_ == true) {
                return std::chrono::duration_cast<Result>(end_-start_).count();
            } else {
                throw std::logic_error("Invalid using of class 'Timer'! Call getDuration() before got stopped measuring.");
            }
        }

        const InnerTags& getTags() const {
            return tags_;
        }
        
        ~Timer() {
            stop();
        }

    };


    class Statistic {

        void saveTimersValue(Timer& timer) { //timer.getDuration<std::chrono::nanoseconds>()
            // PROF_CERR("Timer ", timer.getTags(), " microseconds: ", timer.getDuration());
            if (isOnStatistics_) {
                int duration = static_cast<int>(timer.getDuration<>());
                for(const auto &tag : timer.getTags()) {
                   map_.insert(std::make_pair(tag, duration));
                }
            }
        }

        struct OneElementStatistic {
            float mean = 0;
            int max = 0;
            int min = 0;
            int last = 0;
        };
        const int isOnStatistics_;
        std::multimap<std::string, int> map_;


    public:

        Statistic(bool isOnStatistics)
            : isOnStatistics_(isOnStatistics)
            , map_{}
        {}

        std::map<std::string, float> getStatistics() const {
            std::map<std::string, float> result{};
            if (map_.size() > 0) {
                auto it = map_.begin();
                // int count = 1;
                long int sum = it->second;
                for (auto prevIt = it++; it != map_.end(); ++it, ++prevIt) {
                    if(it->first == prevIt->first) {
                        // count++;
                        sum += it->second;
                    } else {
                        result.insert(std::make_pair(prevIt->first, sum));//, sum / count));
                        // count = 1;
                        sum = it->second;
                    }
                }
                result.insert(std::make_pair((--it)->first, sum));//, sum / count));
            }
            return result;
        }
        
        bool empty() const {
            return map_.empty();
        }

        void clear() {
            map_.clear();
        }

        Timer::EndCallback timerEndHandler() {
            return [this](Timer& timer){this->saveTimersValue(timer);};
        }
    };

    class DeferredTimer: public Timer {
    public:

        DeferredTimer(Statistic &statistics) 
            : Timer(statistics.timerEndHandler())
            , isStarted_(false)
        {}

        void stop() {
            if(isTimerEnd_ != true) {
                end_ = std::chrono::system_clock::now();
                isTimerEnd_ = true;
            }
        }

        void start(std::initializer_list<std::string> &tags) {
            if (!isStarted_) {
                tags_ = tags;
                start_ = std::chrono::system_clock::now();
                isStarted_ = true;
            }
        }

        void start(const std::string &tag) {
            if (!isStarted_) {
                tags_ = {tag};
                start_ = std::chrono::system_clock::now();
                isStarted_ = true;
            }
        }

        ~DeferredTimer() {
            stop();
            if (isStarted_) {
                endCallback_(*this);
            }
        }

    private:

        bool isStarted_;
    };

    class TimerForStatistic: public Timer {
    public:

        TimerForStatistic(const std::string &tag, Statistic &statistics) 
            : Timer(tag, statistics.timerEndHandler())
        {}
        TimerForStatistic(std::initializer_list<std::string> &tags, Statistic &statistics) 
            : Timer(tags, statistics.timerEndHandler())
        {}
    };


    void printTimer(Timer &timer);

    #ifdef TRACING
    
    #define PROF_START_TIMER(timerName) Timer timerName( #timerName , printTimer)
    #define PROF_STOP_TIMER(timerName) timerName.stop()

    #else // ifndef TRACING

    #define PROF_START_TIMER(...) {}
    #define PROF_STOP_TIMER(...)  {}

    #endif //TRACING

} //namespace sml

#endif //UTILITY_H_
