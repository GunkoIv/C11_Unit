#ifndef GUN_TEST_STRUCTURES_H_
#define GUN_TEST_STRUCTURES_H_

#include <string>
#include <memory>
#include <list>
#include <deque>
#include <set>
#include <cstring>
#include "../utils/profiler.h"

#define UNUSED_VAR(expr) { (void)(expr); } 
#define CODE_INFO gun::test::CodeInfo{__FILE__, __LINE__}

namespace gun { namespace test {

        struct Mock {};

        using c_char_ar = const char * const;

        struct CodeInfo {
            c_char_ar file;
            const u_int line;
            // CodeInfo() = default;
            // CodeInfo(CodeInfo &&) = default;
            // CodeInfo(u_int line, const char * const file) 
            //     : assertCodeLine(line)
            //     , assertCodeFile(file)
            // {}
            void printTo(std::ostream &out, bool useShortFileName = true) {
                out << "File: ";
                if (useShortFileName) {
                    c_char_ar partFileName = std::strrchr(file, '/');
                    c_char_ar printName = (partFileName != nullptr) ? (partFileName + 1) : (file);
                    out << printName;
                } else {
                    out << file;
                }
                out << ':' << line;
            }
        };

        template<typename T>
        using Container = std::deque<T>;
        
        using u_int = unsigned int;

        template<typename T>
        using OrderContainer = std::set<T>;

        template<typename T>
        using Unique = std::unique_ptr<T>;


        struct Default {
            static constexpr unsigned int defaultOrderNumber = 100;
        };


        struct SuiteInfo {
            SuiteInfo() = default;

            SuiteInfo(const std::string& name)
                : name(name)
            {}

            SuiteInfo(const std::string& name, unsigned int orderNumber)
                : name(name), order_num(orderNumber)
            {}

            const std::string name = "";
            const unsigned int order_num = Default::defaultOrderNumber + 1;
        };

        struct pass {
            template<typename ...Args>
            pass(Args&& ...args) {}
        };

        template<typename ClassToSetup>
        class SetupWrapper : public ClassToSetup {
        public:
            template<typename ...Args>
            SetupWrapper(Args&& ...args)
                : ClassToSetup(std::forward<Args>(args)...)
            {
                this->setup();
            }
            ~SetupWrapper(){
                this->teardown();
            }
        };

} } //namespace test and gun

#endif //GUN_TEST_STRUCTURES_H_
