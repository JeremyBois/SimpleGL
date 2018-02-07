#ifndef __SCENEFSM__HPP
#define __SCENEFSM__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Interface/IScene.hpp"
#include "Interface/ISceneManager.hpp"

namespace simpleGL
{
    // Basic interface the manager must implement
    class SIMPLEGL_API SceneFSM: public ISceneManager
    {
    protected:
        bool m_transitionToNext;
        bool m_transitionToPrevious;

        IScene* m_pCurrent;
        IScene* m_pPrevious;
        IScene* m_pNext;

        void ToNext();
        void ToPrevious();

    public:
        SceneFSM(IScene& _startScene);
        ~SceneFSM();

        virtual bool Init();
        virtual bool Update();
        virtual bool Quit();
        virtual void Render();

        virtual void    Change(IScene& _scene);
        virtual IScene& GetCurrent();

        virtual void Revert();
    };
}
#endif
