#include "Components/Light.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"


namespace simpleGL
{
    Light::Light()
        : m_ambient(glm::vec3(0.2f, 0.2f, 0.2f)), m_diffuse(glm::vec3(0.5f, 0.5f, 0.5f)),
          m_specular(glm::vec3(1.0f, 1.0f, 1.0f))
    {
        GameManager::GetDataMgr().GetShader("LightGizmo")->Use();

        // Pass color to shader
        GameManager::GetDataMgr().GetShader("LightGizmo")->SetVec3("lightColor", m_diffuse);
    }


    /// Set light color and world position inside the shader
    void Light::Use(const Shader& _shader) const
    {
        _shader.Use();
        // Pass color to shader
        _shader.SetVec3("light.ambient", m_ambient);
        _shader.SetVec3("light.diffuse", m_diffuse);
        _shader.SetVec3("light.specular", m_specular);
        // and position
        _shader.SetVec3("light.worldPosition", GetTransform().GetPosition());

        // Update light gizmo
        GameManager::GetDataMgr().GetShader("LightGizmo")->Use();
        GameManager::GetDataMgr().GetShader("LightGizmo")->SetVec3("lightColor", m_diffuse);
    }
}
