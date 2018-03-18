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
    public:
        static const int SizeNormals = 3;
        static const int SizeVerticeData = 12;

        struct Vertex3D
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 UV;
            glm::vec3 Normals;
        };

        Shape3D() = default;
        virtual ~Shape3D() = default;
    };
}
#endif
