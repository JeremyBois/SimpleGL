#include "OpenGL/Material.hpp"

#include "GameManager.hpp"
#include "Components/Transform.hpp"

namespace simpleGL
{
    Material::Material()
    {
        // Default shader
        m_baseShader = Shader("shaders/basic.vert",
                              "shaders/basic.frag");
        m_pShader = &m_baseShader;
    }

    Material::~Material()
    {
        m_pTextureMap.clear();
    }

    void Material::LinkShader(Shader* _pShader)
    {
        m_pShader = _pShader;
    }

    Shader& Material::GetShader() const
    {
        return *m_pShader;
    }

    void Material::UseDefaultShader()
    {
        m_pShader = &m_baseShader;
    }

    void Material::LinkTexture(Texture* _pTexture, GLenum _unit)
    {
        m_pTextureMap[_unit] = _pTexture;
    }

    Texture& Material::GetTexture(GLenum _unit) const
    {
        return *(m_pTextureMap.at(_unit));
    }

    void Material::UnLinkTexture(GLenum _unit)
    {
        m_pTextureMap.erase(_unit);
    }
    void Material::UnLinkAllTextures()
    {
        m_pTextureMap.clear();
    }

    void Material::Use(const Transform& _transform)
    {
        // Select shader program for the draw call
        m_pShader->Use();

        // Assign correct texture to correct unit
        for (TexUnitMap::const_iterator it=m_pTextureMap.begin(); it!=m_pTextureMap.end(); ++it)
        {
            it->second->Use(it->first);
        }

        // Pass matrices to shader
        m_pShader->SetMat4("_modelM", _transform.GetModelMatrix());
        m_pShader->SetMat4("_modelMInv", glm::inverse(_transform.GetModelMatrix()));


        // View and projection
        m_pShader->SetMat4("_viewM", GameManager::GetWindow().GetViewMatrix());
        m_pShader->SetMat4("_projectionM", GameManager::GetWindow().GetProjectionMatrix());
    }
}
