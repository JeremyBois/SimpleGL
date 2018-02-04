#include "GameManager.hpp"


namespace simpleGL
{

    GameManager::GameManager()
    {
        m_pWindow = nullptr;
        m_pNodeManager = nullptr;
    }

    void GameManager::Init(unsigned int _windowWidth, unsigned int _windowHeight, std::string _windowName)
    {
        m_pWindow = new Window(_windowWidth, _windowHeight, _windowName);
        m_pWindow->Init();

        m_pNodeManager = new NodeManager();
    }

    GameManager* GameManager::Instance()
    {
        static GameManager instance_;
        return &instance_;
    }
}
