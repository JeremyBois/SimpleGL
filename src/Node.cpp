#include "Node.hpp"


namespace simpleGL
{
    Node::Node()
    {
        m_isActive = true;
        m_name = "New Node";
        m_pParent = nullptr;

        m_pTransform = AddComponent<Transform>();
    }

    Node::~Node()
    {
        Destroy();
    }

    void Node::AddNode(Node* _pNode)
    {
        m_children.push_back(_pNode);
        _pNode->SetParent(this);
    }

    // Call Draw of all children and all gameObject attached
    void Node::Draw()
    {
        if (m_isActive)
        {
            unsigned int childrenCount = m_children.size();
            for (unsigned int i = 0; i < childrenCount; ++i)
            {
                m_children[i]->Draw();
            }

            unsigned int objectCount = m_components.size();
            for (unsigned int i = 0; i < objectCount; ++i)
            {
                m_components[i]->Draw();
            }
        }
    }

    void Node::Update()
    {
        if (m_isActive)
        {
            unsigned int childrenCount = m_children.size();
            for (unsigned int i = 0; i < childrenCount; ++i)
            {
                m_children[i]->Update();
            }

            unsigned int objectCount = m_components.size();
            for (unsigned int i = 0; i < objectCount; ++i)
            {
                m_components[i]->Update();
            }
        }
    }

    // Clear children and components (components and node are not destroyed)
    void Node::Clear()
    {
        unsigned int childrenCount = m_children.size();
        for (unsigned int i = 0; i < childrenCount; ++i)
        {
            m_children[i]->Clear();
        }

        m_children.clear();
        m_components.clear();
    }

    void Node::Destroy()
    {
        for (Component* comp : m_components)
        {
            delete comp;
        }
        m_components.clear();

        for (Node* child : m_children)
        {
            delete child;
        }

        m_children.clear();
    }

}
