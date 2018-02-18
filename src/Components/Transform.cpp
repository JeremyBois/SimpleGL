#include "Components/Transform.hpp"

#include "GameManager.hpp"


namespace simpleGL
{
    Transform::Transform()
    {
        // Axis helpers
        m_xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
        m_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        m_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

        // Identity
        m_localToWorld = glm::mat4(1.0f);

        // Default values for scale should be 1.0f not 0.0f
        m_scale = glm::vec3(1.0f);
    }

    Transform::~Transform()
    {

    }

    void Transform::SetPosition(glm::vec3 _position)
    {
        m_position = _position;
        ConstructModelMatrix();
    }

    void Transform::SetScale(glm::vec3 _scale)
    {
        m_scale = _scale;
        ConstructModelMatrix();
    }

    // Euler angles in degrees for rotation around each axis
    void Transform::SetYawPitchRollAngles(glm::vec3 _eulerAngles, glm::vec3 _origin)
    {
        m_eulerAngles.x = glm::radians(_eulerAngles.x);
        m_eulerAngles.y = glm::radians(_eulerAngles.y);
        m_eulerAngles.z = glm::radians(_eulerAngles.z);
        m_rotOrigin = _origin;
        ConstructModelMatrix();
    }

    const glm::vec3 Transform::GetYawPitchRollAngles() const
    {
        glm::vec3 eulerDeg;
        eulerDeg.x = glm::degrees(m_eulerAngles.x);
        eulerDeg.y = glm::degrees(m_eulerAngles.y);
        eulerDeg.z = glm::degrees(m_eulerAngles.z);
    }

    void Transform::SetRotationX(float _degrees)
    {
        m_eulerAngles.x = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Transform::SetRotationY(float _degrees)
    {
        m_eulerAngles.y = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Transform::SetRotationZ(float _degrees)
    {
        m_eulerAngles.z = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Transform::ConstructModelMatrix()
    {
        m_localToWorld = glm::mat4(1.0f);

        if (m_rotOrigin != m_refRotOrigin)
        {
            // Handle new pivot for rotation
            m_localToWorld = glm::translate(m_localToWorld, -m_rotOrigin);
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.z, m_zAxis);
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.y, m_yAxis);
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.x, m_xAxis);
            m_localToWorld = glm::translate(m_localToWorld, m_rotOrigin);

            m_localToWorld = glm::translate(m_localToWorld, m_position);
            m_localToWorld = glm::scale(m_localToWorld, m_scale);

        }
        else
        {
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.z, m_zAxis);
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.y, m_yAxis);
            m_localToWorld = glm::rotate(m_localToWorld, m_eulerAngles.x, m_xAxis);
            m_localToWorld = glm::translate(m_localToWorld, m_position);
            m_localToWorld = glm::scale(m_localToWorld, m_scale);
        }
    }

    bool Transform::SetParent(Node* _pNode)
    {
        return false;
    }
}
