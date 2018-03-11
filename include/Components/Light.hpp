#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Components/Component.hpp"

#include "glm.hpp"

namespace simpleGL
{
    class Shader;

    /// Abstract class for every component attached to a Node.
    class SIMPLEGL_API Light: public Component
    {
    protected:
        glm::vec3 m_diffuse, m_specular;

    public:
        Light();
        virtual ~Light() = default;


        virtual glm::vec3 GetDiffuseColor() const {return m_diffuse;}
        virtual glm::vec3 GetSpecularColor() const {return m_specular;}

        virtual void      Use(Shader* _shader) const;

        virtual bool Init() {};
        virtual bool Draw() {};
        virtual bool Update() {};
        virtual bool Quit() {};

        virtual Light* Clone() {return new Light(*this);}
    };
}
#endif
