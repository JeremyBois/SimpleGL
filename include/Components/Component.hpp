#ifndef __COMPONENT__HPP
#define __COMPONENT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "GameObject.hpp"

namespace simpleGL
{
    class Node;

    class SIMPLEGL_API Component: public GameObject
    {
    protected:
        Node* m_pNode;

        bool m_isActive;

    public:
        Component() {m_isActive = true;};
        virtual ~Component() {};

        virtual bool Init() {};
        virtual bool Draw() = 0;
        virtual bool Update() = 0;
        virtual bool Quit() {};

        virtual Component* Clone() = 0;

        virtual Node& GetNode() {return *m_pNode;}
        virtual void  AttachToNode(Node* _pNode) {m_pNode = _pNode;}

        inline void SetActive(bool _state) {m_isActive = _state;}
        inline bool IsActive() {return m_isActive;}

        // // @TODO Forward and backward inclusion
        // template <typename T> T* GetComponent()
        // {
        //     return GetNode().GetComponent<T>();
        // }
    };
}
#endif
