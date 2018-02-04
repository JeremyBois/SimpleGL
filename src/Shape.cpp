#include "Shape.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Shape::Shape()
    {
        m_pShader = nullptr;
    }

    Shape::~Shape()
    {
        // Should not be destroy by Shape
    }

    void Shape::SetShader(Shader* _pShader)
    {
        m_pShader = _pShader;
    }

}
