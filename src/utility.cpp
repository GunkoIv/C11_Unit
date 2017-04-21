
#include "logger.h"
#include "utility.h"

namespace sml {

        namespace {

            class CustomBytesFieldValuePrinter
                : public google::protobuf::TextFormat::FieldValuePrinter
            {
            public:

                virtual google::protobuf::string PrintBytes(const google::protobuf::string &val) const {
                    std::string stringSize = std::to_string(val.size());
                    return google::protobuf::string("data isn't displayed. size of data - " + stringSize + " bytes");
                }
            };

        } //unname namespace

        std::string protoMessageToString(const google::protobuf::Message &message) {
            message.CheckInitialized();
            std::string stringMessage;
            google::protobuf::TextFormat::Printer printer;
            printer.SetDefaultFieldValuePrinter(new CustomBytesFieldValuePrinter());
            printer.PrintToString(message, &stringMessage);
            return stringMessage;
        }

        std::string split(const std::vector<std::string> &container, const std::string &delimiter) {
            std::string result{};
            bool isFirst = true;
            for(const auto &argument : container) {
                (isFirst) ? (isFirst=false, result) : (result += delimiter);
                result += argument;
            }
            return result;
        }

        
        void printTimer(Timer &timer) {
            LOGOUT_DEBUG(ToString("Timer stop! Name: '", timer.getTags()[0], "'; Micro: ", timer.getDuration()));    
        }

} //namespace sml
