#ifndef __SIMPLEGLMACRO__HPP
#define __SIMPLEGLMACRO__HPP

// More at
// https://cmake.org/Wiki/BuildingWinDLL
// https://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
    // Microsoft
    #define SIMPLEGL_HELPER_DLL_IMPORT __declspec(dllimport)
    #define SIMPLEGL_HELPER_DLL_EXPORT __declspec(dllexport)
    #define SIMPLEGL_HELPER_DLL_LOCAL
#else
    #if __GNUC__ >= 4
        // Linux
        #define SIMPLEGL_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define SIMPLEGL_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        #define SIMPLEGL_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        // GCC does not support __attribute__ before version 4.
        #define SIMPLEGL_HELPER_DLL_IMPORT
        #define SIMPLEGL_HELPER_DLL_EXPORT
        #define SIMPLEGL_HELPER_DLL_LOCAL
    #endif
#endif

// Now we use the generic helper definitions above to define SIMPLEGL_API and SIMPLEGL_LOCAL.
// SIMPLEGL_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// SIMPLEGL_LOCAL is used for non-api symbols.
#ifdef SIMPLEGL_SHARED              // Defined if SIMPLEGL is compiled as a DLL
    #ifdef SIMPLEGL_SHARED_EXPORTS  // Defined if we are building the SIMPLEGL DLL (instead of using it)
        #define SIMPLEGL_API SIMPLEGL_HELPER_DLL_EXPORT
    #else
        #define SIMPLEGL_API SIMPLEGL_HELPER_DLL_IMPORT
    #endif // SIMPLEGL_SHARED_EXPORTS
    #define SIMPLEGL_LOCAL SIMPLEGL_HELPER_DLL_LOCAL
#else  // SIMPLEGL_SHARED is not defined: this means SIMPLEGL is a STATIC lib.
    #define SIMPLEGL_API
    #define SIMPLEGL_LOCAL
#endif // SIMPLEGL_SHARED

// STL
#include <string>
#include <iostream>
#include <map>

// Open GL
// Add Glad first
#include <glad/glad.h>
// Include open Gl under the hood
// Also include window.h if on windows
#include <GLFW/glfw3.h>


using std::cout;
using std::endl;

#endif
