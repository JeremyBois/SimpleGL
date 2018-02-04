#include "Node.hpp"


namespace simpleGL
{
    Node::Node()
    {
        m_name = "New Node";
        m_pParent = nullptr;
    }

    Node::~Node()
    {

    }

    void Node::AddGameObject(GameObject* _pGObject)
    {
        m_pGameObjects.push_back(_pGObject);
    }

    void Node::AddNode(Node* _pNode)
    {
        m_pChildren.push_back(_pNode);
        _pNode->SetParent(this);
    }

    // Call Draw of all children and all gameObject attached
    void Node::Draw()
    {
        unsigned int childrenCount = m_pChildren.size();
        for (unsigned int i = 0; i < childrenCount; ++i)
        {
            m_pChildren[i]->Draw();
        }

        unsigned int objectCount = m_pGameObjects.size();
        for (unsigned int i = 0; i < objectCount; ++i)
        {
            m_pGameObjects[i]->Draw();
        }
    }

    void Node::Update()
    {
        unsigned int childrenCount = m_pChildren.size();
        for (unsigned int i = 0; i < childrenCount; ++i)
        {
            m_pChildren[i]->Update();
        }

        unsigned int objectCount = m_pGameObjects.size();
        for (unsigned int i = 0; i < objectCount; ++i)
        {
            m_pGameObjects[i]->Update();
        }

    }

    // Clear children then clear children and gameobject containers.
    void Node::Clear()
    {
        unsigned int childrenCount = m_pChildren.size();
        for (unsigned int i = 0; i < childrenCount; ++i)
        {
            m_pChildren[i]->Clear();
        }

        m_pChildren.clear();
        m_pGameObjects.clear();
    }

}
