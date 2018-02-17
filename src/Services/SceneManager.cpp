
#include "Services/SceneManager.hpp"


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
    }


    bool SceneManager::Update()
    {
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
    }


    bool SceneManager::Quit()
    {
        m_pCurrent->OnQuit();
    }


    void SceneManager::Render()
    {
        m_pCurrent->OnRender();
    }


    void SceneManager::ToNext()
    {
        m_pCurrent->OnQuit();
        m_pNext->OnInit();

        delete m_pCurrent;
        m_pCurrent = m_pNext;

        m_pNext = nullptr;
        m_transitionToNext = false;
    }

    void SceneManager::ToPrevious()
    {
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

    void SceneManager::Change(IScene& _scene)
    {
        m_transitionToNext = true;
        m_pNext = &_scene;

        delete m_pPrevious;
        m_pPrevious = m_pCurrent;
    }

    IScene* SceneManager::GetCurrent()
    {
        return m_pCurrent;
    }


}
