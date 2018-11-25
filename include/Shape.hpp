#ifndef __SHAPE__HPP
#define __SHAPE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

namespace simpleGL
{
    /// Abstract class for any shape
    class SIMPLEGL_API Shape: public GameObject
    {
    public:
        static const int SizePos = 3;
        static const int SizeColor = 4;
        static const int SizeUV = 2;


        Shape() = default;
        virtual ~Shape() = default;

        virtual void Draw() = 0;
    };
}
#endif
