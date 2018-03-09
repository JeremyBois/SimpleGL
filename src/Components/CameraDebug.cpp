#include "Components/CameraDebug.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include "gtc/matrix_access.hpp"

namespace simpleGL
{
    CameraDebug::CameraDebug()
        : m_fov(45.0f), m_near(0.1f), m_far(100.0f)
    {
        m_width = GameManager::GetWindow().GetWidth();
        m_height = GameManager::GetWindow().GetHeight();
    }

    glm::mat4 CameraDebug::GetViewMatrix() const
    {
        // R⁻¹ * T⁻¹
        // Get position and orientation from transform
        return glm::translate(glm::transpose(glm::mat4_cast(m_pNode->GetTransform().GetRotation())),
                              -GetTransform().GetPosition());
    }

    glm::mat4 CameraDebug::GetPerspectiveMatrix() const
    {
        return glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
    }

    glm::vec3 CameraDebug::GetLook() const
    {
        return GetTransform().GetLook();
    }

    glm::vec3 CameraDebug::GetUp() const
    {
        return GetTransform().GetUp();
    }

    glm::vec3 CameraDebug::GetRight() const
    {
        return GetTransform().GetRight();
    }

    float CameraDebug::GetFov() const
    {
        return m_fov;
    }

    float CameraDebug::GetAspect() const
    {
        return m_width / m_height;
    }

    float CameraDebug::GetAspectWidth() const
    {
        return m_width;
    }

    float CameraDebug::GetAspectHeight() const
    {
        return m_height;
    }

    float CameraDebug::GetNear() const
    {
        return m_near;
    }

    float CameraDebug::GetFar() const
    {
        return m_far;
    }

    /// Positive rotations are counterclockwise.
    void CameraDebug::Rotate(float _degrees, const glm::vec3 &axis)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        glm::quat orientation = pTransform->GetRotation();

        // Update rotation
        orientation *= glm::angleAxis(glm::radians(_degrees), axis * orientation);

        // Return updated vector
        pTransform->SetRotation(orientation);
    }

    /// Rotation around the Y world axis
    void CameraDebug::Yaw(float _degrees)
    {
        Rotate(_degrees, GetTransform().GetUp());
    }

    /// Rotation around the X world axis
    void CameraDebug::Pitch(float _degrees)
    {
        Rotate(_degrees, GetTransform().GetRight());
    }

    /// Rotation around the Z world axis
    void CameraDebug::Roll(float _degrees)
    {
        Rotate(_degrees, GetTransform().GetLook());
    }

    void CameraDebug::Strafe(float _units)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        pTransform->SetPosition(pTransform->GetPosition() +
                                GetTransform().GetRight() * _units);
    }

    void CameraDebug::Fly(float _units)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        pTransform->SetPosition(pTransform->GetPosition() +
                                GetTransform().GetUp() * _units);
    }

    void CameraDebug::Walk(float _units)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        pTransform->SetPosition(pTransform->GetPosition() +
                                GetTransform().GetLook() * _units);
    }

    void CameraDebug::SetAspect(float _width, float _height)
    {
        m_width = _width;
        m_height = _height;
    }

    void CameraDebug::SetNear(float _near)
    {
        m_near = std::min(std::max(_near, 0.1f), m_far);
    }

    void CameraDebug::SetFar(float _far)
    {
        m_far = std::max(m_near, _far);
    }

    /// Set new FOV value in degrees.
    void CameraDebug::SetFov(float _degrees)
    {
        m_fov = std::max(1.0f, _degrees);
    }
}
