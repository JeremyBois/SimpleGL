#ifndef __ISCENEMANAGER__HPP
#define __ISCENEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Interface/IScene.hpp"

namespace simpleGL
{
    /// Interface for SceneManager implementations
    class SIMPLEGL_LOCAL ISceneManager
    {
    public:
        virtual bool Init() = 0;
        virtual bool Update() = 0;
        virtual bool Quit() = 0;
        virtual void Render() = 0;

        virtual void    Change(IScene* _pScene) = 0;
        virtual IScene* GetCurrent() = 0;
    };
}
#endif
