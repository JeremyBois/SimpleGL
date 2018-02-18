#ifndef __TRANSFORMEXCEPTIONS__HPP
#define __TRANSFORMEXCEPTIONS__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include <exception>

namespace simpleGL
{
    // Exception raised when user try to add a Transform to a Node.
    class SIMPLEGL_LOCAL TransformException: public std::exception
    {
        virtual const char* what() const throw()
        {
          return "Cannot add another Transform to a Node.";
        }
    };
}
#endif
