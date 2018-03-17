#include "OpenGL/3D/Plane.hpp"

#include "gtx/string_cast.hpp" // For debug



namespace simpleGL
{
    Plane::Plane()
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
        m_sizeVertices = (_nbCols * _nbRows);
        m_sizeData = (m_sizePos) * m_sizeVertices;
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

        // Define offset
        glm::vec3 offset = glm::vec3(_width / (float)_nbCols, 0.0f, _depth / (float)_nbRows);


        // Create vertices and populate them
        m_pVerticesData = new float[m_sizeData];
        int vIndex = 0;
        for (int row = 0; row < _nbRows; row++)
        {
            for (int col = 0; col < _nbCols; col++)
            {
                // Set position
                m_pVerticesData[vIndex++] = offset.x * col;
                m_pVerticesData[vIndex++] = 0.0f;  // No variation on height
                m_pVerticesData[vIndex++] = offset.z * row;

                // Set color

                // Set UV

                // Set normals
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



        // Debug
        cout << "Offset: " << glm::to_string(offset) << endl;
        cout << "Vertice size: " << m_sizeVertices << endl;
        cout << "Data size: " << m_sizeData << endl;
        cout << "Index size: " << m_sizeIndex << endl;
        cout << "Index count: " << iIndex << endl;
        DebugVertices();
        DebugIndex();


        // Send data to buffer
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
        for (int i = 0; i < m_sizeData; i = i + 3)
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
        int shiftV = m_sizePos;

        // Store inside the first VAO
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_sizeData, m_pVerticesData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeIndex, m_pIndices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, m_sizePos, GL_FLOAT, GL_FALSE,
                              shiftV * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }

    void Plane::Draw()
    {
        // Select VAO to use for passing object to GPU
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLE_STRIP, m_sizeIndex, GL_UNSIGNED_INT, 0);
    }
}
