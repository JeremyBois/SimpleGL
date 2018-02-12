#include "Shape2D.hpp"

#include "gtc/matrix_transform.hpp"


namespace simpleGL
{
    Shape2D::Shape2D()
    {
    }

    Shape2D::~Shape2D()
    {

    }

    void Shape2D::Draw()
    {
        Shape::Draw();
    }

    // Euler angles in degrees for rotation around each axis
    void Shape2D::SetYawPitchRollAngles(glm::vec3 _eulerAngles, glm::vec3 _origin)
    {
        m_eulerAngles.x = glm::radians(_eulerAngles.x);
        m_eulerAngles.y = glm::radians(_eulerAngles.y);
        m_eulerAngles.z = glm::radians(_eulerAngles.z);
        m_rotOrigin = _origin;
        ConstructModelMatrix();
    }

    const glm::vec3 Shape2D::GetYawPitchRollAngles() const
    {
        glm::vec3 eulerDeg;
        eulerDeg.x = glm::degrees(m_eulerAngles.x);
        eulerDeg.y = glm::degrees(m_eulerAngles.y);
        eulerDeg.z = glm::degrees(m_eulerAngles.z);
    }

    void Shape2D::SetRotationX(float _degrees)
    {
        m_eulerAngles.x = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Shape2D::SetRotationY(float _degrees)
    {
        m_eulerAngles.y = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Shape2D::SetRotationZ(float _degrees)
    {
        m_eulerAngles.z = glm::radians(_degrees);
        ConstructModelMatrix();
    }

    void Shape2D::ConstructModelMatrix()
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

}
