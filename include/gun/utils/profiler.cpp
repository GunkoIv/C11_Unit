#include <string>
#include <chrono>
#include "profiler.h"

#ifdef TRACING

void tracePrint(const char *fullFileName, int lineInFile, ToString &&str) {
    const char *partFileName = std::strrchr(fullFileName, '/');
    const char *fileName = (partFileName != nullptr) ? (partFileName + 1) : (fullFileName);
    std::cerr << "File: " << fileName << ":" << lineInFile << ": " << str << std::endl;
}

#else // ifndef TRACING

#endif //TRACING