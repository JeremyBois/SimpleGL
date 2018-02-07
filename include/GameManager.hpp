#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "OpenGL/Window.hpp"
#include "Interface/INodeManager.hpp"
#include "Interface/NullNodeManager.hpp"

#include "Interface/ISceneManager.hpp"
#include "Interface/NullSceneManager.hpp"

namespace simpleGL
{
    // Service locator to provide a global access for different stuff
    // Only Window is an internal service and must be created explicitly using Init().
    // Other can be provide but are not required.
    class SIMPLEGL_API GameManager
    {
    private:
        GameManager();

        // Window as an internal service
        static Window* s_pWindowService;

        // Node manager as a service
        static INodeManager*   s_pNodeService;
        static NullNodeManager s_nullNodeManager;

        // Scene manager as a service
        static ISceneManager*   s_pSceneService;
        static NullSceneManager s_nullSceneManager;

    public:

        static void Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName);

        static inline INodeManager&  GetNodeMgr() {return *s_pNodeService;}
        static inline ISceneManager& GetSceneMgr() {return *s_pSceneService;}
        static inline Window&        GetWindow() {return *s_pWindowService;}


        static void Provide(INodeManager* _service);
        static void Provide(ISceneManager* _service);

        static void Update();
        static void Start();
    };
}
#endif