#include "Services/DataManager.hpp"
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
            m_shaders[_name] = std::unique_ptr<Shader>(new Shader(_vertexPath, _fragPath));
            return m_shaders[_name].get();
        }

        ShaderContainerIt it = m_shaders.find(_name);
        if (it == m_shaders.end())
        {
            m_shaders.emplace(_name, std::unique_ptr<Shader>(new Shader(_vertexPath, _fragPath)));
            return m_shaders[_name].get();
        }

        return nullptr;
    }

    Texture* DataManager::CreateTexture(const std::string _name, const std::string _path,
                                        bool _reverseY, bool _correctGamma, bool _overrideIfExist)
    {
        if (_overrideIfExist)
        {
            m_textures[_name] = std::unique_ptr<Texture>(new Texture(_path, _reverseY, _correctGamma));
            return m_textures[_name].get();
        }

        TexContainerIt it = m_textures.find(_name);
        if (it == m_textures.end())
        {
            m_textures.emplace(_name, std::unique_ptr<Texture>(new Texture(_path, _reverseY, _correctGamma)));
            return m_textures[_name].get();
        }

        return nullptr;
    }

    /// Create a material and link a shader.
    Material* DataManager::CreateMaterial(const std::string _name, const std::string _shaderName,
                                          bool _overrideIfExist)
    {
        Shader* pShader = GetShader(_shaderName);
        Material* pMat = nullptr;

        if (_overrideIfExist)
        {
            m_materials[_name] = std::unique_ptr<Material>(new Material());
            pMat = GetMaterial(_name);
            pMat->LinkShader(pShader);
        }
        else
        {
            MaterialContainerIt it = m_materials.find(_name);
            if (it == m_materials.end())
            {
                m_materials.emplace(_name, std::unique_ptr<Material>(new Material()));
                pMat = GetMaterial(_name);
                pMat->LinkShader(pShader);
            }
        }

        return pMat;
    }

    Model *DataManager::CreateModel(const std::string _name, bool _overrideIfExist)
    {
        return nullptr;
    }

    /// Raise out_of_range exception if Shader does not exists
    Shader*  DataManager::GetShader(const std::string _name) const
    {
        return m_shaders.at(_name).get();
    }

    /// Raise out_of_range exception if Texture does not exists
    Texture* DataManager::GetTexture(const std::string _name) const
    {
        return m_textures.at(_name).get();
    }

    /// Raise out_of_range exception if material does not exists
    Material* DataManager::GetMaterial(const std::string _name) const
    {
        return m_materials.at(_name).get();
    }

    /// Raise out_of_range exception if material does not exists
    Model *DataManager::GetModel(const std::string _name) const
    {
        return m_models.at(_name).get();
    }

    /// Populate container with basic stuff.
    bool DataManager::Init()
    {
        // Default textures
        CreateTexture("White", "data/images/white.jpg");
        CreateTexture("Black", "data/images/black.jpg");

        CreateShader("Default", "shaders/basic.vert", "shaders/basic.frag");
        CreateMaterial("Default", "Default");

        CreateShader("LightGizmo", "shaders/lightGizmo.vert", "shaders/lightGizmo.frag");
        CreateMaterial("LightGizmo", "LightGizmo");


        return true;
    }

    bool DataManager::Update()
    {
        return true;
    }

    bool DataManager::Render()
    {
        return true;
    }

    bool DataManager::Quit()
    {
        return true;
    }

}
