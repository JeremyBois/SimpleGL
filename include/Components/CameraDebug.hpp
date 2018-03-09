#ifndef __CAMERADEBUG__HPP
#define __CAMERADEBUG__HPP


#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/ICamera.hpp"
#include "Components/Component.hpp"


#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"


namespace simpleGL
{
    /// https://www.3dgep.com/understanding-the-view-matrix/
    /// A camera is a component that implement the ICamera interface
    class CameraDebug: public Component
    {
    protected:
        float m_fov, m_near, m_far;
        float m_width, m_height;

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
        virtual void SetAspect(float _width, float _height);
        virtual void SetNear(float _near);
        virtual void SetFar(float _far);
        virtual void SetFov(float _fov);

        virtual glm::mat4 GetViewMatrix() const;
        virtual glm::mat4 GetPerspectiveMatrix() const;
        glm::vec3 GetLook() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;
        float     GetFov() const;
        float     GetAspect() const;
        float     GetAspectWidth() const;
        float     GetAspectHeight() const;
        float     GetNear() const;
        float     GetFar() const;

        virtual bool Draw() {};
        virtual bool Init() {};
        virtual bool Update(){};
        virtual bool Quit(){};
        virtual Component* Clone() {return new CameraDebug(*this);};
    };
}

#endif
