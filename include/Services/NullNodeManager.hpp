#ifndef __NULLNODEMANAGER__HPP
#define __NULLNODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/INodeManager.hpp"


namespace simpleGL
{
    class Node;

    /// Placeholder for the Node manager (Null pattern).
    class SIMPLEGL_LOCAL NullNodeManager: public INodeManager
    {
    public:
        virtual void AddNode(Node* _pNode, Node* _pParent) {};
        virtual Node* CreateNode(Node* _pParent=nullptr) { return nullptr;};

        virtual void Init() {};
        virtual void Render() {};
        virtual void Update() {};
        virtual void Clear() {};
    };
}

#endif
