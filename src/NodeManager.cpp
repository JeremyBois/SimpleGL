#include "NodeManager.hpp"

#include <assert.h>

namespace simpleGL
{
    NodeManager::NodeManager()
    {
        m_pRoot = new Node();
        m_pRoot->SetName("Root");
    }

    NodeManager::~NodeManager()
    {
        if (m_pRoot != nullptr)
        {
            delete m_pRoot;
        }
    }


    void NodeManager::AddNode(Node* _pNode, Node* _pParent)
    {
        if (_pParent != nullptr)
        {
            _pParent->AddNode(_pNode);
        }
        else
        {
            m_pRoot->AddNode(_pNode);
        }
    }

    void NodeManager::Render()
    {
        if (m_pRoot != nullptr)
        {
            m_pRoot->Draw();
        }
    }

    void NodeManager::Update()
    {
        if (m_pRoot != nullptr)
        {
            m_pRoot->Update();
        }
    }

    void NodeManager::Clear()
    {
        if (m_pRoot != nullptr)
        {
            m_pRoot->Clear();
        }
    }

}