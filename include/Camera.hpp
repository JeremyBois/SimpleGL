#ifndef __CAMERA__HPP
#define __CAMERA__HPP


#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/ICamera.hpp"
#include "Node.hpp"


#include "gtc/matrix_transform.hpp"


namespace simpleGL
{
    /// A camera is a special Node that implement ICamera interface.
    class Camera: public ICamera, Node
    {
    protected:
        glm::vec3 m_position;

    public:
        Camera() = default;
        ~Camera() = default;

        virtual void LookAt();
        virtual void Move();
        virtual void Zoom();

        virtual glm::mat4 GetViewMatrix() const = 0;
        virtual glm::mat4 GetPerspectiveMatrix() const = 0;
        virtual glm::vec3 GetPosition() const = 0;
        virtual glm::vec3 GetForward() const = 0;
        virtual glm::vec3 GetUp() const = 0;
        virtual glm::vec3 GetRight() const = 0;
    };
}

#endif
