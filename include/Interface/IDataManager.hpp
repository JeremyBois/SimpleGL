#ifndef __IDATAMANAGER__HPP
#define __IDATAMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "OpenGL/Material.hpp"
#include "OpenGL/Model.hpp"

#include <unordered_map>
#include <memory>
#include <string>

namespace simpleGL
{
    typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TexContainer;
    typedef TexContainer::iterator TexContainerIt;
    typedef TexContainer::const_iterator TexContainerConstIt;

    typedef std::unordered_map<std::string, std::unique_ptr<Shader>>  ShaderContainer;
    typedef ShaderContainer::iterator  ShaderContainerIt;
    typedef ShaderContainer::const_iterator  ShaderContainerConstIt;

    typedef std::unordered_map<std::string, std::unique_ptr<Material>>  MaterialContainer;
    typedef MaterialContainer::iterator  MaterialContainerIt;
    typedef MaterialContainer::const_iterator  MaterialContainerConstIt;

    typedef std::unordered_map<std::string, std::unique_ptr<Model>> ModelContainer;
    typedef ModelContainer::iterator ModelContainerIt;
    typedef ModelContainer::const_iterator ModelContainerConstIt;

    /// Interface for DataManager implementations
    class SIMPLEGL_LOCAL IDataManager
    {
    public:
        virtual ~IDataManager() = default;

        virtual Shader*   CreateShader(const std::string _name, const std::string _vertexPath,
                                      const std::string _fragPath, bool _overrideIfExist=false) = 0;
        virtual Texture*  CreateTexture(const std::string _name, const std::string _path,
                                       bool _reverseY=false, bool _correctGamma=false, bool _overrideIfExist=false) = 0;
        virtual Material* CreateMaterial(const std::string _name, const std::string _shaderName,
                                         bool _overrideIfExist=false) = 0;
        virtual Model*    CreateModel(const std::string _name, bool _overrideIfExist = false) = 0;

        virtual Shader*   GetShader(const std::string _name) const = 0;
        virtual Texture*  GetTexture(const std::string _name) const = 0;
        virtual Material* GetMaterial(const std::string _name) const = 0;
        virtual Model*    GetModel(const std::string _name) const = 0;

        virtual bool Init() = 0;
        virtual bool Update() = 0;
        virtual bool Render() = 0;
        virtual bool Quit() = 0;
    };
}

#endif
