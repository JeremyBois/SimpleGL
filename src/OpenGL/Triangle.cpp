#include "OpenGL/Triangle.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Triangle::Triangle()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    void Triangle::Create(float _pos[m_sizeVertices * m_sizePos])
    {
        int shiftV = m_sizePos + m_sizeColor;

        // Construct the array (pos + color)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            for (int vert = 0; vert < m_sizePos; ++vert)
            {
                m_vertices[(i * shiftV) + vert] = _pos[(i * m_sizePos) + vert];
                // Each vertex are white
                m_vertices[m_sizePos + (i * shiftV) + vert] = 1.0f;
            }
        }

        SendData();
    }


    void Triangle::Create(float _pos[m_sizeVertices * m_sizePos],
                          float _colors[m_sizeVertices * m_sizeColor])
    {
        int shiftV = m_sizePos + m_sizeColor;

        // Construct the array (pos + color)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            for (int vert = 0; vert < m_sizePos; ++vert)
            {
                m_vertices[(i * shiftV) + vert] = _pos[(i * m_sizePos) + vert];
                m_vertices[m_sizePos + (i * shiftV) + vert] = _colors[(i * m_sizePos) + vert];
            }
        }

        SendData();
    }

    void Triangle::SendData()
    {
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

        // Send position (offset take account of color)
        glVertexAttribPointer(0, m_sizePos, GL_FLOAT, GL_FALSE,
                              (m_sizePos + m_sizeColor) * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        // Send color using same offset but using a starting offset to discard position
        glVertexAttribPointer(1, m_sizeColor, GL_FLOAT, GL_FALSE,
                             (m_sizePos + m_sizeColor) * sizeof(float),
                             (void*)(m_sizePos * sizeof(float)));
        glEnableVertexAttribArray(1);
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
