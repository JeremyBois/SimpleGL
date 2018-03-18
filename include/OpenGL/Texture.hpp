#ifndef __TEXTURE__HPP
#define __TEXTURE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

#include "glm.hpp"


namespace simpleGL
{
    // Encapsulate a shader program (vertex and fragment shader).
    class SIMPLEGL_API Texture: public GameObject
    {
    private:
        unsigned int m_texID;

        int m_width, m_height, m_nbChannels;

    public:
        Texture() {};  // Allows lazy initialization
        Texture(std::string _path, bool _reverseY=false, bool _correctGamma=false);
        ~Texture();

        // Getter
        inline int TextureID() const {return m_texID;}
        inline int GetWidth() const {return m_width;}
        inline int GetHeight() const {return m_height;}
        inline int GetNbrChannels() const {return m_nbChannels;}
        void       Get(GLenum _param, GLint* _container);
        void       Get(GLenum _param, GLfloat* _container);

        // Setter
        void Load(std::string _path, bool _hasAlpha=false, bool _reverseY=false);
        void Use(GLenum _unit);
        void Set(GLenum _param, const GLint* _values);
        void Set(GLenum _param, const GLint _value);
        void SetBorderColor(glm::vec4 _color);


        virtual void Init() {};
        virtual void Draw() {};
        virtual void Update() {};
        virtual void Quit() {};

        virtual GameObject* Clone() {return new Texture();}
    };
}
#endif
