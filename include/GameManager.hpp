#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "OpenGL/Window.hpp"
#include "Interface/INodeManager.hpp"
#include "Interface/NullNodeManager.hpp"

#include "Interface/ISceneManager.hpp"
#include "Interface/NullSceneManager.hpp"

#include <memory>


namespace simpleGL
{
    // Used to steal ownership when a service is attached
    typedef std::unique_ptr<INodeManager>  INodeMgrPtr;
    typedef std::unique_ptr<ISceneManager> ISceneMgrPtr;

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
        static INodeMgrPtr   s_pNodeService;

        // Scene manager as a service
        static ISceneMgrPtr   s_pSceneService;

    public:
        GameManager(GameManager const&)    = delete;  // C++ 11
        void operator=(GameManager const&) = delete;  // C++ 11

        static void Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName);

        static inline INodeManager&  GetNodeMgr() {return *s_pNodeService;}
        static inline ISceneManager& GetSceneMgr() {return *s_pSceneService;}
        static inline Window&        GetWindow() {return *s_pWindowService;}

        static void AttachNodeMgr(INodeManager* _service);
        static void AttachSceneMgr(ISceneManager* _service);

        static void DetachNodeMgr();
        static void DetachSceneMgr();

        static void Update();
        static void Render();
        static void Start();
        static void Quit();
    };
}
#endif
