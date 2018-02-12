#include "Shape.hpp"

#include "GameManager.hpp"


namespace simpleGL
{
    Shape::Shape()
    {
        // Default shader
        m_baseShader = Shader("shaders/basic.vert",
                              "shaders/basic.frag");
        m_pShader = &m_baseShader;

        // Axis helpers
        m_xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
        m_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        m_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

        // Identity
        m_localToWorld = glm::mat4(1.0f);
        m_pShader->SetMat4("_modelM", m_localToWorld);

        // Default values for scale should be 1.0f not 0.0f
        m_scale = glm::vec3(1.0f);

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

    void Shape::SetPosition(glm::vec3 _position)
    {
        m_position = _position;
        ConstructModelMatrix();
    }

    void Shape::SetScale(glm::vec3 _scale)
    {
        m_scale = _scale;
        ConstructModelMatrix();
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

        // Pass matrices to shader
        m_pShader->SetMat4("_modelM", m_localToWorld);
        // m_pShader->SetMat4("_modelMInv", glm::inverse(m_localToWorld));


        // View and projection
        m_pShader->SetMat4("_viewM", GameManager::GetWindow().GetViewMatrix());
        m_pShader->SetMat4("_projectionM", GameManager::GetWindow().GetProjectionMatrix());

    }


}
