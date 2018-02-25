#ifndef __CAMERADEBUG__HPP
#define __CAMERADEBUG__HPP


#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/ICamera.hpp"
#include "Components/Component.hpp"


#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"


namespace simpleGL
{
    /// A camera is a component that implement the ICamera interface
    class CameraDebug: public Component
    {
    protected:
        glm::vec3 m_look;
        glm::vec3 m_up;
        glm::vec3 m_right;

        glm::vec3 m_position;
        glm::quat m_orientation;

    public:
        CameraDebug();
        ~CameraDebug() = default;

        virtual void Strafe(float _units);
        virtual void Fly(float _units);
        virtual void Walk(float _units);

        void Rotate(float degrees, const glm::vec3 &axis);
        virtual void Yaw(float degrees);
        virtual void Pitch(float degrees);
        virtual void Roll(float degrees);
        virtual void SetPosition(glm::vec3 _pos);

        virtual glm::mat4 GetViewMatrix() const;
        virtual glm::vec3 GetPosition() const;
        virtual glm::vec3 GetLook() const;
        virtual glm::vec3 GetUp() const;
        virtual glm::vec3 GetRight() const;

        virtual bool Draw() {};
        virtual bool Init() {};
        virtual bool Update(){};
        virtual bool Quit(){};
        virtual Component* Clone() {return nullptr;};
    };
}

#endif
