#ifndef __ICAMERA__HPP
#define __ICAMERA__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "glm.hpp"


namespace simpleGL
{
    /// Interface that Camera must implements.
    class ICamera
    {
    public:
        virtual ~ICamera() = default;

        // virtual void Zoom(float _factor) = 0;
        virtual void Strafe(float _units) = 0;
        virtual void Fly(float _units) = 0;
        virtual void Walk(float _units) = 0;

        virtual void Roll(float _degrees) = 0;
        virtual void Yaw(float _degrees) = 0;
        virtual void Pitch(float _degrees) = 0;
        virtual void SetPosition(glm::vec3& _pos) = 0;

        virtual glm::mat4 GetViewMatrix() const = 0;
        // virtual glm::mat4 GetPerspectiveMatrix() const = 0;
        virtual glm::vec3 GetPosition() const = 0;
        virtual glm::vec3 GetLook() const = 0;
        virtual glm::vec3 GetUp() const = 0;
        virtual glm::vec3 GetRight() const = 0;
    };
}

#endif
