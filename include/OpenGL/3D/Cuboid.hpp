#ifndef __CUBOID__HPP
#define __CUBOID__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape3D.hpp"


namespace simpleGL
{
    /// Represent a cuboid drawn using triangle strips.
    /// Draws a series of triangles (three-sided polygons) using vertices
    /// v0, v1, v2, then v2, v1, v3 (note the order), then v2, v3, v4, and so on.
    class SIMPLEGL_API Cuboid: public Shape3D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        static const int SizeVertices = 24;

        Vertex3D m_verticesData[SizeVertices];

        void SendData();

    public:
        Cuboid();
        virtual ~Cuboid();

        void Create(float _width, float _height, float _depth);
        void SetUV(const glm::vec2 _uvMap[SizeVertices]);

        virtual void Draw();
    };
}
#endif
