
#include "SceneFSM.hpp"


namespace simpleGL
{
    SceneFSM::SceneFSM(IScene& _startScene)
        : m_transitionToNext(false), m_transitionToPrevious(false),
          m_pCurrent(&_startScene), m_pPrevious(nullptr), m_pNext(nullptr)
    {

    }

    SceneFSM::~SceneFSM()
    {
        delete m_pCurrent;
        delete m_pPrevious;
        delete m_pNext;
    }

    bool SceneFSM::Init()
    {
        m_pCurrent->OnInit();
    }


    bool SceneFSM::Update()
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


    bool SceneFSM::Quit()
    {
        m_pCurrent->OnQuit();
    }


    void SceneFSM::Render()
    {
        m_pCurrent->OnRender();
    }


    void SceneFSM::ToNext()
    {
        m_pCurrent->OnQuit();
        m_pNext->OnInit();

        delete m_pCurrent;
        m_pCurrent = m_pNext;

        m_pNext = nullptr;
        m_transitionToNext = false;
    }

    void SceneFSM::ToPrevious()
    {
        m_pCurrent->OnQuit();
        m_pPrevious->OnInit();

        IScene* temp = m_pPrevious;
        m_pPrevious = m_pCurrent;
        m_pCurrent = temp;

        m_transitionToNext = false;
    }


    void SceneFSM::Revert()
    {
        if (m_pPrevious != nullptr)
        {
            m_transitionToPrevious = true;
        }
    }

    void SceneFSM::Change(IScene& _scene)
    {
        m_transitionToNext = true;
        m_pNext = &_scene;

        delete m_pPrevious;
        m_pPrevious = m_pCurrent;
    }

    IScene& SceneFSM::GetCurrent()
    {
        return *m_pCurrent;
    }


}
