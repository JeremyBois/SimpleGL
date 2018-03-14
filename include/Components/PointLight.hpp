#ifndef __POINTLIGHT__HPP
#define __POINTLIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Light.hpp"
#include "OpenGL/Texture.hpp"

#include <vector>


namespace simpleGL
{
    /// Create a light with a position with a given position somewhere that
    /// illuminates in all directions where the light rays fade out over distance.
    class SIMPLEGL_API PointLight: public Light
    {
    protected:
        static std::vector<PointLight*> PointLightContainer;

        float m_constCoef, m_linearCoef, m_quadraticCoef;

    public:
        PointLight();
        virtual ~PointLight();

        // Set light in properties inside the shader
        virtual void Use(const Shader& _shader, int _lightIndex=0) const;
        virtual PointLight* Clone() {return new PointLight(*this);}

        static void UseAll(const Shader& _shader);
    };
}
#endif
