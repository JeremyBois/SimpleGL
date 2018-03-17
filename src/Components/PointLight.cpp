#include "Components/PointLight.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include <algorithm>


namespace simpleGL
{

    std::vector<PointLight*> PointLight::PointLightContainer;


    PointLight::PointLight()
        // http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
        : m_constCoef(1.0f), m_linearCoef(0.14f), m_quadraticCoef(0.07f)
    {
        m_color = glm::vec3(0.6f, 0.6f, 0.6f);
        PointLightContainer.push_back(this);
    }

    PointLight::~PointLight()
    {
        // Has order does not matter reduce overhead using pop_back in place of removeAt
        std::vector<PointLight*>::iterator it = std::find(PointLightContainer.begin(),
                                                          PointLightContainer.end(), this);

        if (it != PointLightContainer.end())
        {
          // Swap current with last one then remove last
          std::swap(*it, PointLightContainer.back());
          PointLightContainer.pop_back();
        }
    }


    /// Set light color and world position inside the shader
    void PointLight::Use(const Shader& _shader, int _lightIndex) const
    {
        if (IsActive())
        {
            // Pass data to shader
            _shader.Use();
            // Pass color to shader
            _shader.SetVec3("_pointLights_[" + std::to_string(_lightIndex) + "].color", m_color);

            // Pass position
            _shader.SetVec3("_pointLights_[" + std::to_string(_lightIndex) + "].worldPosition", GetTransform().GetPosition());

            // Pass attenuation parameters
            _shader.SetFloat("_pointLights_[" + std::to_string(_lightIndex) + "].constant", m_constCoef);
            _shader.SetFloat("_pointLights_[" + std::to_string(_lightIndex) + "].linear", m_linearCoef);
            _shader.SetFloat("_pointLights_[" + std::to_string(_lightIndex) + "].quadratic", m_quadraticCoef);
        }
    }


    /// Loop over all light and pass their data to the shader
    void PointLight::UseAll(const Shader& _shader)
    {
        unsigned int lightNumber = PointLightContainer.size();
        for (unsigned int i = 0; i < lightNumber; ++i)
        {
            PointLightContainer[i]->Use(_shader, i);
        }

        // Pass number of point light to compute
        _shader.SetInt("_PointLightCount_", lightNumber);
    }
}
