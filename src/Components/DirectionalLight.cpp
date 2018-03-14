#include "Components/DirectionalLight.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include <algorithm>

namespace simpleGL
{
    std::vector<DirectionalLight*> DirectionalLight::DirLightContainer;

    DirectionalLight::DirectionalLight()
    {
        DirLightContainer.push_back(this);
    }

    DirectionalLight::~DirectionalLight()
    {
        // Has order does not matter reduce overhead using pop_back in place of removeAt
        std::vector<DirectionalLight*>::iterator it = std::find(DirLightContainer.begin(),
                                                                DirLightContainer.end(), this);

        if (it != DirLightContainer.end())
        {
          // Swap current with last one then remove last
          std::swap(*it, DirLightContainer.back());
          DirLightContainer.pop_back();
        }
    }

    /// Set light color and world position inside the shader
    void DirectionalLight::Use(const Shader& _shader, int _lightIndex) const
    {
        if (IsActive())
        {
            // Pass data to shader
            _shader.Use();
            // Pass color to shader
            _shader.SetVec3("_dirLights_[" + std::to_string(_lightIndex) + "].ambient", m_ambient);
            _shader.SetVec3("_dirLights_[" + std::to_string(_lightIndex) + "].diffuse", m_diffuse);
            _shader.SetVec3("_dirLights_[" + std::to_string(_lightIndex) + "].specular", m_specular);
            // Pass direction
            _shader.SetVec3("_dirLights_[" + std::to_string(_lightIndex) + "].direction", GetTransform().GetLook());
        }
    }

    /// Loop over all light and pass their data to the shader
    void DirectionalLight::UseAll(const Shader& _shader)
    {
        unsigned int lightNumber = DirLightContainer.size();
        for (unsigned int i = 0; i < lightNumber; ++i)
        {
            DirLightContainer[i]->Use(_shader, i);
        }

        // Pass number of point light to compute
        _shader.SetInt("_DirLightCount_", lightNumber);
    }
}
