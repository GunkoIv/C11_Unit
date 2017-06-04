#ifndef PROFILER_H_
#define PROFILER_H_

#ifdef TRACING
#include "toString.h"

void tracePrint(const char *fullFileName, int lineInFile, ToString &&str);
#define TRACE_PRINT(...) tracePrint(__FILE__, __LINE__, ToString(__VA_ARGS__))
#define TRACE_VAR(var) TRACE_PRINT(#var, ":\"" ,var, "\"")

#define TRACE_SEG_FAULT()  { int *pointer = NULL; *pointer = 42; }

#else // ifndef TRACING

#define TRACE_PRINT(...) {}
#define TRACE_SEG_FAULT()  {}
#define TRACE_VAR(var) {}

#endif //TRACING

#endif //PROFILER_H_
