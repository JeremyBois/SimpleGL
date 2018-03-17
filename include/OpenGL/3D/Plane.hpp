#ifndef __PLANE__HPP
#define __PLANE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape3D.hpp"

#include "OpenGL/Texture.hpp"


namespace simpleGL
{
    // Can be used to construct and draw a triangle
    class SIMPLEGL_API Plane: public Shape3D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        // Index buffer object (EBO)
        unsigned int m_VAO, m_VBO, m_EBO;

        int m_sizeData;
        int m_sizeIndex;
        int m_sizeVertices;
        static const int m_sizePos = 3;
        // static const int m_sizeColor = 4;
        // static const int m_sizeUV = 2;

        float*        m_pVerticesData;
        unsigned int* m_pIndices;

        void  SendData();
        void  ComputeDataSize(int _nbCols, int _nbRows);
        void  ComputeIndexSize(int _nbCols, int _nbRows);

        void  DebugVertices();
        void  DebugIndex();

    public:
        Plane();
        virtual ~Plane();

        void Create(float _width, float _height, int _nbCols, int _nbRows);

        virtual void Draw();
    };
}
#endif
