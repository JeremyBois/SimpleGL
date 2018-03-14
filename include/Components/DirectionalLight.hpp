#ifndef __DIRECTIONALLIGHT__HPP
#define __DIRECTIONALLIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Light.hpp"
#include "OpenGL/Texture.hpp"

#include <vector>

namespace simpleGL
{
    /// Create a light at an infinite distance. Rays coming from the light
    /// source are close to parallel to each other since all its light rays have
    /// the same direction. It is independent of the location of the light source.
    class SIMPLEGL_API DirectionalLight: public Light
    {
    protected:
        static std::vector<DirectionalLight*> DirLightContainer;

    public:
        DirectionalLight();
        virtual ~DirectionalLight();

        // Set light in properties inside the shader
        virtual void Use(const Shader& _shader, int _lightIndex=0) const;
        virtual DirectionalLight* Clone() {return new DirectionalLight(*this);}

        static void UseAll(const Shader& _shader);
    };
}
#endif
