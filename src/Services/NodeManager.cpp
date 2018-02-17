#include "Services/NodeManager.hpp"

#include <assert.h>
#include <typeinfo>



namespace simpleGL
{
    NodeManager::NodeManager()
    {
        m_root.SetName("Root");

        m_root.AddComponent<Transform>();
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

    Node* NodeManager::CreateNode(Node* _pParent)
    {
        Node* newNode = new Node();
        AddNode(newNode, _pParent);
        return newNode;
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
