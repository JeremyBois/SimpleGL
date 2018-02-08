#ifndef __TEXTURE__HPP
#define __TEXTURE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include "Utility/Tools.hpp"
#include "GameObject.hpp"

namespace simpleGL
{
    // Encapsulate a shader program (vertex and fragment shader).
    class SIMPLEGL_API Texture: public GameObject
    {
    private:
        unsigned int m_id;

        int m_width, m_height, m_nbChannels;

    public:
        Texture() {};  // Allows lazy initialization
        Texture(std::string _path);
        ~Texture();

        // Getter
        inline int GetWidth() {return m_width;}
        inline int GetHeight() {return m_height;}
        inline int GetNbrChannels() {return m_nbChannels;}

        // Setter
        void Load(std::string _path);
        void Use();
        void Set(GLenum _param, const GLint* _values);
        void SetBorderColor(GL_COLOR4 _color);


        virtual void Init() {};
        virtual void Draw() {};
        virtual void Update() {};
        virtual void Quit() {};

        virtual GameObject* Clone() {return new Texture();}
    };
}
#endif
