#ifndef __DATAMANAGER__HPP
#define __DATAMANAGER__HPP

#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "Interface/IDataManager.hpp"

namespace simpleGL
{
    /// Basic DataManager implementation to keep track of Shaders / Textures / Materials.
    class SIMPLEGL_API DataManager: public IDataManager
    {
    private:
        TexContainer      m_textures;
        ShaderContainer   m_shaders;
        MaterialContainer m_materials;
        ModelContainer    m_models;

      public:
        DataManager()          = default;
        virtual ~DataManager() = default;

        virtual Shader*   CreateShader(const std::string _name, const std::string _vertexPath,
                                      const std::string _fragPath, bool _overrideIfExist=false);
        virtual Texture*  CreateTexture(const std::string _name, const std::string _path,
                                       bool _reverseY=false, bool _correctGamma=false, bool _overrideIfExist=false);
        virtual Material* CreateMaterial(const std::string _name, const std::string _shaderName,
                                         bool _overrideIfExist=false);
        virtual Model*    CreateModel(const std::string _name, bool _overrideIfExist = false);

        virtual Shader*   GetShader (const std::string _name) const;
        virtual Texture*  GetTexture (const std::string _name) const;
        virtual Material* GetMaterial(const std::string _name) const;
        virtual Model*    GetModel(const std::string _name) const;

        virtual bool Init();
        virtual bool Update();
        virtual bool Render();
        virtual bool Quit();
    };
}

#endif
