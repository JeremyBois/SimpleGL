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

        // Colors
        glm::vec3 m_ambient, m_diffuse, m_specular;
        float m_shininess, m_glossiness;


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


        // Color
        inline glm::vec3 GetAmbient() const {return m_ambient;}
        inline glm::vec3 GetDiffuse() const {return m_diffuse;}
        inline glm::vec3 GetSpecular() const {return m_specular;}
        inline float     GetShininess() const {return m_shininess;}
        inline float     GetGlossiness() const {return m_glossiness;}

        inline void SetAmbient(glm::vec3 _ambient) {m_ambient = _ambient;}
        inline void SetDiffuse(glm::vec3 _diffuse) {m_diffuse = _diffuse;}
        inline void SetSpecular(glm::vec3 _specular) {m_specular = _specular;}
        inline void SetShininess(float _shininess) {m_shininess = _shininess;}
        inline void SetGlossiness(float _glossiness) {m_glossiness = _glossiness;}

        // Send data to shader
        void     Use(const Transform& _transform);
    };
}
#endif
