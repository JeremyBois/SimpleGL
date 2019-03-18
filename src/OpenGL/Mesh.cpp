#include "OpenGL/Mesh.hpp"


namespace simpleGL
{

    Mesh::Mesh()
    {
        SetupBuffers();
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::SetupBuffers()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    }

    void Mesh::SendData()
    {
        // @NOTE offsetof used because a struct has the same memory layout as ana array

        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_verticesData.size() * sizeof(VertexMesh), &m_verticesData[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, SizePos, GL_FLOAT, GL_FALSE,
                              sizeof(VertexMesh),
                              (void *)0);
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(1, SizeColor, GL_FLOAT, GL_FALSE,
                              sizeof(VertexMesh),
                              (void *)(offsetof(VertexMesh, Color)));
        glEnableVertexAttribArray(1);

        // UV
        glVertexAttribPointer(2, SizeUV, GL_FLOAT, GL_FALSE,
                              sizeof(VertexMesh),
                              (void *)(offsetof(VertexMesh, UV)));
        glEnableVertexAttribArray(2);

        // Normals
        glVertexAttribPointer(3, SizeNormals, GL_FLOAT, GL_FALSE,
                              sizeof(VertexMesh),
                              (void *)(offsetof(VertexMesh, Normals)));
        glEnableVertexAttribArray(3);


        // Avoid side effects
        glBindVertexArray(0);
    }

    void Mesh::Create(std::vector<VertexMesh> &_vertices, std::vector<unsigned int> &_indices)
    {
        m_verticesData = _vertices;
        m_indices = _indices;

        SendData();
    }

    void Mesh::Draw(Component *_pcomp)
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);


        // Avoid side effects
        glBindVertexArray(0);
    }

}
