#ifndef __TRANSFORM__HPP
#define __TRANSFORM__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Component.hpp"

#include "glm.hpp"


namespace simpleGL
{
    /// Base component attached to every Node.
    class SIMPLEGL_API Transform: public Component
    {
    private:
        glm::vec3 m_refRotOrigin;

    protected:
        // Transformations
        glm::vec3 m_xAxis, m_yAxis, m_zAxis;
        glm::vec3 m_position;
        glm::vec3 m_scale;

        glm::vec3 m_rotOrigin;
        glm::vec3 m_eulerAngles;

        glm::mat4 m_localToWorld;

        virtual void ConstructModelMatrix();

    public:
        Transform();
        virtual ~Transform();

        inline         const glm::vec3  GetPosition()    const {return m_position;}
        inline         const glm::vec3  GetScale()       const {return m_scale;}
        inline virtual const glm::mat4& GetModelMatrix() const {return m_localToWorld;}


        // Common transformations
        virtual void SetPosition(glm::vec3 _position);
        virtual void SetScale(glm::vec3 _scale);
        virtual void SetYawPitchRollAngles(glm::vec3 _eulerAngles, glm::vec3 _origin=glm::vec3(0.0f, 0.0f, 0.0f));
        virtual void SetRotationX(float _degrees);
        virtual void SetRotationY(float _degrees);
        virtual void SetRotationZ(float _degrees);

        const glm::vec3 GetYawPitchRollAngles() const;

        virtual bool Init() {};
        virtual bool Draw() {};
        virtual bool Update() {};
        virtual bool Quit() {};

        virtual Component* Clone() {return new Transform();}
    };
}
#endif
