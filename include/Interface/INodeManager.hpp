#ifndef __INODEMANAGER__HPP
#define __INODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{
    class Node;

    // Interface for NodeManager implementations
    class SIMPLEGL_LOCAL INodeManager
    {
    public:
        virtual void AddNode(Node* _pNode, Node* _pParent=nullptr) = 0;
        virtual void Init() = 0;
        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void Clear() = 0;
    };
}

#endif
