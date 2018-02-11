#include "OpenGL/Texture.hpp"

#include "stb_image.h"


namespace simpleGL
{

    Texture::Texture(std::string _path)
    {
        Load(_path);
    }

    Texture::~Texture()
    {

    }

    void Texture::Get(GLenum _param, GLint* _container)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glGetTexParameteriv(GL_TEXTURE_2D, _param, _container);
    }

    void Texture::Get(GLenum _param, GLfloat* _container)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glGetTexParameterfv(GL_TEXTURE_2D, _param, _container);
    }

    void Texture::Set(GLenum _param, const GLint* _values)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, _param, *_values);
    }

    void Texture::Set(GLenum _param, const GLint _value)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, _param, _value);
    }

    void Texture::Load(std::string _path, bool _hasAlpha, bool _reverseY)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        // Default wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
            GLenum format = _hasAlpha ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format,
                         m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

            // Construct mipmap
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "ERROR::TEXTURE::FAILED TO LOAD TEXTURE" << std::endl;
        }
        stbi_image_free(data);
    }

    // Bind texture to a specific unit
    // Default to first one (GL_TEXTURE0)
    void Texture::Use(GLenum _unit)
    {
        glActiveTexture(_unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }


    void Texture::SetBorderColor(GL_COLOR4 _color)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        float borderColor[] = {_color.r, _color.g, _color.b, _color.a};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
}

