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
            // Pos
            int tempShift = (i * SizeVerticeData);

            m_verticesData[tempShift + 0] = tempPos[i].x;
            m_verticesData[tempShift + 1] = tempPos[i].y;
            m_verticesData[tempShift + 2] = tempPos[i].z;

            // Default to white color
            m_verticesData[SizePos + tempShift + 0] = 1.0f;
            m_verticesData[SizePos + tempShift + 1] = 1.0f;
            m_verticesData[SizePos + tempShift + 2] = 1.0f;
            m_verticesData[SizePos + tempShift + 3] = 1.0f;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempUV[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempUV[i].t;
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
            // Pos
            int tempShift = (i * SizeVerticeData);

            m_verticesData[tempShift + 0] = tempPos[i].x;
            m_verticesData[tempShift + 1] = tempPos[i].y;
            m_verticesData[tempShift + 2] = tempPos[i].z;

            // Default to white color
            m_verticesData[SizePos + tempShift + 0] = _colors[i].r;
            m_verticesData[SizePos + tempShift + 1] = _colors[i].g;
            m_verticesData[SizePos + tempShift + 2] = _colors[i].b;
            m_verticesData[SizePos + tempShift + 3] = _colors[i].a;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempUV[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempUV[i].t;
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
            // Pos
            int tempShift = (i * SizeVerticeData);

            m_verticesData[tempShift + 0] = _pos[i].x;
            m_verticesData[tempShift + 1] = _pos[i].y;
            m_verticesData[tempShift + 2] = _pos[i].z;

            // Default to white color
            m_verticesData[SizePos + tempShift + 0] = 1.0f;
            m_verticesData[SizePos + tempShift + 1] = 1.0f;
            m_verticesData[SizePos + tempShift + 2] = 1.0f;
            m_verticesData[SizePos + tempShift + 3] = 1.0f;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempUV[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempUV[i].t;
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
            // Pos
            int tempShift = (i * SizeVerticeData);
            m_verticesData[tempShift + 0] = _pos[i].x;
            m_verticesData[tempShift + 1] = _pos[i].y;
            m_verticesData[tempShift + 2] = _pos[i].z;

            // Color
            m_verticesData[SizePos + tempShift + 0] = _colors[i].r;
            m_verticesData[SizePos + tempShift + 1] = _colors[i].g;
            m_verticesData[SizePos + tempShift + 2] = _colors[i].b;
            m_verticesData[SizePos + tempShift + 3] = _colors[i].a;

            // ST
            m_verticesData[SizePos + SizeColor + tempShift + 0] = tempUV[i].s;
            m_verticesData[SizePos + SizeColor + tempShift + 1] = tempUV[i].t;
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

    void Triangle::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, SizeVertices);
    }
}
