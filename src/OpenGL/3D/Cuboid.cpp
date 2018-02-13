#include "OpenGL/3D/Cuboid.hpp"


namespace simpleGL
{
    Cuboid::Cuboid()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    Cuboid::~Cuboid()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Cuboid::Create(float _width, float _height, float _depth)
    {
        float halfWidth  = _width / 2.0f;
        float halfHeight = _height / 2.0f;
        float halfDepth  = _depth / 2.0f;

        // Counter clockwise
        // Top left - Bottom left - Bottom right - Top right
        glm::vec3 tempVertices[] =
        {
            // Front Face (1-2-3-4)
            { -halfWidth, halfHeight, halfDepth },
            { -halfWidth, -halfHeight, halfDepth },
            { halfWidth, halfHeight, halfDepth },
            { halfWidth, -halfHeight, halfDepth },

            // Right Face (2-6-4-8)
            { halfWidth, halfHeight, halfDepth },
            { halfWidth, -halfHeight, halfDepth },
            { halfWidth, halfHeight, -halfDepth },
            { halfWidth, -halfHeight, -halfDepth },

            // Top Face (5-6-1-2)
            { -halfWidth, halfHeight, -halfDepth },
            { -halfWidth, halfHeight, halfDepth },
            { halfWidth, halfHeight, -halfDepth },
            { halfWidth, halfHeight, halfDepth },

            // Back Face (6-5-8-7)
            { halfWidth, halfHeight, -halfDepth },
            { halfWidth, -halfHeight, -halfDepth },
            { -halfWidth, halfHeight, -halfDepth },
            { -halfWidth, -halfHeight, -halfDepth },

            // Left Face (5-1-7-3)
            { -halfWidth, halfHeight, -halfDepth },
            { -halfWidth, -halfHeight, -halfDepth },
            { -halfWidth, halfHeight, halfDepth },
            { -halfWidth, -halfHeight, halfDepth },

            // Bottom Face (3-4-7-8)
            { -halfWidth, -halfHeight, halfDepth },
            { -halfWidth, -halfHeight, -halfDepth },
            { halfWidth, -halfHeight, halfDepth },
            { halfWidth, -halfHeight, -halfDepth }
        };


        int shiftV = m_sizePos + m_sizeColor + m_sizeUV;


        // Construct the array (pos + color + ST)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * shiftV);

            m_vertices[tempShift + 0] = tempVertices[i].x;
            m_vertices[tempShift + 1] = tempVertices[i].y;
            m_vertices[tempShift + 2] = tempVertices[i].z;

            // Default to white color
            m_vertices[m_sizePos + tempShift + 0] = 1.0f;
            m_vertices[m_sizePos + tempShift + 1] = 1.0f;
            m_vertices[m_sizePos + tempShift + 2] = 1.0f;
            m_vertices[m_sizePos + tempShift + 3] = 1.0f;

            // ST
            m_vertices[m_sizePos + m_sizeColor + tempShift + 0] = 0.0f;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 1] = 0.0f;
        }

        SendData();
    }

    void Cuboid::SendData()
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

    void Cuboid::Draw()
    {
        Shape3D::Draw();

        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);

        // One strip per face
        for (int i = 0; i < 6; ++i)
        {
            glDrawArrays(GL_TRIANGLE_STRIP, i * (m_sizeVertices / 6), m_sizeVertices / 6);
        }
    }
}
