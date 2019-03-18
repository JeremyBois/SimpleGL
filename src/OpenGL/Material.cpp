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
            if (m_texturesContainer[_texType][0] == GameManager::GetDataMgr().GetTexture("White"))
            {
                // Then replace it
                m_texturesContainer[_texType][0] = _pTexture;
                return;
            }
            break;
        case TextureType::TextureType_SPECULAR:
        case TextureType::TextureType_EMISSIVE:
            if (m_texturesContainer[_texType][0] == GameManager::GetDataMgr().GetTexture("Black"))
            {
                // Then replace it
                m_texturesContainer[_texType][0] = _pTexture;
                return;
            }
            break;
        default:
            break;
        }

        // Create it if default already replaced
        m_texturesContainer[_texType].emplace_back(_pTexture);
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

        // Add defaults
        Texture* map = GameManager::GetDataMgr().GetTexture("White");

        m_texturesContainer[TextureType::TextureType_DIFFUSE].emplace_back(map);

        map = GameManager::GetDataMgr().GetTexture("Black");
        m_texturesContainer[TextureType::TextureType_SPECULAR].emplace_back(map);
        m_texturesContainer[TextureType::TextureType_EMISSIVE].emplace_back(map);
    }


    void Material::Use(const Transform& _transform)
    {
        // Select shader program for the draw call
        m_pShader->Use();
        // All shaders should have a material structure with this
        std::string baseName = "_objectMaterial_.";

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
                std::string name = baseName + GetTextureTypeName(texType);

                // Look in this type collection
                unsigned int texOfTypeIndex = 0;
                for (Texture *pTex : m_texturesContainer[texType])
                {
                    pTex->Use(currentUnit);

                    m_pShader->SetInt(name + std::to_string(texOfTypeIndex), currentUnit - GL_TEXTURE0);

                    // Units are always store in order starting at GL_TEXTURE0
                    ++currentUnit;
                    ++texOfTypeIndex;
                }
            }
        }

        // Get back to first unit to avoid side effects
        glActiveTexture(GL_TEXTURE0);

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
                return "_noneMap";
            case TextureType_DIFFUSE:
                return "_diffuseMap";
            case TextureType_SPECULAR:
                return "_specularMap";
            case TextureType_AMBIENT:
                return "_ambientMap";
            case TextureType_EMISSIVE:
                return "_emissiveMap";
            case TextureType_HEIGHT:
                return "_heightMap";
            case TextureType_NORMALS:
                return "_normalsMap";
            case TextureType_SHININESS:
                return "_shininessMap";
            case TextureType_OPACITY:
                return "_opacityMap";
            case TextureType_DISPLACEMENT:
                return "_displacementMap";
            case TextureType_LIGHTMAP:
                return "_lightmapMap";
            case TextureType_REFLECTION:
                return "_reflectionMap";
            case TextureType_UNKNOWN:
                return "_unknownMap";
            default:
                return "_noneMap";
        }
    }
}
