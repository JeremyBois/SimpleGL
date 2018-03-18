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
        glm::vec2 tempVertices[] =
        {
            {-halfWidth, halfHeight},
            {-halfWidth, -halfHeight},
            {halfWidth, -halfHeight},
            {halfWidth, halfHeight}
        };


        glm::vec2 tempST[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * SizeVerticeData);

            m_verticesData[tempShift + 0] = tempVertices[i].x;
            m_verticesData[tempShift + 1] = tempVertices[i].y;
            m_verticesData[tempShift + 2] = 0.0f;

            // Default to white color
            m_verticesData[SizePos + tempShift + 0] = 1.0f;
            m_verticesData[SizePos + tempShift + 1] = 1.0f;
            m_verticesData[SizePos + tempShift + 2] = 1.0f;
            m_verticesData[SizePos + tempShift + 3] = 1.0f;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempST[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempST[i].t;
        }

        SendData();
    }


    void Quad::Create(float _width, float _height,
                      glm::vec4 _colors[SizeVertices])
    {
        float halfWidth  = _width / 2.0f;
        float halfHeight = _height / 2.0f;

        // Counter clockwise
        glm::vec2 tempVertices[] =
        {
            {-halfWidth, halfHeight},
            {-halfWidth, -halfHeight},
            {halfWidth, -halfHeight},
            {halfWidth, halfHeight}
        };


        glm::vec2 tempST[] =
        {
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}
        };

        // Construct the array (pos + color + ST)
        for (int i = 0; i < SizeVertices; ++i)
        {
            // Pos
            int tempShift = (i * SizeVerticeData);
            m_verticesData[tempShift + 0] = tempVertices[i].x;
            m_verticesData[tempShift + 1] = tempVertices[i].y;
            m_verticesData[tempShift + 2] = 0.0f;

            // Color
            m_verticesData[SizePos + tempShift + 0] = _colors[i].r;
            m_verticesData[SizePos + tempShift + 1] = _colors[i].g;
            m_verticesData[SizePos + tempShift + 2] = _colors[i].b;
            m_verticesData[SizePos + tempShift + 3] = _colors[i].a;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempST[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempST[i].t;
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
