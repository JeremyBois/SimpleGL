#include "OpenGL/Material.hpp"

#include "GameManager.hpp"
#include "Components/Transform.hpp"
#include "Components/PointLight.hpp"
#include "Components/DirectionalLight.hpp"
#include "Components/SpotLight.hpp"


#include <exception>


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

    void Material::LinkTexture(Texture* _pTexture, TextureType _texType)
    {
        // If default still in use replace it
        switch (_texType)
        {
        case TextureType::TextureType_DIFFUSE:
        case TextureType::TextureType_SPECULAR:
        case TextureType::TextureType_EMISSIVE:
            if (m_texturesContainer[_texType][0] == m_pDefaultMap)
            {
                // Then replace it
                m_texturesContainer[_texType][0] = _pTexture;
                return;
            }
        default:
            break;
        }

        // Create it if default already replaced
        m_texturesContainer[_texType].emplace_back(_pTexture);

        ++m_textCount;
    }

    Texture& Material::GetTexture(GLenum _unit) const
    {
        // Look in each type
        for (TexturesMapType::const_iterator it = m_texturesContainer.begin(); it != m_texturesContainer.end(); ++it)
        {
            // Look in this type collection
            for (Texture* pTex: it->second)
            {
                if (pTex->GetID() == _unit)
                {
                    return *pTex;
                }
            }
        }

        // @TODO Throw detailed exception
        throw std::out_of_range(" <_unit> not assign for this material ");
    }

    void Material::UnLinkAllTextures()
    {
        for (TexturesMapType::iterator it = m_texturesContainer.begin(); it != m_texturesContainer.end(); ++it)
        {
            it->second.clear();
        }

        m_texturesContainer.clear();

        m_textCount = 0;

        // Add default
        m_texturesContainer[TextureType::TextureType_DIFFUSE].emplace_back(m_pDefaultMap);
        m_texturesContainer[TextureType::TextureType_SPECULAR].emplace_back(m_pDefaultMap);
        m_texturesContainer[TextureType::TextureType_EMISSIVE].emplace_back(m_pDefaultMap);
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
        unsigned int currentUnit = GL_TEXTURE0;

        // Order defined by enum order
        for (int enumID = TextureType_NONE; enumID != TextureType_LAST; enumID++)
        {
            // Check if key exists
            TextureType texType = static_cast<TextureType>(enumID);
            if (m_texturesContainer.find(texType) != m_texturesContainer.end())
            {
                // Assign correct sampler to shader
                switch (texType)
                {
                    case TextureType::TextureType_DIFFUSE :
                        m_pShader->SetInt("_objectMaterial_._diffuseMap", currentUnit - GL_TEXTURE0);
                        break;
                    case TextureType::TextureType_SPECULAR:
                        m_pShader->SetInt("_objectMaterial_._specularMap", currentUnit - GL_TEXTURE0);
                        break;
                    case TextureType::TextureType_EMISSIVE:
                        m_pShader->SetInt("_objectMaterial_._emissionMap", currentUnit - GL_TEXTURE0);
                        break;
                    default:
                        break;
                }

                // Look in this type collection
                for (Texture *pTex : m_texturesContainer[texType])
                {
                    pTex->Use(currentUnit);
                    ++currentUnit;
                }
            }
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
        // @TODO NEED UPDATE TO BE GENERIC (IN loop)
        // m_pShader->SetInt("_objectMaterial_._diffuseMap", 1);
        // m_pShader->SetInt("_objectMaterial_._specularMap", 3);
        // m_pShader->SetInt("_objectMaterial_._emissionMap", 4);

        m_pShader->SetVec3("_objectMaterial_.ambiant", m_ambiant);
        m_pShader->SetVec3("_objectMaterial_.diffuse", m_diffuse);
        m_pShader->SetVec3("_objectMaterial_.emission", m_emission);
        m_pShader->SetFloat("_objectMaterial_.shininess", m_shininess);
        m_pShader->SetFloat("_objectMaterial_.glossiness", m_glossiness);
    }

    void Material::LinkDiffuseMap(Texture* _pTexture)
    {
        LinkTexture(_pTexture, TextureType::TextureType_DIFFUSE);
    }

    void Material::LinkSpecularMap(Texture* _pTexture)
    {
        LinkTexture(_pTexture, TextureType::TextureType_SPECULAR);
    }

    void Material::LinkEmissionMap(Texture* _pTexture)
    {
        LinkTexture(_pTexture, TextureType::TextureType_EMISSIVE);
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
