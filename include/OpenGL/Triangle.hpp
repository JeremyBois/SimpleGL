#ifndef __TRIANGLE__HPP
#define __TRIANGLE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Shape2D.hpp"


namespace simpleGL
{
    // Can be used to construct and draw a triangle
    class SIMPLEGL_API Triangle: public Shape2D
    {

    public:
        Triangle();
        ~Triangle();
    };
}
#endif
