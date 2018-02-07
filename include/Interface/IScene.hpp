#ifndef __ISCENE__HPP
#define __ISCENE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition


namespace simpleGL
{
    class SIMPLEGL_API IScene
    {
    public:
        IScene(){};
        virtual ~IScene(){};

        virtual bool OnInit() = 0;
        virtual bool OnUpdate() = 0;
        virtual bool OnQuit() = 0;
        virtual void OnRender() = 0;
    };
}
#endif
