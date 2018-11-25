#ifndef __STREAMUTILITY__HPP
#define __STREAMUTILITY__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{
    /// Collection of function to manipulate stream and files.
    class SIMPLEGL_LOCAL StreamUtility
    {
    private:
        StreamUtility();

    public:
        StreamUtility(StreamUtility const&) = delete;   // C++ 11
        void operator=(StreamUtility const&) = delete;  // C++ 11

        static std::string ReadFile(const std::string& _path);
    };
}
#endif
