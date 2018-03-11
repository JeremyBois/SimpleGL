#include "OpenGL/Material.hpp"

#include "GameManager.hpp"
#include "Components/Transform.hpp"

namespace simpleGL
{
    Material::Material()
        : m_diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), m_emission(glm::vec3(0.0f, 0.0f, 0.0f)),
          m_specular(glm::vec3(1.0f, 1.0f, 1.0f)), m_shininess(32.0f), m_glossiness(1.0f)
    {
        // Default shader
        m_baseShader = Shader("shaders/basic.vert",
                              "shaders/basic.frag");
        m_pShader = &m_baseShader;

        // Default texture
        m_pDefaultMap = GameManager::GetDataMgr().GetTexture("White");
        UnLinkAllTextures();
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

    /// Link texture from 2 to ...
    /// 0 and 1 are reserved for lighting effect (diffuse and specular map).
    void Material::LinkTexture(Texture* _pTexture, GLenum _unit)
    {
        if (_unit != m_diffuseID && _unit != m_specularID && _unit != m_emissionID)
        {
            m_pTextureMap[_unit] = _pTexture;
        }
    }

    Texture& Material::GetTexture(GLenum _unit) const
    {
        return *(m_pTextureMap.at(_unit));
    }

    void Material::UnLinkTexture(GLenum _unit)
    {
        if (_unit == m_diffuseID || _unit == m_specularID || _unit == m_emissionID)
        {
            m_pTextureMap[_unit] = m_pDefaultMap;
        }
        else
        {
            m_pTextureMap.erase(_unit);
        }
    }
    void Material::UnLinkAllTextures()
    {
        m_pTextureMap.clear();

        m_pTextureMap[m_diffuseID] = m_pDefaultMap;
        m_pTextureMap[m_specularID] = m_pDefaultMap;
        m_pTextureMap[m_emissionID] = m_pDefaultMap;
    }

    void Material::Use(const Transform& _transform)
    {
        // Select shader program for the draw call
        m_pShader->Use();
        m_pShader->SetInt("objectMaterial._diffuseMap", m_diffuseID);
        m_pShader->SetInt("objectMaterial._specularMap", m_specularID);
        m_pShader->SetInt("objectMaterial._emissionMap", m_emissionID);

        // Assign correct texture to correct unit
        for (TexUnitMap::const_iterator it=m_pTextureMap.begin(); it!=m_pTextureMap.end(); ++it)
        {
            it->second->Use(it->first);
        }

        // Model to World and World to Model
        m_pShader->SetMat4("_modelM", _transform.GetModelMatrix());
        glm::mat4 modelInv = glm::inverse(_transform.GetModelMatrix());
        m_pShader->SetMat4("_modelInvM", modelInv);

        // Normal matrix in world space
        m_pShader->SetMat3("_normalM", glm::mat3(glm::transpose(modelInv)));

        // View and projection matrix
        m_pShader->SetMat4("_viewM", GameManager::GetWindow().GetViewMatrix());
        m_pShader->SetMat4("_projectionM", GameManager::GetWindow().GetProjectionMatrix());

        // Pass object color informations
        m_pShader->SetVec3("objectMaterial.diffuse", m_diffuse);
        m_pShader->SetVec3("objectMaterial.specular", m_specular);
        m_pShader->SetVec3("objectMaterial.emission", m_emission);
        m_pShader->SetFloat("objectMaterial.shininess", m_shininess);
        m_pShader->SetFloat("objectMaterial.glossiness", m_glossiness);
    }

    void Material::LinkDiffuseMap(Texture* _pTexture)
    {
        m_pTextureMap[m_diffuseID] = _pTexture;
    }

    void Material::LinkSpecularMap(Texture* _pTexture)
    {
        m_pTextureMap[m_specularID] = _pTexture;
    }

    void Material::LinkEmissionMap(Texture* _pTexture)
    {
        m_pTextureMap[m_emissionID] = _pTexture;
    }

    void Material::UnLinkDiffuseMap()
    {
        m_pTextureMap[m_diffuseID] = m_pDefaultMap;
    }

    void Material::UnLinkSpecularMap()
    {
        m_pTextureMap[m_specularID] = m_pDefaultMap;
    }

    void Material::UnLinkEmissionMap()
    {
        m_pTextureMap[m_emissionID] = m_pDefaultMap;
    }

    Texture& Material::GetDiffuseMap() const
    {
        return *(m_pTextureMap.at(m_diffuseID));
    }

    Texture& Material::GetSpecularMap() const
    {
        return *(m_pTextureMap.at(m_specularID));
    }

    Texture& Material::GetEmissionMap() const
    {
        return *(m_pTextureMap.at(m_emissionID));
    }
}
