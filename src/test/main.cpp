#include "gun/test/test.h"

int main(int argc, char** argv) {
    const auto settings = TESTS_CL_PARSE(argc, argv);
    TRACE_PRINT("Programm first step!!!");
    auto programExitCode = TESTS_EXECUTE(settings);
    TRACE_VAR(programExitCode);
    return programExitCode;
    //NOTE: short good working version
    // return TESTS_EXECUTE(TESTS_CL_PARSE(argc, argv));
}
