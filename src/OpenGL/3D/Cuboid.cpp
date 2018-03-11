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
        // Top left - Bottom left - top right - bottom right
        glm::vec3 positions[] =
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

        // Counter clockwise
        // Top left - Bottom left - top right - bottom right
        glm::vec2 faceUV[] =
        {
            // All faces
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f }
        };

        // Front - Right - Top - Back - Left - Bottom
        glm::vec3 faceNormals[] =
        {
            {0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, -1.0f},
            {-1.0f, 0.0f, 0.0f},
            {0.0f, -1.0f, 0.0f}
        };

        int shiftV = m_sizePos + m_sizeColor + m_sizeUV + m_sizeNormals;
        int normalInd = -1;

        // Construct the array (pos + color + ST)
        for (int i = 0; i < m_sizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * shiftV);

            m_vertices[tempShift + 0] = positions[i].x;
            m_vertices[tempShift + 1] = positions[i].y;
            m_vertices[tempShift + 2] = positions[i].z;

            // Default to white color
            m_vertices[m_sizePos + tempShift + 0] = 1.0f;
            m_vertices[m_sizePos + tempShift + 1] = 1.0f;
            m_vertices[m_sizePos + tempShift + 2] = 1.0f;
            m_vertices[m_sizePos + tempShift + 3] = 1.0f;

            // ST
            int uvInd = i % 4;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 0] = faceUV[uvInd].x;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 1] = faceUV[uvInd].y;

            // Normals
            // On a same face normals are the same for each vertices
            // uvInd == 0 each time a new face starts
            if (uvInd == 0)
            {
                normalInd += 1;
            }
            m_vertices[m_sizePos + m_sizeColor + m_sizeUV + tempShift + 0] = faceNormals[normalInd].x;
            m_vertices[m_sizePos + m_sizeColor + m_sizeUV + tempShift + 1] = faceNormals[normalInd].y;
            m_vertices[m_sizePos + m_sizeColor + m_sizeUV + tempShift + 2] = faceNormals[normalInd].z;
        }

        SendData();
    }

    /// Change UV mapping
    /// Counter clockwise definition of vertices using triangles strips
    /// Top left - Bottom left - top right - bottom right
    void Cuboid::SetUV(const glm::vec2 _uvMap[m_sizeVertices])
    {
        int shiftV = m_sizePos + m_sizeColor + m_sizeUV + m_sizeNormals;

        for (int i = 0; i < m_sizeVertices - 1; ++i)
        {
            // Just update UV
            int tempShift = (i * shiftV);

            m_vertices[m_sizePos + m_sizeColor + tempShift + 0] = _uvMap[i].x;
            m_vertices[m_sizePos + m_sizeColor + tempShift + 1] = _uvMap[i].y;
        }

        SendData();
    }

    void Cuboid::SendData()
    {
        int shiftV = m_sizePos + m_sizeColor + m_sizeUV + m_sizeNormals;

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

        // Normals
        glVertexAttribPointer(3, m_sizeNormals, GL_FLOAT, GL_FALSE,
                              shiftV * sizeof(float),
                              (void*)((m_sizePos + m_sizeColor + m_sizeUV) * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void Cuboid::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);

        // One strip per face
        for (int i = 0; i < 6; ++i)
        {
            glDrawArrays(GL_TRIANGLE_STRIP, i * (m_sizeVertices / 6), m_sizeVertices / 6);
        }
    }
}
