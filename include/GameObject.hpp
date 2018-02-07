#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{
    // @TODO Must be implement using an interface ?
    // Abstract class for any game object (sprite, text, shape, ...)
    // Define minimal interface to implement for all
    class SIMPLEGL_LOCAL GameObject
    {
    public:
        GameObject();
        ~GameObject();

        virtual void Init() = 0;
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void Quit() = 0;

        virtual GameObject* Clone() = 0;
    };
}
#endif
