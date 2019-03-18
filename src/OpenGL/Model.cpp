#include "OpenGL/Model.hpp"

#include "OpenGL/Material.hpp"
#include "OpenGL/Mesh.hpp"

#include "Components/ShapeRenderer.hpp"
#include "Components/Transform.hpp"

#include "Node.hpp"

// To load model
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace simpleGL
{
    void Model::Load(std::string _path, int postProcessFlags, bool _overrideTexture)
    {
        // Make sure data is a collection of triangles and reverse UV to please OpenGL
        // Combine with user flags as a global bitmask
        int usedPostProcess = postProcessFlags | aiProcess_Triangulate | aiProcess_FlipUVs | 0;

        // First get model in assimop format
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(_path, usedPostProcess);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
            return;
        }

        // Recursively load tree data
        ProcessAINode(scene->mRootNode, scene);
    }

    void Model::ProcessAINode(aiNode *_node, const aiScene *_scene)
    {
        // @TODO
    }


    void Model::ProcessAIMesh(aiMesh *_mesh, const aiScene *_scene)
    {
        // @TODO
    }


    void Model::Draw(Component *_pcomp)
    {
        // Get Renderer and use it to draw multiple meshes
        ShapeRenderer* pShapeRenderer = dynamic_cast<ShapeRenderer*>(_pcomp);

        if (pShapeRenderer != nullptr)
        {
            for (size_t i = 0; i < m_meshes.size(); i++)
            {
                // Draw each mesh
                m_materials[i]->Use(*(pShapeRenderer->GetParent().GetComponent<Transform>()));
                m_meshes[i].Draw(_pcomp);
            }
        }
    }
}
