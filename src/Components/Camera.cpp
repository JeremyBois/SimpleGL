#include "Components/Camera.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include "gtc/matrix_access.hpp"

namespace simpleGL
{
    Camera::Camera()
        : m_fov(45.0f), m_near(0.1f), m_far(100.0f)
    {
        m_width = GameManager::GetWindow().GetWidth();
        m_height = GameManager::GetWindow().GetHeight();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        // inv(R) * inv(T)
        // Get position and orientation from transform
        return glm::translate(glm::transpose(glm::mat4_cast(GetTransform().GetRotation())),
                              -GetTransform().GetPosition());
    }

    glm::mat4 Camera::GetPerspectiveMatrix() const
    {
        return glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
    }

    glm::vec3 Camera::GetLook() const
    {
        return GetTransform().GetLook();
    }

    glm::vec3 Camera::GetUp() const
    {
        return GetTransform().GetUp();
    }

    glm::vec3 Camera::GetRight() const
    {
        return GetTransform().GetRight();
    }

    float Camera::GetFov() const
    {
        return m_fov;
    }

    float Camera::GetAspect() const
    {
        return m_width / m_height;
    }

    float Camera::GetAspectWidth() const
    {
        return m_width;
    }

    float Camera::GetAspectHeight() const
    {
        return m_height;
    }

    float Camera::GetNear() const
    {
        return m_near;
    }

    float Camera::GetFar() const
    {
        return m_far;
    }

    /// Positive rotations are counterclockwise.
    void Camera::Rotate(float _degrees, const glm::vec3 &axis)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        glm::quat orientation = pTransform->GetRotation();

        // Update rotation
        orientation *= glm::angleAxis(glm::radians(_degrees), axis * orientation);

        // Return updated vector
        pTransform->SetRotation(orientation);
    }

    /// Rotation around the Y world axis
    void Camera::Yaw(float _degrees)
    {
    }

    /// Rotation around the X world axis
    void Camera::Pitch(float _degrees)
    {
    }

    /// Rotation around the Z world axis
    void Camera::Roll(float _degrees)
    {
    }

    void Camera::Strafe(float _units)
    {
    }

    void Camera::Fly(float _units)
    {
    }

    void Camera::Walk(float _units)
    {
    }

    void Camera::SetAspect(float _width, float _height)
    {
        m_width = _width;
        m_height = _height;
    }

    void Camera::SetNear(float _near)
    {
        m_near = std::min(std::max(_near, 0.1f), m_far);
    }

    void Camera::SetFar(float _far)
    {
        m_far = std::max(m_near, _far);
    }

    /// Set new FOV value in degrees.
    void Camera::SetFov(float _degrees)
    {
        m_fov = std::max(1.0f, _degrees);
    }
}
