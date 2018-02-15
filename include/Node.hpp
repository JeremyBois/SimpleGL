#ifndef __NODE__HPP
#define __NODE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Components/Transform.hpp"
#include "Utility/Tools.hpp"

#include <vector>
#include <typeinfo>



namespace simpleGL
{

    typedef std::vector<Component*>   ComponentsList;

    // Define base class for a component
    // A Node can be a parent of multiple Node
    // A Node can be a parent of a list of Component (see Component.hpp)
    class SIMPLEGL_API Node
    {
    private:
        bool        m_isActive;
        std::string m_name;

        // Composite
        Node*              m_pParent;
        Transform*         m_pTransform;
        std::vector<Node*> m_children;
        ComponentsList     m_components;

    public:
        Node();
        ~Node();

        inline void   SetActive(bool _state) {m_isActive = _state;}
        inline void   SetName(std::string _name) {m_name = _name;}
        inline void   SetParent(Node* _pNode){m_pParent = _pNode;}

        inline bool               IsActive() {return m_isActive;}
        inline const std::string& GetName() {return m_name;}
        inline Transform&         GetTransform() {return *m_pTransform;}
        inline Node&              GetParent(){return *m_pParent;}

        void AddNode(Node* _pNode);

        template <typename T> T* AddComponent()
        {
            // Inherite from Gameobject ?
            Derived_from<T, Component>();

            Component* created = new T();

            // Add reference to Node in object
            created->AttachToNode(this);

            m_components.push_back(created);

            return (T*)created;
        }

        template <typename T> T* GetComponent()
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
                    return dynamic_cast<T*>(m_components[i]);
                }
            }
            return nullptr;
        }

        template <typename T> T* GetComponents()
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
                    listOfComponents.push_back(dynamic_cast<T*>(m_components[i]));
                }
            }
            return listOfComponents;
        }

        virtual void Draw();
        virtual void Update();
        virtual void Clear();
        virtual void Destroy();
    };
}

#endif
