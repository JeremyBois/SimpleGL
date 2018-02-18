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

        virtual void LookAt() = 0;
        virtual void Move(glm::vec3 _position) = 0;
        virtual void Zoom(float _factor) = 0;

        virtual void Rool(float _degrees) = 0;
        virtual void Yaw(float _degrees) = 0;
        virtual void Pitch(float _degrees) = 0;

        virtual glm::mat4 GetViewMatrix() const = 0;
        virtual glm::mat4 GetPerspectiveMatrix() const = 0;
        virtual glm::vec3 GetPosition() const = 0;
        virtual glm::vec3 GetForward() const = 0;
        virtual glm::vec3 GetUp() const = 0;
        virtual glm::vec3 GetRight() const = 0;
    };
}

#endif
