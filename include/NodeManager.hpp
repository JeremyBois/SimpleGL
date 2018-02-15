#ifndef __NODEMANAGER__HPP
#define __NODEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/INodeManager.hpp"
#include "Node.hpp"


namespace simpleGL
{
    // @TODO Implement as Scene graph
    // @TODO see https://stackoverflow.com/questions/5319282/game-engines-what-are-scene-graphs#5319558
    // @TODO     https://en.wikipedia.org/wiki/Scene_graph)

    // Implemenation of the Node manager interface
    class SIMPLEGL_API NodeManager: public INodeManager
    {
    private:
        Node m_root;

    public:
        NodeManager();
        ~NodeManager();

        virtual void AddNode(Node* _pNode, Node* _pParent=nullptr);
        virtual void Init() {};
        virtual void Render();
        virtual void Update();
        virtual void Clear();
    };
}

#endif
