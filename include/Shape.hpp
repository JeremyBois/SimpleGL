#ifndef __SHAPE__HPP
#define __SHAPE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

namespace simpleGL
{
    // Abstract class for any shape
    class SIMPLEGL_API Shape: public GameObject
    {
    public:
        Shape();
        virtual ~Shape();

        virtual void Draw();
    };
}
#endif
