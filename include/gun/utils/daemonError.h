#ifndef DAEMON_ERROR_H_
#define DAEMON_ERROR_H_

#include <string>
#include <exception>

namespace sml {

        #ifdef check
        #error check macro defined not only in daemonError.h
        #endif

        #define check(expression,error_to_throw) { if (!(expression)) { throw error_to_throw; } }

        class DaemonError {
        public:
            int code;
            std::string status;
            std::string message;

            DaemonError(const int code, const std::string &status, const std::string &message)
                : code(code)
                , status(status)
                , message(message)
            {}

            static DaemonError BAD_REQUEST(const std::string& message) {
                return DaemonError(400, "BAD_REQUEST", message);
            }

            static DaemonError INTERNAL_SERVER_ERROR(const std::string& message) {
                return DaemonError(500, "INTERNAL_SERVER_ERROR", message);
            }
        }; 

} //namespace sml

#endif //DAEMON_ERROR_H_
