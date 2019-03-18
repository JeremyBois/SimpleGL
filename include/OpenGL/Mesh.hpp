#ifndef __MESH__HPP
#define __MESH__HPP

#include "simpleGL_macro.hpp" // Needed for macro definition
#include "Shape.hpp"

#include "glm.hpp"

namespace simpleGL
{
    class Material;


    /// A mesh is a buffer of vertex with a position, a color, an UV coordinate, and a normal value
    class SIMPLEGL_API Mesh : public Shape
    {
    public:
        static const int SizeNormals = 3;

        struct VertexMesh
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 UV;
            glm::vec3 Normals;
        };

    private:
        // Vertex array buffer (VAO)
        // Vertex buffer object (VBO)
        // Index buffer object (EBO)
        unsigned int m_VAO, m_VBO, m_EBO;

        std::vector<VertexMesh>   m_verticesData;
        std::vector<unsigned int> m_indices;

    private:
        void SendData();
        void SetupBuffers();


    public:
        Mesh();
        virtual ~Mesh();
        virtual void Draw(Component *_pcomp);

        // Populate mesh with data
        void         Create(std::vector<VertexMesh> &_vertices, std::vector<unsigned int> &_indices);
    };

} // namespace simpleGL

#endif
