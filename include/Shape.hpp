#ifndef __SHAPE__HPP
#define __SHAPE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"

#include <map>

namespace simpleGL
{
    typedef std::map<GLenum, Texture*> TexUnitMap;

    // Abstract class for any shape
    class SIMPLEGL_API Shape: public GameObject
    {
    protected:
        Shader  m_baseShader;

        // Flyweight pattern
        Shader* m_pShader;

        // Maintain a collection of texture for each unit
        TexUnitMap m_pTextureMap;

        // Helpers
        glm::vec3 m_xAxis, m_yAxis, m_zAxis;
        glm::mat4 m_localToWorld;


    public:
        Shape();
        virtual ~Shape();

        // Shader
        void     LinkShader(Shader* _pShader);
        Shader&  GetShader() const;
        void     UseDefaultShader();

        // Texture
        void     LinkTexture(Texture* _pTexture, GLenum _unit=GL_TEXTURE0);
        Texture& GetTexture(GLenum _unit=GL_TEXTURE0) const;
        void     UnLinkTexture(GLenum _unit);
        void     UnLinkAllTextures();

        virtual void Draw();
    };
}
#endif
