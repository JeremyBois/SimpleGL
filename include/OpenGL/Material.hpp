#ifndef __MATERIAL__HPP
#define __MATERIAL__HPP


#include "simpleGL_macro.hpp"  // Needed for macro definition
#include "GameObject.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "Components/Transform.hpp"

#include <unordered_map>
#include <vector>

namespace simpleGL
{

    typedef std::vector<Texture *> TexturesContainerType;
    typedef std::unordered_map<TextureType, TexturesContainerType> TexturesMapType;


/// A material is a container used to store information about shaders, textures,
/// and colors parameters.
class SIMPLEGL_API Material : public GameObject
{
  protected:
    // @TODO Flyweight pattern --> Get a reference to it not an instance
    Shader m_baseShader;

    Shader *m_pShader;

    /// Needed to keep track of type used for texture in shader
    /// Will be used to construct variable name pass to shader
    TexturesMapType m_texturesContainer;

    Texture *m_pDefaultMap;

    // Colors
    glm::vec3 m_ambiant, m_diffuse, m_emission;
    float m_shininess, m_glossiness;

  public:
    Material();
    virtual ~Material();

    // Shader
    void LinkShader(Shader *_pShader);
    Shader &GetShader() const;
    void UseDefaultShader();

    // Texture and texture mask
    void LinkTexture(Texture *_pTexture, TextureType texType);
    void LinkDiffuseMap(Texture *_pTexture);
    void LinkSpecularMap(Texture *_pTexture);
    void LinkEmissionMap(Texture *_pTexture);

    // void UnLinkTexture(TextureType texType);
    // void UnLinkDiffuseMap();
    // void UnLinkSpecularMap();
    // void UnLinkEmissionMap();
    void UnLinkAllTextures();

    Texture &GetTexture(GLenum _unit) const;
    Texture &GetDiffuseMap() const;
    Texture &GetSpecularMap() const;
    Texture &GetEmissionMap() const;

    // Color
    inline glm::vec3 GetAmbiant() const { return m_ambiant; }
    inline glm::vec3 GetDiffuse() const { return m_diffuse; }
    inline float GetShininess() const { return m_shininess; }
    inline float GetGlossiness() const { return m_glossiness; }

    inline void SetAmbiant(glm::vec3 _ambiant) { m_ambiant = _ambiant; }
    inline void SetDiffuse(glm::vec3 _diffuse) { m_diffuse = _diffuse; }
    inline void SetEmission(glm::vec3 _emission) { m_emission = _emission; }
    inline void SetShininess(float _shininess) { m_shininess = _shininess; }
    inline void SetGlossiness(float _glossiness) { m_glossiness = _glossiness; }

    // Send data to shader
    void Use(const Transform &_transform);

  private:
    static std::string GetTextureTypeName(TextureType _texType) noexcept;
};
} // namespace simpleGL
#endif
