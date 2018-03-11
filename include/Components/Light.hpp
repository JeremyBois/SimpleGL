#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Component.hpp"
#include "OpenGL/Texture.hpp"


#include "glm.hpp"

namespace simpleGL
{
    class Shader;

    /// Abstract class for every component attached to a Node.
    class SIMPLEGL_API Light: public Component
    {
    protected:
        glm::vec3 m_ambient, m_diffuse, m_specular;

        Texture* m_pDiffuseMap;
        Texture* m_pSpecularMap;
        Texture* m_pDefaultMap;

    public:
        Light();
        virtual ~Light() = default;

        // Color
        virtual glm::vec3 GetAmbient() const {return m_ambient;}
        virtual glm::vec3 GetDiffuse() const {return m_diffuse;}
        virtual glm::vec3 GetSpecular() const {return m_specular;}

        virtual void SetAmbient(glm::vec3 _ambient) {m_ambient = _ambient;}
        virtual void SetDiffuse(glm::vec3 _diffuse) {m_diffuse = _diffuse;}
        virtual void SetSpecular(glm::vec3 _specular) {m_specular = _specular;}

        // Set light in properties inside the shader
        virtual void Use(const Shader& _shader) const;

        virtual bool Init() {};
        virtual bool Draw() {};
        virtual bool Update() {};
        virtual bool Quit() {};

        virtual Light* Clone() {return new Light(*this);}
    };
}
#endif
