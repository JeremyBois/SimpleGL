#ifndef __TRIANGLE__HPP
#define __TRIANGLE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape2D.hpp"


namespace simpleGL
{
    // Can be used to construct and draw a triangle
    class SIMPLEGL_API Triangle: public Shape2D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        unsigned int m_VAO, m_VBO;

        static const int m_sizeData = 18;
        static const int m_sizeVertices = 3;
        static const int m_sizePos = 3;
        static const int m_sizeColor = 3;

        float m_vertices[m_sizeData];

        void SendData();

    public:
        Triangle();
        ~Triangle();

        void Create(float _pos[3], float _colors[3]);
        void Create(float _pos[3]);
        virtual void Draw();
        virtual void Init() {};
        virtual void Update(){};
        virtual void Quit(){};
        virtual GameObject* Clone() {return new Triangle();}
    };
}
#endif
