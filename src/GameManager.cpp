#include "GameManager.hpp"
#include "Services/DataManager.hpp"

namespace simpleGL
{
    Window*         GameManager::s_pWindowService;
    INodeMgrPtr     GameManager::s_pNodeService;
    ISceneMgrPtr    GameManager::s_pSceneService;
    IDataMgrPtr     GameManager::s_pDataService;

    // Should be called before anything else
    void GameManager::Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName)
    {
        // Window as an internal service
        s_pWindowService = new Window(_windowWidth, _windowHeight, _windowName);
        s_pWindowService->Init();

        // DataMgr as an internal service
        s_pDataService = IDataMgrPtr(new DataManager());
        s_pDataService->Init();

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
        GetDataMgr().Update();
        GetSceneMgr().Update();
        GetNodeMgr().Update();
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
        GetSceneMgr().Quit();
        GetDataMgr().Quit();
    }

    void GameManager::Render()
    {
        GetDataMgr().Render();
        GetSceneMgr().Render();
        GetNodeMgr().Render();
    }
}
