#ifndef __PLANE__HPP
#define __PLANE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape3D.hpp"

namespace simpleGL
{
    // Represent a 3D plane constructed with an indexed triangle strip representation
    /// for memory efficiency and require only one draw call thanks to degenerated
    /// triangles.
    class SIMPLEGL_API Plane: public Shape3D
    {
    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        // Index buffer object (EBO)
        unsigned int m_VAO, m_VBO, m_EBO;

        int m_sizeVertices;
        int m_sizeIndex;
        int m_nbRows, m_nbCols;

        Vertex3D*     m_pVerticesData;
        unsigned int* m_pIndices;

        void  SendData();
        void  ComputeVerticesSize(int _nbCols, int _nbRows);
        void  ComputeIndexSize(int _nbCols, int _nbRows);
        void  ComputeNormals();

        void  DebugVerticesPos();
        void  DebugVerticesNormals();
        void  DebugIndex();

    public:
        Plane();
        virtual ~Plane();

        void Create(float _width, float _height, int _nbCols, int _nbRows, float _maxHeight=0.0f);
        void SetClampedUV();
        void SetUnclampedUV();

        virtual void Draw(Component *_pcomp);
    };
}
#endif
