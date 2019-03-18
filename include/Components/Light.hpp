#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Component.hpp"
#include "OpenGL/Texture.hpp"

#include "glm.hpp"

namespace simpleGL
{
    class Shader;

    /// Create a base light similar to a point light without any attenuation
    /// with distance.
    class SIMPLEGL_LOCAL Light: public Component
    {
    protected:
        glm::vec3 m_color;

        Texture* m_pDiffuseMap;
        Texture* m_pSpecularMap;
        Texture* m_pDefaultMap;

        int m_shaderIndex;

    public:
        Light();
        virtual ~Light() = default;

        // Color
        virtual glm::vec3 GetColor() const {return m_color;}

        virtual void SetColor(glm::vec3 _ambient) {m_color = _ambient;}

        // Set light in properties inside the shader
        virtual void Use(const Shader& _shader) const;

        virtual bool Init() {return true;}
        virtual bool Draw(Component *_pcomp);
        virtual bool Update() { return true; }
        virtual bool Quit() {return true;}

        virtual Light* Clone() {return new Light(*this);}
    };
}
#endif
