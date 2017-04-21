#include <string>
#include <chrono>
#include "profiler.h"

void realdprintf(const char *fullFileName, int lineInFile, const std::string &str) {
    const char *partFileName = std::strrchr(fullFileName, '/');
    const char *fileName = (partFileName != nullptr) ? (partFileName + 1) : (fullFileName);
    std::cerr << "\nFile: " << fileName << ":" << lineInFile << ": " << str << std::endl;
}