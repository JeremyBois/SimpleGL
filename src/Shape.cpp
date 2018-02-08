#include "Shape.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Shape::Shape()
        :m_pTexture(nullptr)
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

    void Shape::LinkShader(Shader* _pShader)
    {
        m_pShader = _pShader;
    }

    Shader& Shape::GetShader() const
    {
        return *m_pShader;
    }

    void Shape::UseDefaultShader()
    {
        m_pShader = &m_baseShader;
    }

    void Shape::LinkTexture(Texture* _pTexture)
    {
        m_pTexture = _pTexture;
    }

    Texture& Shape::GetTexture() const
    {
        return *m_pTexture;
    }


}
