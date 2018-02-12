#ifndef __SHAPE3D__HPP
#define __SHAPE3D__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape.hpp"

#include "glm.hpp"


namespace simpleGL
{
    // Abstract class for any 3D shapes
    class SIMPLEGL_LOCAL Shape3D: public Shape
    {
        virtual void ConstructModelMatrix();

    public:
        Shape3D();
        virtual ~Shape3D();

        virtual void Draw();
    };
}
#endif
