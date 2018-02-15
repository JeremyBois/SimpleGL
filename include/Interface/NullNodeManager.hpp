#ifndef __NULLNODEMANAGER__HPP
#define __NULLNODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/INodeManager.hpp"


namespace simpleGL
{
    class Node;

    // Placeholder for the Node manager
    class SIMPLEGL_LOCAL NullNodeManager: public INodeManager
    {
    public:
        virtual void AddNode(Node* _pNode, Node* _pParent) {};
        virtual void Init() {};
        virtual void Render() {};
        virtual void Update() {};
        virtual void Clear() {};
        virtual void Destroy() {};
    };
}

#endif
