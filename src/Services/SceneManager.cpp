
#include "Services/SceneManager.hpp"
#include "GameManager.hpp"

namespace simpleGL
{
    SceneManager::SceneManager(IScene& _startScene)
        : m_transitionToNext(false), m_transitionToPrevious(false),
          m_pCurrent(&_startScene), m_pPrevious(nullptr), m_pNext(nullptr)
    {

    }

    SceneManager::~SceneManager()
    {
        delete m_pCurrent;
        delete m_pPrevious;
        delete m_pNext;
    }

    bool SceneManager::Init()
    {
        m_pCurrent->OnInit();
        return true;
    }


    bool SceneManager::Update()
    {
        m_pCurrent->ProcessInput();
        m_pCurrent->OnUpdate();

        // Change must occurs after current scene update ended
        // to avoid calls to deleted elements
        if (m_transitionToNext)
        {
            ToNext();
        }
        else if(m_transitionToPrevious)
        {
            ToPrevious();
        }

        return true;
    }


    bool SceneManager::Quit()
    {
        m_pCurrent->OnQuit();
        return true;
    }


    void SceneManager::Render()
    {
        m_pCurrent->OnRender();
    }


    void SceneManager::ToNext()
    {
        // Make sure camera pointer is reset
        GameManager::GetWindow().mainCam = nullptr;

        if (m_pCurrent)
        {
            m_pCurrent->OnQuit();
            // m_pPrevious still point to current
            // to be able to go to previous scene
            m_pCurrent = m_pNext;
        }
        m_pCurrent->OnInit();

        m_pNext = nullptr;
        m_transitionToNext = false;
    }

    void SceneManager::ToPrevious()
    {
        // Make sure camera pointer is reset
        GameManager::GetWindow().mainCam = nullptr;

        m_pCurrent->OnQuit();
        m_pPrevious->OnInit();

        IScene* temp = m_pPrevious;
        m_pPrevious = m_pCurrent;
        m_pCurrent = temp;

        m_transitionToNext = false;
    }


    void SceneManager::Revert()
    {
        if (m_pPrevious != nullptr)
        {
            m_transitionToPrevious = true;
        }
    }

    void SceneManager::Change(IScene* _pScene)
    {
        m_transitionToNext = true;
        m_pNext = _pScene;

        delete m_pPrevious;
        m_pPrevious = m_pCurrent;
    }

    IScene* SceneManager::GetCurrent()
    {
        return m_pCurrent;
    }


}
