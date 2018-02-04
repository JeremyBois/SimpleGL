#ifndef __SHAPE__HPP
#define __SHAPE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"
#include "OpenGL/Shader.hpp"


namespace simpleGL
{
    // Abstract class for any shape
    class SIMPLEGL_LOCAL Shape: public GameObject
    {
    protected:
        Shader* m_pShader;

    public:
        Shape();
        ~Shape();

        virtual void SetShader(Shader* _pShader);
    };
}
#endif
