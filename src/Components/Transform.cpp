#include "Components/Transform.hpp"

#include "GameManager.hpp"
#include "gtc/matrix_access.hpp"

namespace simpleGL
{

    // Axis helpers (World basis)
    const glm::vec3 Transform::s_xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 Transform::s_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 Transform::s_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);


    Transform::Transform()
        : m_right(glm::vec3(1.0f, 0.0f, 0.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
          m_look(glm::vec3(0.0f, 0.0f, 1.0f))
    {
        // Identity
        m_localToWorld = glm::mat4(1.0f);

        // Default values for scale should be 1.0f not 0.0f
        m_scale = glm::vec3(1.0f);
    }

    Transform::~Transform()
    {

    }

    void Transform::SetPosition(const glm::vec3 _position)
    {
        m_position = _position;
        ConstructModelMatrix();
    }

    void Transform::SetScale(const glm::vec3 _scale)
    {
        m_scale = _scale;
        ConstructModelMatrix();
    }

    void Transform::SetRotation(const glm::quat _rotation)
    {
        m_orientation = glm::normalize(_rotation);

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

        ConstructModelMatrix();
    }

    // Euler angles in degrees for rotation around each axis
    void Transform::SetRotation(const glm::vec3 _eulerAngles)
    {
        m_orientation = glm::quat(glm::vec3(glm::radians(_eulerAngles.x),
                                            glm::radians(_eulerAngles.y),
                                            glm::radians(_eulerAngles.z)
                                           )
                                 );

        ConstructModelMatrix();
    }

    /// Return Euler angles from orientation in degrees
    const glm::vec3 Transform::GetYawPitchRollAngles() const
    {
        glm::vec3 eulerDeg = glm::eulerAngles(m_orientation);
        eulerDeg.x = glm::degrees(eulerDeg.x);
        eulerDeg.y = glm::degrees(eulerDeg.y);
        eulerDeg.z = glm::degrees(eulerDeg.z);

        return eulerDeg;
    }

    void Transform::SetRotationX(float _degrees)
    {
        SetRotation(glm::angleAxis(glm::radians(_degrees), Transform::s_xAxis));
    }

    void Transform::SetRotationY(float _degrees)
    {
        SetRotation(glm::angleAxis(glm::radians(_degrees), Transform::s_yAxis));
    }

    void Transform::SetRotationZ(float _degrees)
    {
        SetRotation(glm::angleAxis(glm::radians(_degrees), Transform::s_zAxis));
    }

    void Transform::ConstructModelMatrix()
    {
        m_localToWorld = glm::mat4_cast(m_orientation);
        m_localToWorld = glm::translate(m_localToWorld, m_position);
        m_localToWorld = glm::scale(m_localToWorld, m_scale);
    }

    bool Transform::SetParent(Node* _pNode)
    {
        return false;
    }
}
