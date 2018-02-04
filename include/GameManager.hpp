#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "OpenGL/Window.hpp"
#include "NodeManager.hpp"

namespace simpleGL
{
    // Singleton representing the global interface for the game.
    class SIMPLEGL_API GameManager
    {
    private:
        GameManager();

        Window*      m_pWindow;
        NodeManager* m_pNodeManager;

    public:
        GameManager(GameManager const&) = delete;    // C++ 11
        void operator=(GameManager const&) = delete; // C++ 11

        void Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName);

        // Provide unique access to specific stuff
        inline Window&      GetWindow() {return *m_pWindow;}
        inline NodeManager& GetNodeManager() {return *m_pNodeManager;}

        static GameManager* Instance();

    };
}
#endif
