#ifndef __TEXTURE__HPP
#define __TEXTURE__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"

#include "glm.hpp"

namespace simpleGL
{

    // Mirror assimp types
    enum TextureType
    {
        TextureType_NONE         = 0x0,
        TextureType_DIFFUSE      = 0x1,
        TextureType_SPECULAR     = 0x2,
        TextureType_AMBIENT      = 0x3,
        TextureType_EMISSIVE     = 0x4,
        TextureType_HEIGHT       = 0x5,
        TextureType_NORMALS      = 0x6,
        TextureType_SHININESS    = 0x7,
        TextureType_OPACITY      = 0x8,
        TextureType_DISPLACEMENT = 0x9,
        TextureType_LIGHTMAP     = 0xA,
        TextureType_REFLECTION   = 0xB,
        TextureType_UNKNOWN      = 0xC
    };

    /// Abstraction of an Image (texture).
    class SIMPLEGL_API Texture : public GameObject
    {
    private:
        unsigned int m_texID;

        int m_width, m_height, m_nbChannels;


    public:
        Texture(){}; // Allows lazy initialization
        Texture(std::string _path, bool _reverseY = false, bool _correctGamma = false);
        ~Texture();

        // Getter
        inline int TextureID() const { return m_texID; }
        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }
        inline int GetNbrChannels() const { return m_nbChannels; }
        void Get(GLenum _param, GLint *_container);
        void Get(GLenum _param, GLfloat *_container);

        // Setter
        void Load(std::string _path, bool _hasAlpha = false, bool _reverseY = false);
        void Use(GLenum _unit);
        void Set(GLenum _param, const GLint *_values);
        void Set(GLenum _param, const GLint _value);
        void SetBorderColor(glm::vec4 _color);

        virtual void Init(){};
        virtual void Draw(){};
        virtual void Update(){};
        virtual void Quit(){};

        virtual GameObject *Clone() { return new Texture(); }

    private:
        // Needed when passing texture to shader (name convention)
        static std::string GetTypeName(const Texture &texture) noexcept;
    };
}
#endif
