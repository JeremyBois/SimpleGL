#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

namespace simpleGL
{

    // Abstract class for any game object (sprite, text, shape, ...)
    // Define minimal interface to implement for all
    class SIMPLEGL_API GameObject
    {
    private:
        static unsigned int s_nextID;

    protected:
        unsigned int m_id;

    public:
        GameObject();
        virtual ~GameObject();

        unsigned int GetID() {return m_id;}
    };
}
#endif
