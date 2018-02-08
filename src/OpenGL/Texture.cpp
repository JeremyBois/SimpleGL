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

    void Texture::Set(GLenum _param, const GLint* _values)
    {
        Use();
        glTexParameteri(GL_TEXTURE_2D, _param, *_values);
    }

    // Setter
    void Texture::Load(std::string _path)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        // Default wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        unsigned char *data = stbi_load(_path.c_str(),
                                        &m_width, &m_height,
                                        &m_nbChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            // Construct mipmap
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "ERROR::TEXTURE::FAILED TO LOAD TEXTURE" << std::endl;
        }
        stbi_image_free(data);
    }

    void Texture::Use()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }


    void Texture::SetBorderColor(GL_COLOR4 _color)
    {
        Use();
        float borderColor[] = {_color.r, _color.g, _color.b, _color.a};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
                         borderColor);
    }
}

