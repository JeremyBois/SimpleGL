#include "Shape.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Shape::Shape()
    {
        // Default shader
        m_baseShader = Shader("../shaders/basic.vert",
                              "../shaders/basic.frag");
        m_pShader = &m_baseShader;
    }

    Shape::~Shape()
    {
        // Shader should not be destroy by Shape
    }

    void Shape::SetShader(Shader* _pShader)
    {
        m_pShader = _pShader;
    }

    Shader& Shape::GetShader() const
    {
        return *m_pShader;
    }

    void Shape::UseDefault()
    {
        m_pShader = &m_baseShader;
    }

}
