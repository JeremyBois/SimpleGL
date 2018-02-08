#ifndef __Tools__HPP
#define __Tools__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{
    // Collection of function to manipulate stream and files.
    class SIMPLEGL_LOCAL Tools
    {
    private:
        Tools();

    public:
        Tools(Tools const&) = delete;           // C++ 11
        void operator=(Tools const&) = delete;  // C++ 11

        template<typename T> static void SafeDelete(T*& a) {delete a; a = nullptr;};
    };


    struct SIMPLEGL_API GL_COLOR3
    {
        GLfloat r, g, b;
        static int _nbElements;
    };

    struct SIMPLEGL_API GL_COLOR4
    {
        GLfloat r, g, b, a;
        static int _nbElements;
    };

    struct SIMPLEGL_API GL_POS3
    {
        GLfloat x, y, z;
        static int _nbElements;
    };

    struct SIMPLEGL_API GL_UV2
    {
        GLfloat tu, tv;
        static int _nbElements;
    };
}
#endif
