#include "OpenGL/2D/Quad.hpp"


namespace simpleGL
{
    Quad::Quad()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    Quad::~Quad()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Quad::Create(float _width, float _height)
    {
        float halfWidth  = _width / 2.0f;
        float halfHeight = _height / 2.0f;

        // Counter clockwise (top left - bottom left - bottom right - top right)
        glm::vec3 tempVertices[] =
        {
            {-halfWidth, halfHeight, 0.0f},
            {-halfWidth, -halfHeight, 0.0f},
            {halfWidth, -halfHeight, 0.0f},
            {halfWidth, halfHeight, 0.0f}
        };


        glm::vec2 tempUV[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = tempVertices[i];
            m_verticesData[i].Color = glm::vec4(1.0f);
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }


    void Quad::Create(float _width, float _height,
                      glm::vec4 _colors[SizeVertices])
    {
        float halfWidth  = _width / 2.0f;
        float halfHeight = _height / 2.0f;

        // Counter clockwise
        glm::vec3 tempVertices[] =
        {
            {-halfWidth, halfHeight, 0.0f},
            {-halfWidth, -halfHeight, 0.0f},
            {halfWidth, -halfHeight, 0.0f},
            {halfWidth, halfHeight, 0.0f}
        };


        glm::vec2 tempUV[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = tempVertices[i];
            m_verticesData[i].Color = _colors[i];
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }

    void Quad::SendData()
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
    }

    void Quad::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, SizeVertices);
    }
}
