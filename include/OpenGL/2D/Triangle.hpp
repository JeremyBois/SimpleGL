#ifndef __TRIANGLE__HPP
#define __TRIANGLE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape2D.hpp"


namespace simpleGL
{
    // Represent a triangle
    class SIMPLEGL_API Triangle: public Shape2D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        static const int SizeVertices = 3;

        Vertex2D m_verticesData[SizeVertices];

        void SendData();

    public:
        Triangle();
        virtual ~Triangle();

        void Create(glm::vec3 _pos[SizeVertices], glm::vec4 _colors[SizeVertices]);
        void Create(glm::vec3 _pos[SizeVertices]);

        void Create(float _base, float _height);
        void Create(float _base, float _height, glm::vec4 _colors[SizeVertices]);

        virtual void Draw(Component *_pcomp);
    };
}
#endif
