#include "Shape2D.hpp"

#include "gtc/matrix_transform.hpp"
// #include "gtc/matrix_inverse.hpp"

namespace simpleGL
{
    Shape2D::Shape2D()
        : m_angleRad(0)
    {
        m_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        m_scale    = glm::vec3(1.0f, 1.0f, 1.0f);

        // Identity
        m_localToWorld = glm::mat4(1.0f);

        // To avoid initialization each type matrix is constructed
        m_refRotOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Shape2D::~Shape2D()
    {

    }

    void Shape2D::Draw()
    {
        // Select texture for each unit and shader
        Shape::Draw();

        // Pass matrices to shader
        m_pShader->SetMat4("ObjectToWorld", m_localToWorld);
        m_pShader->SetMat4("WorldToObject", glm::inverse(m_localToWorld));
    }


    void Shape2D::SetRotation(float _degrees, glm::vec3 _origin)
    {
        m_angleRad = glm::radians(_degrees);
        m_rotOrigin = _origin;
        ConstructLocalToWorldMatrix();
    }

    void Shape2D::SetPosition(glm::vec3 _position)
    {
        m_position = _position;
        ConstructLocalToWorldMatrix();
    }

    void Shape2D::SetScale(glm::vec3 _scale)
    {
        m_scale = _scale;
        ConstructLocalToWorldMatrix();
    }

    void Shape2D::ConstructLocalToWorldMatrix()
    {
        m_localToWorld = glm::mat4(1.0f);

        if (m_rotOrigin != m_refRotOrigin)
        {
            // Handle new pivot for rotation
            m_localToWorld = glm::translate(m_localToWorld, -m_rotOrigin);
            m_localToWorld = glm::rotate(m_localToWorld, m_angleRad, m_zAxis);
            m_localToWorld = glm::translate(m_localToWorld, m_rotOrigin);

            m_localToWorld = glm::translate(m_localToWorld, m_position);
            m_localToWorld = glm::scale(m_localToWorld, m_scale);

        }
        else
        {
            m_localToWorld = glm::rotate(m_localToWorld, m_angleRad, m_zAxis);
            m_localToWorld = glm::translate(m_localToWorld, m_position);
            m_localToWorld = glm::scale(m_localToWorld, m_scale);
        }
    }

}
