#ifndef __NULLSCENEMANAGER__HPP
#define __NULLSCENEMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Interface/ISceneManager.hpp"

namespace simpleGL
{
    class IScene;

    // Basic interface the manager must implement
    class SIMPLEGL_LOCAL NullSceneManager: public ISceneManager
    {
    public:
        virtual bool Init() {}
        virtual bool Update() {}
        virtual bool Quit() {}
        virtual void Render() {}

        virtual void    Change(IScene& _scene) {}
        virtual IScene& GetCurrent() {}
    };
}
#endif
