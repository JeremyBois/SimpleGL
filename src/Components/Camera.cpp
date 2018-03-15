#include "Components/Camera.hpp"
#include "OpenGL/Shader.hpp"
#include "GameManager.hpp"
#include "Node.hpp"

#include "gtc/matrix_access.hpp"


#include "gtx/string_cast.hpp"


namespace simpleGL
{
    Camera::Camera()
        : m_fov(45.0f), m_near(0.1f), m_far(100.0f)
    {
        m_width = GameManager::GetWindow().GetWidth();
        m_height = GameManager::GetWindow().GetHeight();

        // Each new camera become the new main
        GameManager::GetWindow().mainCam = this;
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
        // In view space camera look is reversed
        // https://gamedev.stackexchange.com/questions/65677/quaternion-lookat-for-camera
        return -GetTransform().GetLook();
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

    void Camera::LookAt(glm::vec3 _target)
    {
        Transform* pTransform = &m_pNode->GetTransform();

        // Calculate rotation and axis used to rotate
        glm::vec3 look = glm::normalize(_target - pTransform->GetPosition());

        // Rotation axis is a perpendicular axis of both directions
        glm::vec3 rotationAxis = glm::normalize(glm::cross(-Transform::ZAxis, look));

        // Get angle between world look and camera look
        // Avoid conversion radians --> degrees --> radians
        float angle = acos(glm::dot(-Transform::ZAxis, look));
        pTransform->SetRotation(glm::quat(rotationAxis * angle));

        cout << "Correct : " << glm::to_string(look) << endl;

        // Debug show similar result (difference from floating point errors ???)
        cout << glm::to_string(glm::lookAt(pTransform->GetPosition(), _target, Transform::YAxis)) << endl << endl;
        cout << glm::to_string(GetViewMatrix()) << endl;
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

    /// Set camera world position inside the shader
    void Camera::Use(const Shader& _shader) const
    {
        if (IsActive())
        {
            _shader.Use();

            // Pass position
            _shader.SetVec3("_viewWorldPos_", GetTransform().GetPosition());
        }
    }
}
