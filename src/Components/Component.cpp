#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Node.hpp"

namespace simpleGL
{
    Component::Component()
    {
        m_pNode = nullptr;
    }


    bool Component::SetParent(Node* _pNode)
    {
        if (_pNode == nullptr || m_pNode == _pNode)
        {
            return false;
        }

        if (m_pNode != nullptr)
        {
            // Detach from previous parent
            m_pNode->ReleaseComponent(m_id);
        }

        m_pNode = _pNode;
        // Give back ownership to the node
        m_pNode->EmplaceBack(this);

        return true;
    }

    const Transform& Component::GetTransform() const
    {
        return m_pNode->GetTransform();
    }
}
