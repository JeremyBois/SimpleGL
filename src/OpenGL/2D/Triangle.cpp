#include "OpenGL/2D/Triangle.hpp"


namespace simpleGL
{
    Triangle::Triangle()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    Triangle::~Triangle()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Triangle::Create(float _base, float _height)
    {
        // Counter clockwise
        glm::vec2 tempUV[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f}
        };

        auto halfSize = glm::vec2(_base / 2.0f, _height / 2.0f);

        glm::vec3 tempPos[] =
        {
            {0.0f, halfSize.y, 0.0f},
            {-halfSize.x, -halfSize.y, 0.0f},
            {halfSize.x, -halfSize.y, 0.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = tempPos[i];
            m_verticesData[i].Color = glm::vec4(1.0f);
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }

    void Triangle::Create(float _base, float _height,
                          glm::vec4 _colors[SizeVertices])
    {
        // Counter clockwise
        glm::vec2 tempUV[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f}
        };

        auto halfSize = glm::vec2(_base / 2.0f, _height / 2.0f);

        glm::vec3 tempPos[] =
        {
            {0.0f, halfSize.y, 0.0f},
            {-halfSize.x, -halfSize.y, 0.0f},
            {halfSize.x, -halfSize.y, 0.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = tempPos[i];
            m_verticesData[i].Color = _colors[i];
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }

    void Triangle::Create(glm::vec3 _pos[SizeVertices])
    {
        // Counter clockwise
        glm::vec2 tempUV[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = _pos[i];
            m_verticesData[i].Color = glm::vec4(1.0f);
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }


    void Triangle::Create(glm::vec3 _pos[SizeVertices],
                          glm::vec4 _colors[SizeVertices])
    {
        glm::vec2 tempUV[] =
        {
            {0.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 0.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            m_verticesData[i].Position = _pos[i];
            m_verticesData[i].Color = glm::vec4(1.0f);
            m_verticesData[i].UV = tempUV[i];
        }

        SendData();
    }

    void Triangle::SendData()
    {
        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_verticesData), m_verticesData, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, SizePos, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex2D),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(1, SizeColor, GL_FLOAT, GL_FALSE,
                             sizeof(Vertex2D),
                             (void*)(offsetof(Vertex2D, Color)));
        glEnableVertexAttribArray(1);

        // Texture
        glVertexAttribPointer(2, SizeUV, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex2D),
                              (void*)(offsetof(Vertex2D, UV)));
        glEnableVertexAttribArray(2);

        // Avoid side effects
        glBindVertexArray(0);
    }

    void Triangle::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, SizeVertices);

        // Avoid side effects
        glBindVertexArray(0);
    }
}
