// Кодировка utf-8.
#include "threadPool.h"
#include "profiler.h"
#include <chrono>
#include <vector>

namespace sml {

    void test() {
        int baby =1;
        std::vector<int> vec(100,10);
        ThreadPool threadPool(2);
        PROF_CERR("Started Values: ", baby, " ", vec); 
        while (baby < 6) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            auto &&task = ThreadPool::Task(
                [baby, &vec] () 
                {
                    PROF_CERR("Form start thread: ", baby); 
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    PROF_CERR("Form end thread: ", baby, " last vector elem:", vec.back()); 
                }
            );
            threadPool.addTask(std::move(task));
            ++baby;
        }        
    }

} //namespace sml
