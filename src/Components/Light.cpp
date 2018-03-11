#include "Components/Light.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"


namespace simpleGL
{
    Light::Light()
        : m_diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), m_specular(glm::vec3(1.0f, 1.0f, 1.0f))
    {
        GameManager::GetDataMgr().GetShader("LightGizmo")->Use();

        // Pass color to shader
        GameManager::GetDataMgr().GetShader("LightGizmo")->SetVec3("lightColor", m_diffuse);
    }


    /// Set light color and world position inside the shader
    void Light::Use(Shader* _shader) const
    {
        _shader->Use();

        // Pass color to shader
        _shader->SetVec3("lightColor", m_diffuse);
        _shader->SetVec3("lightSpecularColor", m_specular);

        // and position
        _shader->SetVec3("lightWorldPos", GetTransform().GetPosition());
    }
}
