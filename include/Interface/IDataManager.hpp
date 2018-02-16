#ifndef __IDATAMANAGER__HPP
#define __IDATAMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition

#include <unordered_map>
#include <memory>
#include <string>

namespace simpleGL
{
    class Texture;
    class Shader;


    typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TexContainer;
    typedef TexContainer::iterator TexContainerIt;
    typedef TexContainer::const_iterator TexContainerConstIt;

    typedef std::unordered_map<std::string, std::unique_ptr<Shader>>  ShaderContainer;
    typedef ShaderContainer::iterator  ShaderContainerIt;
    typedef ShaderContainer::const_iterator  ShaderContainerConstIt;


    /// Interface for DataManager implementations
    class SIMPLEGL_LOCAL IDataManager
    {
    public:
        virtual ~IDataManager() = default;

        virtual Shader*  CreateShader(const std::string _name, const std::string _vertexPath,
                                      const std::string _fragPath, bool _overrideIfExist=false) = 0;
        virtual Texture* CreateTexture(const std::string _name, const std::string _path,
                                       bool _overrideIfExist=false) = 0;

        virtual Shader*  GetShader(const std::string _name) = 0;
        virtual Texture* GetTexture(const std::string _name) = 0;
    };
}

#endif
