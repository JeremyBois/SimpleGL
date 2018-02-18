#include "Node.hpp"


namespace simpleGL
{
    Node::Node()
    {
        m_isActive = true;
        m_name = "New Node";
        m_pParent = nullptr;

        // Transform can only be added internally
        m_pTransform = new Transform();
        EmplaceBack(m_pTransform);
    }

    Node::~Node()
    {
        // Handle by smart pointers
    }

    void Node::AddNode(Node* _pNode)
    {
        if (_pNode != nullptr)
        {
            m_children.emplace_back(_pNode);
            _pNode->SetParent(this);
        }
    }

    // Call Draw of all children and all gameObject attached
    bool Node::Draw()
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
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Node::Update()
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
            return true;
        }
        else
        {
            return false;
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

    void Node::AttachComponent(Component* _pComponent)
    {
        // Add reference to Node in object
        _pComponent->SetParent(this);
    }

    Component* Node::ReleaseComponent(unsigned int _id)
    {
        Component* result = nullptr;

        for (auto it = m_components.begin(); it != m_components.end(); it++)
        {
            if ((*it)->GetID() == _id)
            {
                // Smart pointer does not manage it anymore
                result = (*it).release();
                m_components.erase(it);
                break;
            }
        }
        return result;
    }

    void Node::EmplaceBack(Component* pComp)
    {
        m_components.emplace_back(pComp);
    }
}
