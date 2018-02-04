#ifndef __NODE__HPP
#define __NODE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

#include <vector>


namespace simpleGL
{
    // Define base class for a component
    // A Node can be a parent of multiple Node
    // A Node can be a parent of a list of GameObject (see GameObject.hpp)
    class SIMPLEGL_API Node
    {
    private:
        std::string m_name;

        // Composite
        Node* m_pParent;
        std::vector<Node*> m_pChildren;
        std::vector<GameObject*> m_pGameObjects;

    public:
        Node();
        ~Node();

        inline std::string GetName() {return m_name;}
        inline void   SetName(std::string _name) {m_name = _name;}
        inline void   SetParent(Node* _pNode){m_pParent = _pNode;}

        void AddGameObject(GameObject* _pGObject);
        void AddNode(Node* _pNode);

        void Draw();
        void Update();
        void Clear();

    };
}

#endif
