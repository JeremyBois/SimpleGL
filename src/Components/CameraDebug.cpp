#include "Components/CameraDebug.hpp"
#include "GameManager.hpp"

#include "gtc/matrix_access.hpp"

namespace simpleGL
{
    CameraDebug::CameraDebug()
        : m_position(glm::vec3(0.0f, 0.0f, 0.0f)), m_right(glm::vec3(1.0f, 0.0f, 0.0f)),
          m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_look(glm::vec3(0.0f, 0.0f, 1.0f)),
          m_fov(45.0f), m_near(0.1f), m_far(100.0f)
    {
        m_width = GameManager::GetWindow().GetWidth();
        m_height = GameManager::GetWindow().GetHeight();
    }

    glm::mat4 CameraDebug::GetViewMatrix() const
    {
        // R⁻¹ * T⁻¹
        return glm::translate(glm::transpose(glm::mat4_cast(m_orientation)), -m_position);
    }

    glm::mat4 CameraDebug::GetPerspectiveMatrix() const
    {
        return glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
    }

    glm::vec3 CameraDebug::GetPosition() const
    {
        return m_position;
    }

    glm::vec3 CameraDebug::GetLook() const
    {
        return m_look;
    }

    glm::vec3 CameraDebug::GetUp() const
    {
        return m_up;
    }

    glm::vec3 CameraDebug::GetRight() const
    {
        return m_right;
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

    void CameraDebug::SetPosition(glm::vec3 _pos)
    {
        m_position = _pos;
    }

    /// Positive rotations are counterclockwise.
    void CameraDebug::Rotate(float degrees, const glm::vec3 &axis)
    {
        m_orientation *= glm::angleAxis(glm::radians(degrees), axis * m_orientation);

        // A matrix M which transforms from the space A to the space B has the
        // basis vectors of space A, but expressed relative to space B.
        // The View matrix transforms from world space to camera space.
        // Thus, the basis vectors of the View matrix are the basis vectors
        // of world space, as seen from camera space, not the basis vectors of camera space
        glm::mat3 rotationM = glm::mat3_cast(m_orientation);

        // Camera local basis
        // GLM access is M[col][row] (Section 5.6 of the GLSL reference)
        m_right = glm::column(rotationM, 0);
        m_up = glm::column(rotationM, 1);
        m_look = glm::column(rotationM, 2);
    }

    /// Rotation around the Y world axis
    void CameraDebug::Yaw(float degrees)
    {
        Rotate(degrees, m_up);
    }

    /// Rotation around the X world axis
    void CameraDebug::Pitch(float degrees)
    {
        Rotate(degrees, m_right);
    }

    /// Rotation around the Z world axis
    void CameraDebug::Roll(float degrees)
    {
        Rotate(degrees, m_look);
    }

    void CameraDebug::Strafe(float _units)
    {
        m_position += m_right * _units;
    }

    void CameraDebug::Fly(float _units)
    {
        m_position += m_up * _units;
    }

    void CameraDebug::Walk(float _units)
    {
        m_position += m_look * _units;
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
