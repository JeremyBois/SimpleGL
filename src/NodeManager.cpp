#include "NodeManager.hpp"

#include <assert.h>

namespace simpleGL
{
    NodeManager::NodeManager()
    {
        m_root.SetName("Root");
    }

    NodeManager::~NodeManager()
    {
    }


    void NodeManager::AddNode(Node* _pNode, Node* _pParent)
    {
        if (_pParent != nullptr)
        {
            _pParent->AddNode(_pNode);
        }
        else
        {
            m_root.AddNode(_pNode);
        }
    }

    void NodeManager::Render()
    {
        m_root.Draw();
    }

    void NodeManager::Update()
    {
        m_root.Update();
    }

    void NodeManager::Clear()
    {
        m_root.Clear();
    }

}
