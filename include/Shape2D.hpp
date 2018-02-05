#ifndef __SHAPE2D__HPP
#define __SHAPE2D__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape.hpp"


namespace simpleGL
{
    // Abstract class for any 2D shapes
    class SIMPLEGL_LOCAL Shape2D: public Shape
    {
    public:
        Shape2D();
        virtual ~Shape2D();
    };
}
#endif
