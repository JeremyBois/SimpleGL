#ifndef __NODE__HPP
#define __NODE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Transform.hpp"
#include "Components/Camera.hpp"
#include "Utility/Tools.hpp"
#include "Utility/TransformException.hpp"

#include "GameObject.hpp"
#include "GameManager.hpp"

#include <vector>
#include <typeinfo>
#include <memory>
#include <type_traits>

namespace simpleGL
{
    typedef std::unique_ptr<Node> NodePtr;
    typedef std::vector<NodePtr> NodesList;

    typedef std::unique_ptr<Component> ComponentPtr;
    typedef std::vector<ComponentPtr> ComponentsVector;

    /// A Node can be the parent of multiple nodes (children) and can
    /// have multiple components.
    class SIMPLEGL_API Node: public GameObject
    {
    private:
        // Provide access to private and protected members of Node
        friend bool Component::SetParent(Node *_pNode);

        std::string m_name;

        // Composite
        Node*              m_pParent;
        Transform*         m_pTransform;
        NodesList          m_children;
        ComponentsVector   m_components;


        Component* ReleaseComponent(unsigned int _id);
        void       EmplaceBack(Component* pComp);

    public:
        Node();
        ~Node();

        inline void   SetName(std::string _name) {m_name = _name;}
        inline void   SetParent(Node* _pNode){m_pParent = _pNode;}

        inline const std::string& GetName() const {return m_name;}
        inline Transform&         GetTransform() const {return *m_pTransform;}
        inline Node&              GetParent() const {return *m_pParent;}

        void AddNode(Node* _pNode);
        void AttachComponent(Component* _pComponent);

        template <typename T> T* AddComponent()
        {
            // Inherite from Gameobject ?
            Derived_from<T, Component>();

            T* created = new T();

            // Add reference to Node in object
            // and steal ownership (see friend Component::SetParent)
            created->SetParent(this);

            return created;
        }

        template <typename T> T* GetComponent() const
        {
            // Inherite from Gameobject ?
            Derived_from<T, Component>();

            // Try to find it
            unsigned int size = m_components.size();
            for (int i = 0; i < size; ++i)
            {
                auto& componentRef = *m_components[i];

                // Return type of base class if not polymorphic
                // else return type of child.
                // A class is polymorphic if it defines a virtual method.
                if (typeid(T) == typeid(componentRef))
                {
                    return dynamic_cast<T*>(m_components[i].get());
                }
            }
            return nullptr;
        }

        template <typename T> T* GetComponents() const
        {
            // Inherite from Gameobject ?
            Derived_from<T, Component>();

            std::vector<T*> listOfComponents;

            // Try to find it
            unsigned int size = m_components.size();
            for (int i = 0; i < size; ++i)
            {
                auto& componentRef = *m_components[i];

                // Return type of base class if not polymorphic
                // else return type of child.
                // A class is polymorphic if it defines a virtual method.
                if (typeid(T) == typeid(componentRef))
                {
                    listOfComponents.push_back(dynamic_cast<T*>(m_components[i].get()));
                }
            }
            return listOfComponents;
        }

        virtual bool Draw();
        virtual bool Update();
        virtual void Clear();
    };

    // Specialization for Transform (must be inlined)
    template<> inline Transform* Node::AddComponent()
    {
        throw TransformException();
    }
}

#endif
