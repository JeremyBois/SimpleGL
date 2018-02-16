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

        bool m_isActive;

    public:
        GameObject();
        virtual ~GameObject();

        inline unsigned int GetID() {return m_id;}
        inline void SetActive(bool _state) {m_isActive = _state;}
        inline bool IsActive() {return m_isActive;}
    };
}
#endif
