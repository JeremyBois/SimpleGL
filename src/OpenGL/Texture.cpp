#include "OpenGL/Texture.hpp"

#include "stb_image.h"


namespace simpleGL
{

    Texture::Texture(std::string _path, bool _hasAlpha, bool _reverseY)
    {
        Load(_path, _hasAlpha, _reverseY);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_texID);
    }

    void Texture::Get(GLenum _param, GLint* _container)
    {
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glGetTexParameteriv(GL_TEXTURE_2D, _param, _container);
    }

    void Texture::Get(GLenum _param, GLfloat* _container)
    {
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glGetTexParameterfv(GL_TEXTURE_2D, _param, _container);
    }

    void Texture::Set(GLenum _param, const GLint* _values)
    {
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexParameteri(GL_TEXTURE_2D, _param, *_values);
    }

    void Texture::Set(GLenum _param, const GLint _value)
    {
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexParameteri(GL_TEXTURE_2D, _param, _value);
    }

    /// _correctGamma should be set to true when you want OpenGl to applied correction
    /// on the texture colors (assume texture in sRGB which is usually the case)
    void Texture::Load(std::string _path, bool _reverseY, bool _correctGamma)
    {
        glGenTextures(1, &m_texID);
        glBindTexture(GL_TEXTURE_2D, m_texID);

        if (_reverseY)
        {
            stbi_set_flip_vertically_on_load(true);
        }
        else
        {
            stbi_set_flip_vertically_on_load(false);
        }

        unsigned char *data = stbi_load(_path.c_str(),
                                        &m_width, &m_height,
                                        &m_nbChannels, 0);
        if (data)
        {
            // Assign correct format based on number of channels and gamma correction
            GLenum internalformat;
            GLenum format;

            if (m_nbChannels == 1)
            {
                internalformat = format = GL_RED;
            }
            else if (m_nbChannels == 3)
            {
                internalformat = _correctGamma ? GL_SRGB : GL_RGB;
                format = GL_RGB;
            }
            else if (m_nbChannels == 4)
            {
                internalformat = _correctGamma ? GL_SRGB_ALPHA : GL_RGBA;
                format = GL_RGBA;
            }
            else
            {
                std::cerr << "ERROR::TEXTURE::FAILED TO SELECT FORMAT" << std::endl;
            }


            glTexImage2D(GL_TEXTURE_2D, 0, internalformat,
                         m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

            // Construct mipmap
            glGenerateMipmap(GL_TEXTURE_2D);

            // Default wrapping and filtering
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            std::cerr << "ERROR::TEXTURE::FAILED TO LOAD TEXTURE" << std::endl;
        }
        stbi_image_free(data);
    }

    // Bind texture to a specific unit
    // Default to first one (GL_TEXTURE0)
    void Texture::Use(GLenum _unit)
    {
        glActiveTexture(_unit);
        glBindTexture(GL_TEXTURE_2D, m_texID);
    }


    void Texture::SetBorderColor(glm::vec4 _color)
    {
        glBindTexture(GL_TEXTURE_2D, m_texID);
        float borderColor[] = {_color.r, _color.g, _color.b, _color.a};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
}

