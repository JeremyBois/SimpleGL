#include "DataManager.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"

#include <iostream>


namespace simpleGL
{
    Shader*  DataManager::CreateShader(const std::string _name, const std::string _vertexPath,
                                       const std::string _fragPath, bool _overrideIfExist)
    {
        if (_overrideIfExist)
        {
            m_pShaders[_name] = std::unique_ptr<Shader>(new Shader(_vertexPath, _fragPath));
            return m_pShaders[_name].get();
        }

        ShaderContainerIt it = m_pShaders.find(_name);
        if (it != m_pShaders.end())
        {
            m_pShaders.emplace(_name, std::unique_ptr<Shader>(new Shader(_vertexPath, _fragPath)));
            return m_pShaders[_name].get();
        }

        return nullptr;
    }

    Texture* DataManager::CreateTexture(const std::string _name, const std::string _path,
                                        bool _overrideIfExist)
    {
        if (_overrideIfExist)
        {
            m_pTextures[_name] = std::unique_ptr<Texture>(new Texture(_path));
            return m_pTextures[_name].get();
        }

        TexContainerIt it = m_pTextures.find(_name);
        if (it != m_pTextures.end())
        {
            m_pTextures.emplace(_name, std::unique_ptr<Texture>(new Texture(_path)));
            return m_pTextures[_name].get();
        }

        return nullptr;
    }


    Shader*  DataManager::GetShader(const std::string _name)
    {
        Shader* pShader = nullptr;
        try
        {
            pShader = m_pShaders.at(_name).get();
        }
        catch (std::out_of_range)
        {
            pShader = nullptr;
        }

        return pShader;
    }


    Texture* DataManager::GetTexture(const std::string _name)
    {
        Texture* pTex = nullptr;
        try
        {
            pTex = m_pTextures.at(_name).get();
        }
        catch (std::out_of_range)
        {
            pTex = nullptr;
        }

        return pTex;
    }
}
