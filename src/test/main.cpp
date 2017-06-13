// Кодировка utf-8.

#include "executor.h"

int main(int argc, char** argv) {
    TRACE_PRINT("Programm first step!!!");
    auto programExitCode = TESTS_EXECUTE();
    TRACE_VAR(programExitCode);
    return programExitCode;
}
