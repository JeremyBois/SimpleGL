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
        Shader  m_baseShader;

    public:
        Shape();
        virtual ~Shape();

        void    SetShader(Shader* _pShader);
        Shader& GetShader() const;
        void    UseDefault();

        virtual void Draw() = 0;
    };
}
#endif
