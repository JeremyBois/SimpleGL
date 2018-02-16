#include "GameManager.hpp"


namespace simpleGL
{
    Window*         GameManager::s_pWindowService;
    INodeMgrPtr     GameManager::s_pNodeService;
    ISceneMgrPtr    GameManager::s_pSceneService;

    // Should be called before anything else
    void GameManager::Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName)
    {
        // Internal service
        s_pWindowService = new Window(_windowWidth, _windowHeight, _windowName);
        s_pWindowService->Init();

        // Null pattern
        s_pNodeService = INodeMgrPtr(new NullNodeManager());
        s_pSceneService = ISceneMgrPtr(new NullSceneManager());
    }

    void GameManager::DetachNodeMgr()
    {
        s_pNodeService.reset(new NullNodeManager());
    }

    void GameManager::DetachSceneMgr()
    {
        s_pSceneService.reset(new NullSceneManager());
    }

    void GameManager::AttachNodeMgr(INodeManager* _service)
    {
        if (_service == nullptr)
        {
            s_pNodeService.reset(new NullNodeManager());
        }
        else
        {
            s_pNodeService.reset(_service);
        }
    }

    void GameManager::AttachSceneMgr(ISceneManager* _service)
    {
        if (_service == nullptr)
        {
            s_pSceneService.reset(new NullSceneManager());
        }
        else
        {
            s_pSceneService.reset(_service);
        }
    }

    // Reset services if needed
    void GameManager::Update()
    {
        GameManager::GetSceneMgr().Update();
        GameManager::GetNodeMgr().Update();
    }

    void GameManager::Start()
    {
        s_pSceneService->Init();
        s_pNodeService->Init();
        s_pWindowService->Update();
        s_pWindowService->Quit();
    }

    void GameManager::Quit()
    {
        GameManager::GetSceneMgr().Quit();
    }

    void GameManager::Render()
    {
        GameManager::GetSceneMgr().Render();
        GameManager::GetNodeMgr().Render();
    }
}
