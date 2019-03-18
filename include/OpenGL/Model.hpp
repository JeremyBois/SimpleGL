#ifndef __MODEL__HPP
#define __MODEL__HPP

#include "simpleGL_macro.hpp" // Needed for macro definition
#include "Shape.hpp"

#include "glm.hpp"


struct aiNode;
struct aiMesh;
struct aiScene;

namespace simpleGL
{
    class Material;
    class Mesh;

    /// A model is a collection of meshes and associated materials
    class SIMPLEGL_API Model : public Shape
    {
    private:
        std::vector<Mesh>     m_meshes;
        std::vector<Material*> m_materials;

    private:
        void SendData();
        void ProcessAINode(aiNode *_node, const aiScene *_scene);
        void ProcessAIMesh(aiMesh *_mesh, const aiScene *_scene);

      public:
        Model()          = default;
        virtual ~Model() = default;

        void Load(std::string _path, int postProcessFlags, bool _overrideTexture = true);

        virtual void Draw(Component *_pcomp);
    };

} // namespace simpleGL

#endif
