#include "OpenGL/Triangle.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Triangle::Triangle()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    void Triangle::Create(GL_POS3 _pos[m_sizeVertices])
    {
        int shiftV = m_sizePos + m_sizeColor + m_sizeUV;

        // Construct the array (pos + color)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * shiftV);
            m_vertices[tempShift + 0] = _pos[i].x;
            m_vertices[tempShift + 1] = _pos[i].y;
            m_vertices[tempShift + 2] = _pos[i].z;

            // Color (black as default to only see texture if added)
            m_vertices[m_sizePos + tempShift + 0] = 0.0f;
            m_vertices[m_sizePos + tempShift + 1] = 0.0f;
            m_vertices[m_sizePos + tempShift + 2] = 0.0f;

            // UV
            m_vertices[m_sizePos + m_sizeColor + tempShift + 0] = 0.0f;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 1] = 1.0f;
        }

        SendData();
    }


    void Triangle::Create(GL_POS3 _pos[m_sizeVertices],
                          GL_COLOR3 _colors[m_sizeVertices])
    {
        int shiftV = m_sizePos + m_sizeColor + m_sizeUV;

        GL_UV2 tempUV[] =
        {
            {0.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 0.0f}
        };

        // Construct the array (pos + color + UV)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * shiftV);
            m_vertices[tempShift + 0] = _pos[i].x;
            m_vertices[tempShift + 1] = _pos[i].y;
            m_vertices[tempShift + 2] = _pos[i].z;

            // Color
            m_vertices[m_sizePos + tempShift + 0] = _colors[i].r;
            m_vertices[m_sizePos + tempShift + 1] = _colors[i].g;
            m_vertices[m_sizePos + tempShift + 2] = _colors[i].b;

            // UV
            m_vertices[m_sizePos + m_sizeColor + tempShift + 0] = tempUV[i].tu;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 1] = tempUV[i].tv;
        }

        SendData();
    }

    void Triangle::SendData()
    {
        int shiftV = m_sizePos + m_sizeColor + m_sizeUV;

        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, m_sizePos, GL_FLOAT, GL_FALSE,
                              shiftV * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(1, m_sizeColor, GL_FLOAT, GL_FALSE,
                             shiftV * sizeof(float),
                             (void*)(m_sizePos * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture
        glVertexAttribPointer(2, m_sizeUV, GL_FLOAT, GL_FALSE,
                              shiftV * sizeof(float),
                              (void*)((m_sizePos + m_sizeColor) * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void Triangle::Draw()
    {
        // Select shader program for the draw call
        m_pShader->Use();

        // Set associate texture if exist
        if (m_pTexture)
        {
            m_pTexture->Use();
        }

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
