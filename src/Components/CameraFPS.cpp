#include "Components/CameraFPS.hpp"
#include "Node.hpp"

#include "Components/Transform.hpp"

namespace simpleGL
{
    CameraFPS::CameraFPS()
    {
        m_fov = 60.0f;
    }

    /// Rotation around the Y world axis
    void CameraFPS::Yaw(float _degrees)
    {
        Rotate(_degrees, -Transform::YAxis);
    }

    /// Rotation around the X world axis
    void CameraFPS::Pitch(float _degrees)
    {
        Rotate(_degrees, GetRight());
    }

    /// Rotation around the Z world axis
    void CameraFPS::Roll(float _degrees)
    {
        Rotate(_degrees, GetLook());
    }

    void CameraFPS::Strafe(float _units)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        pTransform->SetPosition(pTransform->GetPosition() +
                                GetRight() * _units);
    }

    void CameraFPS::Fly(float _units)
    {
    }

    void CameraFPS::Walk(float _units)
    {
        Transform* pTransform = &m_pNode->GetTransform();
        pTransform->SetPosition(pTransform->GetPosition() +
                                GetLook() * _units);
    }
}
