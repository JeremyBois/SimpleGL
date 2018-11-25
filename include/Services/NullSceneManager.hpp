#ifndef __NULLSCENEMANAGER__HPP
#define __NULLSCENEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Interface/ISceneManager.hpp"

namespace simpleGL
{
    class IScene;

    /// Placeholder for the Scene manager (Null pattern).
    class SIMPLEGL_LOCAL NullSceneManager: public ISceneManager
    {
    public:
        virtual bool Init() {return true;}
        virtual bool Update() {return true;}
        virtual bool Quit() {return true;}
        virtual void Render() {}

        virtual void    Change(IScene* _pScene) {}
        virtual IScene* GetCurrent() {return nullptr;}
    };
}
#endif
