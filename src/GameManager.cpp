#include "GameManager.hpp"


namespace simpleGL
{
    // Should be defined
    Window*         GameManager::s_pWindowService;

    INodeManager*   GameManager::s_pNodeService;
    NullNodeManager GameManager::s_nullNodeManager = NullNodeManager();

    ISceneManager*   GameManager::s_pSceneService;
    NullSceneManager GameManager::s_nullSceneManager = NullSceneManager();

    // Should be called before anything else
    void GameManager::Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName)
    {
        // Internal service
        s_pWindowService = new Window(_windowWidth, _windowHeight, _windowName);
        s_pWindowService->Init();

        // Null pattern
        s_pNodeService = &s_nullNodeManager;
        s_pSceneService = &s_nullSceneManager;
    }

    void GameManager::Provide(INodeManager* _service)
    {
        if (_service == nullptr)
        {
            s_pNodeService = &s_nullNodeManager;
        }
        else
        {
            s_pNodeService = _service;
        }
    }

    void GameManager::Provide(ISceneManager* _service)
    {
        if (_service == nullptr)
        {
            s_pSceneService = &s_nullSceneManager;
        }
        else
        {
            s_pSceneService = _service;
        }
    }

    // Reset services if needed
    void GameManager::Update()
    {
        if (!s_pSceneService)
        {
            s_pSceneService = &s_nullSceneManager;
        }

        if (!s_pNodeService)
        {
            s_pNodeService = &s_nullNodeManager;
        }
    }

    void GameManager::Start()
    {
        s_pSceneService->Init();
        s_pNodeService->Init();
        s_pWindowService->Update();
        s_pWindowService->Quit();
    }
}
