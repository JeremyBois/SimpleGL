#ifndef __IWINDOW__HPP
#define __IWINDOW__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition


namespace simpleGL
{
    /// Interface for Window implementations
    class SIMPLEGL_LOCAL IWindow
    {
    public:

        virtual bool Init() = 0;
        virtual bool Update() = 0;
        virtual bool Quit() = 0;
        virtual void Render() = 0;

        // A constant reference
        virtual GLFWwindow& GetGLFWwindow() const = 0;
    };
}
#endif
