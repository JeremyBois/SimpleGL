#ifndef __NODEMANAGER__HPP
#define __NODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/INodeManager.hpp"
#include "Node.hpp"


namespace simpleGL
{
    // Implemenation of the Node manager interface
    class SIMPLEGL_API NodeManager: public INodeManager
    {
    private:
        Node* m_pRoot;

        static bool instantiated_;

    public:
        NodeManager();
        ~NodeManager();

        virtual void AddNode(Node* _pNode, Node* _pParent=nullptr);
        virtual void Draw();
        virtual void Update();
        virtual void Clear();
    };
}

#endif
