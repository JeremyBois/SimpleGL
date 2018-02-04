#ifndef __NODEMANAGER__HPP
#define __NODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Node.hpp"


namespace simpleGL
{
    // Define a common entry to control nodes tree.
    class SIMPLEGL_API NodeManager
    {
    private:
        Node* m_pRoot;

        static bool instantiated_;

    public:
        NodeManager();
        ~NodeManager();

        void AddNode(Node* _pNode, Node* _pParent);
        void Draw();
        void Update();
        void Clear();
    };
}

#endif
