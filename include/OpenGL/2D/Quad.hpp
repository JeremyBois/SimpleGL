#ifndef __QUAD__HPP
#define __QUAD__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape2D.hpp"


namespace simpleGL
{
    /// Represent a 2D Quad drawn with triangle fan (describes a set of connected
    /// triangles that share one central vertex).
    class SIMPLEGL_API Quad: public Shape2D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        static const int SizeVertices = 4;

        Vertex2D m_verticesData[SizeVertices];

        void SendData();

    public:
        Quad();
        virtual ~Quad();

        void Create(float _width, float _height, glm::vec4 _colors[SizeVertices]);
        void Create(float _width, float _height);

        virtual void Draw(Component *_pcomp);
    };
}
#endif
