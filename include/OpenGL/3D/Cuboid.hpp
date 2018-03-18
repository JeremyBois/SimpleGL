#ifndef __CUBOID__HPP
#define __CUBOID__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape3D.hpp"


namespace simpleGL
{
    // Can be used to construct and draw a triangle
    class SIMPLEGL_API Cuboid: public Shape3D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        // Total size of the buffer
        static const int SizeData = 288;
        static const int SizeVertices = 24;

        float m_verticesData[SizeData];

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
