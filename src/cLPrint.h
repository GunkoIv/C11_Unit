// Кодировка utf-8.
#ifndef CLColor_H_
#define CLColor_H_

#include "toString.h"

    enum class CLColor { 
        RED        = 31,
        GREEN      = 32,
        YELLOW     = 33,
        LIGHT_CYAN = 96,
        DEFAULT    = 39,
    };
    
    template<CLColor colorCode = CLColor::DEFAULT>
    class CLPrint {
    public:

        template<class ... Args> 
        CLPrint(Args&& ...args)
            : m_str(std::forward<Args>(args)...) 
        {}

        std::ostream & printTo(std::ostream &streamOut) {
            return streamOut << "\033[" << static_cast<int>(colorCode) << "m"
                << m_str << "\033[0m"
            ;
        }

    private:
        ToString m_str;
    };

    template<CLColor ColorCode>
    std::ostream &operator<<(std::ostream &os, CLPrint<ColorCode> &&colorPrinter) { 
        return colorPrinter.printTo(os);
    }

#endif //CLColor_H_
