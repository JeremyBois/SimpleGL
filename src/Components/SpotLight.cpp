#include "Components/SpotLight.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include <algorithm>


namespace simpleGL
{

    std::vector<SpotLight*> SpotLight::SpotLightContainer;


    SpotLight::SpotLight()
        // http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
        : m_constCoef(1.0f), m_linearCoef(0.09f), m_quadraticCoef(0.032f),
          m_cutOffAngle(12.5f), m_outerCutOffAngle(18.5f)
    {
        m_diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        SpotLightContainer.push_back(this);
    }

    SpotLight::~SpotLight()
    {
        // Has order does not matter reduce overhead using pop_back in place of removeAt
        std::vector<SpotLight*>::iterator it = std::find(SpotLightContainer.begin(),
                                                          SpotLightContainer.end(), this);

        if (it != SpotLightContainer.end())
        {
          // Swap current with last one then remove last
          std::swap(*it, SpotLightContainer.back());
          SpotLightContainer.pop_back();
        }
    }


    /// Set light color and world position inside the shader
    void SpotLight::Use(const Shader& _shader, int _lightIndex) const
    {
        if (IsActive())
        {
            // Pass data to shader
            _shader.Use();
            // Pass color to shader
            _shader.SetVec3("_spotLights_[" + std::to_string(_lightIndex) + "].ambient", m_ambient);
            _shader.SetVec3("_spotLights_[" + std::to_string(_lightIndex) + "].diffuse", m_diffuse);
            _shader.SetVec3("_spotLights_[" + std::to_string(_lightIndex) + "].specular", m_specular);

            // Pass position
            _shader.SetVec3("_spotLights_[" + std::to_string(_lightIndex) + "].worldPosition", GetTransform().GetPosition());
            _shader.SetVec3("_spotLights_[" + std::to_string(_lightIndex) + "].worldDirection", GetTransform().GetLook());

            // Pass attenuation parameters
            _shader.SetFloat("_spotLights_[" + std::to_string(_lightIndex) + "].constant", m_constCoef);
            _shader.SetFloat("_spotLights_[" + std::to_string(_lightIndex) + "].linear", m_linearCoef);
            _shader.SetFloat("_spotLights_[" + std::to_string(_lightIndex) + "].quadratic", m_quadraticCoef);

            // Pass angle as a cos value to reduce computation time in shader
            // In the fragment shader we compute the dot product between the LightDir (lightPos - fragPos)
            // and the SpotDir using normalized vector --> Get cos(angle)
            _shader.SetFloat("_spotLights_[" + std::to_string(_lightIndex) + "].cutOff",
                             glm::cos(glm::radians(m_cutOffAngle)));
            _shader.SetFloat("_spotLights_[" + std::to_string(_lightIndex) + "].outerCutOff",
                             glm::cos(glm::radians(m_outerCutOffAngle)));
        }
    }


    /// Loop over all light and pass their data to the shader
    void SpotLight::UseAll(const Shader& _shader)
    {
        unsigned int lightNumber = SpotLightContainer.size();
        for (unsigned int i = 0; i < lightNumber; ++i)
        {
            SpotLightContainer[i]->Use(_shader, i);
        }

        // Pass number of point light to compute
        _shader.SetInt("_SpotLightCount_", lightNumber);
    }
}
