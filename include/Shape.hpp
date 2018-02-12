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
        // @TODO Flyweight pattern --> Get a reference to it not an instance
        Shader  m_baseShader;

        Shader* m_pShader;

        // Maintain a collection of texture for each unit
        TexUnitMap m_pTextureMap;

        // Transformations
        glm::vec3 m_xAxis, m_yAxis, m_zAxis;
        glm::vec3 m_position;
        glm::vec3 m_scale;

        glm::mat4 m_localToWorld;

        virtual void ConstructModelMatrix() = 0;

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

        // Common transformations
        virtual void SetPosition(glm::vec3 _position);
        virtual void SetScale(glm::vec3 _scale);

        inline         const glm::vec3  GetPosition()    const {return m_position;}
        inline         const glm::vec3  GetScale()       const {return m_scale;}
        inline virtual const glm::mat4& GetModelMatrix() const {return m_localToWorld;};

        virtual void Draw();
    };
}
#endif
