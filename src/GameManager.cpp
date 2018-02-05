#include "GameManager.hpp"


namespace simpleGL
{
    // Should be defined
    Window*         GameManager::s_pWindowService;
    INodeManager*   GameManager::s_pNodeService;

    NullNodeManager GameManager::s_nullNodeManager = NullNodeManager();

    void GameManager::Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName)
    {
        // Internal service
        s_pWindowService = new Window(_windowWidth, _windowHeight, _windowName);
        s_pWindowService->Init();

        // Null pattern
        s_pNodeService = &s_nullNodeManager;
    }

    // GameManager* GameManager::Instance()
    // {
    //     static GameManager instance_;
    //     return &instance_;
    // }

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

    //  void GameManager::Provide(IWindow* _service)
    // {
    //     if (_service == nullptr)
    //     {
    //         s_pWindowService = nullptr;
    //     }
    //     else
    //     {
    //         s_pWindowService = _service;
    //     }
    // }
}
