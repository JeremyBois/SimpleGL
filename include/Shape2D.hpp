#ifndef __SHAPE2D__HPP
#define __SHAPE2D__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape.hpp"

#include "glm.hpp"

namespace simpleGL
{
    // Abstract class for any 2D shapes
    class SIMPLEGL_LOCAL Shape2D: public Shape
    {
    public:
        static const int SizeVerticeData = 9;

        struct Vertex2D
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 UV;
        };


        Shape2D() = default;
        virtual ~Shape2D() = default;
    };
}
#endif
