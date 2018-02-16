#ifndef __DATAMANAGER__HPP
#define __DATAMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/IDataManager.hpp"

namespace simpleGL
{
    /// Interface for DataManager implementations
    class SIMPLEGL_API DataManager: public IDataManager
    {
    private:
        TexContainer    m_pTextures;
        ShaderContainer m_pShaders;

    public:
        DataManager() = default;
        virtual ~DataManager() = default;

        virtual Shader*  CreateShader(const std::string _name, const std::string _vertexPath,
                                      const std::string _fragPath, bool _overrideIfExist=false);
        virtual Texture* CreateTexture(const std::string _name, const std::string _path,
                                       bool _overrideIfExist=false);
        virtual Shader*  GetShader(const std::string _name);
        virtual Texture* GetTexture(const std::string _name);
    };
}

#endif
