#pragma once
#define TS_ENABLE_ASSERTS
#ifdef TS_ENABLE_ASSERTS
#define JPH_ENABLE_ASSERTS
#endif

#ifdef TS_SUPPRESS_WARNINGS
#define JPH_SUPPRESS_WARNINGS
#endif
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <cstdarg>
#include <thread>

// Disable cmmon warnings triggered by Jolt, you can use JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the warning state

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.

namespace Techstorm {
}
