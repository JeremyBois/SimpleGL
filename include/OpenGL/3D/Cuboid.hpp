#ifndef __CUBOID__HPP
#define __CUBOID__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape3D.hpp"

#include "OpenGL/Texture.hpp"


namespace simpleGL
{
    // Can be used to construct and draw a triangle
    class SIMPLEGL_API Cuboid: public Shape3D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        static const int m_sizeData = 216;
        static const int m_sizeVertices = 24;
        static const int m_sizePos = 3;
        static const int m_sizeColor = 4;
        static const int m_sizeUV = 2;

        float m_vertices[m_sizeData];

        void SendData();

    public:
        Cuboid();
        virtual ~Cuboid();

        void Create(float _width, float _height, float _depth);

        virtual void Draw();
    };
}
#endif
