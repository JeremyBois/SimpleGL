#include "Components/CameraDebug.hpp"
#include "Node.hpp"


namespace simpleGL
{
    CameraDebug::CameraDebug()
    {
        m_fov = 60.0f;
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
}
