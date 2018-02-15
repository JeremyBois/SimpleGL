#ifndef __MATERIAL__HPP
#define __MATERIAL__HPP



#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "Components/Transform.hpp"

#include <map>

namespace simpleGL
{
    typedef std::map<GLenum, Texture*> TexUnitMap;

    // Abstract class for any shape
    class SIMPLEGL_API Material: public GameObject
    {
    protected:
        // @TODO Flyweight pattern --> Get a reference to it not an instance
        Shader  m_baseShader;

        Shader* m_pShader;

        // Maintain a collection of texture for each unit
        TexUnitMap m_pTextureMap;

    public:
        Material();
        virtual ~Material();

        // Shader
        void     LinkShader(Shader* _pShader);
        Shader&  GetShader() const;
        void     UseDefaultShader();

        // Texture
        void     LinkTexture(Texture* _pTexture, GLenum _unit=GL_TEXTURE0);
        Texture& GetTexture(GLenum _unit=GL_TEXTURE0) const;
        void     UnLinkTexture(GLenum _unit);
        void     UnLinkAllTextures();

        void     Use(const Transform& _transform);
    };
}
#endif
