#include "OpenGL/3D/Plane.hpp"

#include "gtx/string_cast.hpp" // For debug



namespace simpleGL
{
    Plane::Plane()
        : m_nbRows(0), m_nbCols(0)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        m_pVerticesData = nullptr;
        m_pIndices = nullptr;
    }

    Plane::~Plane()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);

        delete m_pVerticesData;
        delete m_pIndices;
    }

    void  Plane::ComputeDataSize(int _nbCols, int _nbRows)
    {
        // Take account for data stored inside each vertices
        // and total number of vertices
        m_sizeVerticesData = (_nbCols * _nbRows) * SizeVerticeData;
    }

    void  Plane::ComputeIndexSize(int _nbCols, int _nbRows)
    {
        // Add two vertice between each rows to preserve winding
        // and draw the whole plane in one draw call
        // Added vertices will create (2 * 2) degenerate triangles (no area)
        // and will be removed in the rendering pipeline
        // This technique is called stitching (https://tinyurl.com/ycnmttu6)
        m_sizeIndex = (_nbCols * _nbRows) + (_nbRows - 2) * (2 + _nbCols);
    }


    void Plane::Create(float _width, float _depth, int _nbCols, int _nbRows)
    {
        // Delete previous data
        delete m_pVerticesData;
        delete m_pIndices;

        // Set size to use for each containers
        ComputeIndexSize(_nbCols, _nbRows);
        ComputeDataSize(_nbCols, _nbRows);

        // Update size reference to be able to change UV easily
        m_nbRows = _nbRows;
        m_nbCols = _nbCols;

        // Define offset
        glm::vec3 offset = glm::vec3(_width / (float)_nbCols, 0.0f, _depth / (float)_nbRows);
        glm::vec3 halfSize =  glm::vec3(_width / 2.0f, 0.0f, _depth / (float)2.0f);

        // Create vertices and populate them
        m_pVerticesData = new float[m_sizeVerticesData];
        int vIndex = 0;
        for (int row = 0; row < _nbRows; row++)
        {
            for (int col = 0; col < _nbCols; col++)
            {
                // Set position at plane centered
                m_pVerticesData[vIndex++] = offset.x * col - halfSize.x;
                m_pVerticesData[vIndex++] = 0.0f;  // No variation on height
                m_pVerticesData[vIndex++] = offset.z * row - halfSize.z;

                // Set color
                m_pVerticesData[vIndex++] = 1.0f;
                m_pVerticesData[vIndex++] = 1.0f;
                m_pVerticesData[vIndex++] = 1.0f;
                m_pVerticesData[vIndex++] = 1.0f;

                // Set UV
                m_pVerticesData[vIndex++] = col / (float)(_nbCols - 1);
                m_pVerticesData[vIndex++] = 1 - row / (float)(_nbRows - 1);

                // Set normals
                m_pVerticesData[vIndex++] = 0.0f;
                m_pVerticesData[vIndex++] = 1.0f;
                m_pVerticesData[vIndex++] = 0.0f;
            }
        }

        // Create index buffer
        m_pIndices = new unsigned int[m_sizeIndex];
        int iIndex = 0;
        int maxForDegenerate = _nbRows - 2;
        for (int row = 0; row < (_nbRows - 1); row++)
        {
            if (row != 0)
            {
                m_pIndices[iIndex++] = row * _nbCols; // First of current strip
            }

            for (int col = 0; col < _nbCols; col++)
            {
                m_pIndices[iIndex++] = col + row * _nbCols;
                m_pIndices[iIndex++] = col + (row + 1) * _nbCols;
            }

            // No degenerate triangles for last strip
            if (row < maxForDegenerate)
            {
                m_pIndices[iIndex++] = (_nbCols - 1) + (row + 1) * _nbCols;  // Last of current strip
            }
        }



        // // Debug
        // cout << "Offset: " << glm::to_string(offset) << endl;
        // cout << "Vertice count: " << (_nbCols * _nbRows) << endl;
        // cout << "Vertice data size: " << SizeVerticeData << endl;
        // cout << "Data size: " << m_sizeVerticesData << endl;
        // cout << "Index size: " << m_sizeIndex << endl;
        // cout << "Index count: " << iIndex << endl;
        // DebugVertices();
        // DebugIndex();


        // Send data to buffer
        SendData();
    }

    void Plane::SetClampedUV()
    {
        int baseOffset = SizePos + SizeColor;
        int vIndex = 0;
        for (int row = 0; row < m_nbRows; row++)
        {
            for (int col = 0; col < m_nbCols; col++)
            {
                // Offset array to change only UV
                vIndex += baseOffset;

                // Set UV
                m_pVerticesData[vIndex++] = col / (float)(m_nbCols - 1);
                m_pVerticesData[vIndex++] = 1 - row / (float)(m_nbRows - 1);

                // OffSet normals
                vIndex += SizeNormals;
            }
        }

        SendData();
    }

    void Plane::SetUnclampedUV()
    {
        int baseOffset = SizePos + SizeColor;
        glm::vec2 uv = glm::vec2(0, m_nbRows);
        int vIndex = 0;
        for (int row = 0; row < m_nbRows; row++)
        {
            for (int col = 0; col < m_nbCols; col++)
            {
                // Offset array to change only UV
                vIndex += baseOffset;

                // Set UV
                m_pVerticesData[vIndex++] = uv.x;
                m_pVerticesData[vIndex++] = uv.y;

                uv.x += 1.0f;

                // OffSet normals
                vIndex += SizeNormals;
            }
            uv.x = 0;
            uv.y -= 1.0f;
        }

        SendData();
    }

    void Plane::DebugIndex()
    {
        for (int i = 0; i < m_sizeIndex; ++i)
        {
            cout << m_pIndices[i] << " ";
        }
        cout << endl;
    }

    void Plane::DebugVertices()
    {
        for (int i = 0; i < m_sizeVerticesData; i = i + 3)
        {
            cout << m_pVerticesData[i] << " ";
            cout << m_pVerticesData[i + 1] << " ";
            cout << m_pVerticesData[i + 2] << " ";
            cout << "\t";
        }
        cout << endl;
    }


    void Plane::SendData()
    {
        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_sizeVerticesData * sizeof(m_pVerticesData), m_pVerticesData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeIndex * sizeof(m_pIndices), m_pIndices, GL_STATIC_DRAW);

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

        // UV
        glVertexAttribPointer(2, SizeUV, GL_FLOAT, GL_FALSE,
                              SizeVerticeData * sizeof(float),
                              (void*)((SizePos + SizeColor) * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Normals
        glVertexAttribPointer(3, SizeUV, GL_FLOAT, GL_FALSE,
                              SizeVerticeData * sizeof(float),
                              (void*)((SizePos + SizeColor + SizeUV) * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void Plane::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLE_STRIP, m_sizeIndex, GL_UNSIGNED_INT, 0);
    }
}
