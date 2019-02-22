#include "OpenGL/Material.hpp"

#include "GameManager.hpp"
#include "Components/Transform.hpp"
#include "Components/PointLight.hpp"
#include "Components/DirectionalLight.hpp"
#include "Components/SpotLight.hpp"


// Exceptions
#include <stdexcept>

namespace simpleGL
{
    Material::Material()
        : m_ambiant(glm::vec3(1.0f, 1.0f, 1.0f)), m_diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), m_emission(glm::vec3(0.0f, 0.0f, 0.0f)),
          m_shininess(32.0f), m_glossiness(1.0f)
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
        for (TexturesMapType::iterator it = m_texturesContainer.begin(); it != m_texturesContainer.end(); ++it)
        {
            it->second.clear();
        }

        m_texturesContainer.clear();
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
    void Material::LinkTexture(Texture* _pTexture, TextureType _texType)
    {
        // Create it if does not exists yet
        m_texturesContainer[_texType].emplace_back(_pTexture);
    }

    Texture& Material::GetTexture(GLenum _unit) const
    {
        // return *(m_textureArray.at(_unit));

        // Look in each type
        for (TexturesMapType::const_iterator it = m_texturesContainer.begin(); it != m_texturesContainer.end(); ++it)
        {
            for (Texture* pTex: it->second)
            {
                if (pTex->GetID() == _unit)
                {
                    return *pTex;
                }
            }
        }

        throw std::out_of_range

            // @TODO clean this
            return *(m_texturesContainer.at(-1));
    }

    void Material::UnLinkTexture(GLenum _unit)
    {
        // m_textureArray[_unit]
    }
    void Material::UnLinkAllTextures()
    {
        for (TexturesMapType::iterator it = m_texturesContainer.begin(); it != m_texturesContainer.end(); ++it)
        {
            it->second.clear();
        }

        m_texturesContainer.clear();

        m_pTextureMap[m_diffuseID] = m_pDefaultMap;
        m_pTextureMap[m_specularID] = m_pDefaultMap;
        m_pTextureMap[m_emissionID] = m_pDefaultMap;
    }

    void Material::Use(const Transform& _transform)
    {
        // Select shader program for the draw call
        m_pShader->Use();

        // Pass data from lights to shaders
        PointLight::UseAll(*m_pShader);
        DirectionalLight::UseAll(*m_pShader);
        SpotLight::UseAll(*m_pShader);

        // Also inform shader of camera position
        GameManager::GetWindow().mainCam->Use(*m_pShader);

        // Assign correct texture to correct unit
        for (TexUnitMap::const_iterator it=m_pTextureMap.begin(); it!=m_pTextureMap.end(); ++it)
        {
            it->second->Use(it->first);
        }

        // Pass matrix to vertex shader
        // Model to World and World to Model
        m_pShader->SetMat4("_modelM_", _transform.GetModelMatrix());
        glm::mat4 modelInv = glm::inverse(_transform.GetModelMatrix());
        m_pShader->SetMat4("_modelInvM_", modelInv);

        // Normal matrix in world space
        m_pShader->SetMat3("_normalM_", glm::mat3(glm::transpose(modelInv)));


        // View and projection matrix
        m_pShader->SetMat4("_viewM_", GameManager::GetWindow().GetViewMatrix());
        m_pShader->SetMat4("_projectionM_", GameManager::GetWindow().GetProjectionMatrix());

        // Pass object color informations
        m_pShader->SetInt("_objectMaterial_._diffuseMap", 0);
        m_pShader->SetInt("_objectMaterial_._specularMap", 1);
        m_pShader->SetInt("_objectMaterial_._emissionMap", 2);

        m_pShader->SetVec3("_objectMaterial_.ambiant", m_ambiant);
        m_pShader->SetVec3("_objectMaterial_.diffuse", m_diffuse);
        m_pShader->SetVec3("_objectMaterial_.emission", m_emission);
        m_pShader->SetFloat("_objectMaterial_.shininess", m_shininess);
        m_pShader->SetFloat("_objectMaterial_.glossiness", m_glossiness);
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

    std::string Material::GetTextureTypeName(TextureType _texType) noexcept
    {
        switch (_texType)
        {
            case TextureType_NONE:
                return "None";
            case TextureType_DIFFUSE:
                return "Diffuse";
            case TextureType_SPECULAR:
                return "Specular";
            case TextureType_AMBIENT:
                return "Ambient";
            case TextureType_EMISSIVE:
                return "Emissive";
            case TextureType_HEIGHT:
                return "Height";
            case TextureType_NORMALS:
                return "Normals";
            case TextureType_SHININESS:
                return "Shininess";
            case TextureType_OPACITY:
                return "Opacity";
            case TextureType_DISPLACEMENT:
                return "Displacement";
            case TextureType_LIGHTMAP:
                return "Lightmap";
            case TextureType_REFLECTION:
                return "Reflection";
            case TextureType_UNKNOWN:
                return "Unknown";
        }
    }
}
