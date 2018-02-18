#ifndef __COMPONENT__HPP
#define __COMPONENT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "GameObject.hpp"

namespace simpleGL
{
    class Node;

    /// Abstract class for every component attached to a Node.
    class SIMPLEGL_API Component: public GameObject
    {
    protected:
        Node* m_pNode;

    public:
        Component();
        virtual ~Component() = default;

        virtual bool Init() = 0;
        virtual bool Draw() = 0;
        virtual bool Update() = 0;
        virtual bool Quit() = 0;

        virtual Component* Clone() = 0;

        virtual Node& GetNode() {return *m_pNode;}
        virtual bool  SetParent(Node* _pNode);
    };
}
#endif
