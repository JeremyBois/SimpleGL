#include "OpenGL/Triangle.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    // 3 * (m_sizeVertices + m_sizeColor)
    // const int Triangle::m_sizeData = 18;
    // const int Triangle::m_sizeVertices = 3;
    // const int Triangle::m_sizeColor = 3;

    Triangle::Triangle()
    {
        // glGenVertexArrays(1, &m_VAO);
        // glGenBuffers(1, &m_VBO);
    }

    void Triangle::Create()
    {
        float temp[] =
        {
            // Position        Color
            0.4f, 0.4f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.4f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.8f, 0.4f, 0.0f,  0.0f, 0.0f, 1.0f
        };

        for (int i = 0; i < m_sizeVertices; ++i)
        {
            m_vertices[i] = temp[i];
        }

        ToGPU();
    }

    void Triangle::ToGPU()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

        // Send position (offset take account of color)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Send color using same offset but using a starting offset of sizeof(position)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // // Send position (offset take account of color)
        // glVertexAttribPointer(0, m_sizeVertices, GL_FLOAT, GL_FALSE,
        //                       (m_sizeVertices + m_sizeColor) * sizeof(float),
        //                       (void*)0);
        // glEnableVertexAttribArray(0);
        // // Send color using same offset but using a starting offset to discard position
        // glVertexAttribPointer(1, m_sizeColor, GL_FLOAT, GL_FALSE,
        //                      (m_sizeVertices + m_sizeColor) * sizeof(float),
        //                      (void*)(m_sizeVertices * sizeof(float)));
        // glEnableVertexAttribArray(1);
    }

    void Triangle::Draw()
    {
        // Select shader program for the draw call
        m_pShader->Use();
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    Triangle::~Triangle()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }
}
