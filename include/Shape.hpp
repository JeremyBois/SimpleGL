#ifndef __SHAPE__HPP
#define __SHAPE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"


namespace simpleGL
{
    // Abstract class for any shape
    class SIMPLEGL_API Shape: public GameObject
    {
    protected:
        Shader  m_baseShader;

        // Flyweight pattern
        Shader* m_pShader;
        Texture* m_pTexture;

    public:
        Shape();
        virtual ~Shape();

        void     LinkShader(Shader* _pShader);
        void     LinkTexture(Texture* _pTexture);

        Texture& GetTexture() const;
        Shader&  GetShader() const;

        void     UseDefaultShader();

        virtual void Draw() = 0;
    };
}
#endif
