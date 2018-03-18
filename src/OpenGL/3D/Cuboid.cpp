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

        int normalInd = -1;

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = positions[i];
            m_verticesData[i].Color = glm::vec4(1.0f);
            int uvInd = i % 4;
            m_verticesData[i].UV = faceUV[uvInd];

            // Normals
            // On a same face normals are the same for each vertices
            // uvInd == 0 each time a new face starts
            if (uvInd == 0)
            {
                normalInd += 1;
            }
            m_verticesData[i].Normals = faceNormals[normalInd];
        }

        SendData();
    }

    /// Change UV mapping
    /// Counter clockwise definition of vertices using triangles strips
    /// Top left - Bottom left - top right - bottom right
    void Cuboid::SetUV(const glm::vec2 _uvMap[SizeVertices])
    {
        for (int i = 0; i < SizeVertices - 1; ++i)
        {
            m_verticesData[i].UV = _uvMap[i];
        }

        SendData();
    }

    void Cuboid::SendData()
    {
        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_verticesData), m_verticesData, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, SizePos, GL_FLOAT, GL_FALSE,
                              SizeVerticeData * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(1, SizeColor, GL_FLOAT, GL_FALSE,
                             SizeVerticeData * sizeof(float),
                             (void*)(SizePos * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture
        glVertexAttribPointer(2, SizeUV, GL_FLOAT, GL_FALSE,
                              SizeVerticeData * sizeof(float),
                              (void*)((SizePos + SizeColor) * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Normals
        glVertexAttribPointer(3, SizeNormals, GL_FLOAT, GL_FALSE,
                              SizeVerticeData * sizeof(float),
                              (void*)((SizePos + SizeColor + SizeUV) * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void Cuboid::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);

        // One strip per face
        for (int i = 0; i < 6; ++i)
        {
            glDrawArrays(GL_TRIANGLE_STRIP, i * (SizeVertices / 6), SizeVertices / 6);
        }
    }
}
