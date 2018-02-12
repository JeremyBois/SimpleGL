#include "Shape3D.hpp"

#include "gtc/matrix_transform.hpp"


namespace simpleGL
{
    Shape3D::Shape3D()
    {

    }

    Shape3D::~Shape3D()
    {

    }

    void Shape3D::Draw()
    {
        Shape::Draw();
    }

    void Shape3D::ConstructModelMatrix()
    {
        m_localToWorld = glm::mat4(1.0f);

        m_localToWorld = glm::translate(m_localToWorld, m_position);
        m_localToWorld = glm::scale(m_localToWorld, m_scale);
    }

}
