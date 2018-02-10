#include "Shape.hpp"

#include "Utility/Tools.hpp"

namespace simpleGL
{
    Shape::Shape()
    {
        // Default shader
        m_baseShader = Shader("shaders/basic.vert",
                              "shaders/basic.frag");
        m_pShader = &m_baseShader;
    }

    Shape::~Shape()
    {
        m_pTextureMap.clear();
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

    void Shape::LinkTexture(Texture* _pTexture, GLenum _unit)
    {
        m_pTextureMap[_unit] = _pTexture;
    }

    Texture& Shape::GetTexture(GLenum _unit) const
    {
        return *(m_pTextureMap.at(_unit));
    }

    void Shape::UnLinkTexture(GLenum _unit)
    {
        m_pTextureMap.erase(_unit);
    }
    void Shape::UnLinkAllTextures()
    {
        m_pTextureMap.clear();
    }

    void Shape::Draw()
    {
        // Select shader program for the draw call
        m_pShader->Use();

        // Assign correct texture to correct unit
        for (TexUnitMap::const_iterator it=m_pTextureMap.begin(); it!=m_pTextureMap.end(); ++it)
        {
            it->second->Use(it->first);
        }

    }


}
