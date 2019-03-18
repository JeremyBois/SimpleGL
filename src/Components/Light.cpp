#include "Components/Light.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"


namespace simpleGL
{
    Light::Light()
        // : m_ambient(glm::vec3(0.2f, 0.2f, 0.2f)), m_diffuse(glm::vec3(0.5f, 0.5f, 0.5f)),
        //   m_specular(glm::vec3(1.0f, 1.0f, 1.0f))
        : m_color(glm::vec3(0.5f, 0.5f, 0.5f))
    {
    }


    /// Set light color and world position inside the shader
    void Light::Use(const Shader& _shader) const
    {
        if (IsActive())
        {
            // Pass data to shader
            _shader.Use();
            // Pass color to shader
            _shader.SetVec3("_light_.color", m_color);
            // Pass position
            _shader.SetVec3("_light_.worldPosition", GetTransform().GetPosition());
        }
    }

    bool Light::Draw(Component *_pcomp)
    {
        if (IsActive())
        {
            // Update light gizmo
            GameManager::GetDataMgr().GetShader("LightGizmo")->Use();
            GameManager::GetDataMgr().GetShader("LightGizmo")->SetVec3("lightColor", m_color);

            return true;
        }

        return false;
    }
}
