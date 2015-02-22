#include "meshfactory.hpp"

#include "assimp.hpp"
#include "graphicsdevice.hpp"
#include "logger.hpp"
#include "mesh.hpp"
#include "vertexarrayimpl.hpp"

gst::MeshFactory::MeshFactory(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<Logger> logger)
    : device(device),
      logger(logger)
{
}

gst::Mesh gst::MeshFactory::create_quad(float width, float height)
{
    auto vertex_array = std::make_shared<VertexArrayImpl>(device);
    auto mesh = Mesh(device, vertex_array);

    mesh.set_positions({
        glm::vec3(-width, -height, 0.0f),
        glm::vec3(width, -height, 0.0f),
        glm::vec3(-width, height, 0.0f),
        glm::vec3(width, height, 0.0f),
    });
    mesh.set_tex_coords({
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
    });
    mesh.set_indices({ 0, 1, 2, 2, 1, 3, });

    return mesh;
}

std::vector<gst::Mesh> gst::MeshFactory::create_from_file(std::string const & path)
{
    std::vector<Mesh> meshes;

    Assimp::Importer importer;
    aiScene const * scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
    if (!scene) {
        logger->log(TRACE("assimp: " + std::string(importer.GetErrorString())));
        return meshes;
    }

    std::function<void(aiNode *, aiScene const *)> traverse;
    traverse = [this, &traverse, &meshes](aiNode * node, aiScene const * scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh const * ai_mesh = scene->mMeshes[node->mMeshes[i]];

            std::vector<glm::vec3> positions(ai_mesh->mNumVertices);
            for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
                aiVector3D ai_position = ai_mesh->mVertices[i];
                positions[i].x = ai_position.x;
                positions[i].y = ai_position.y;
                positions[i].z = ai_position.z;
            }

            std::vector<glm::vec3> normals(ai_mesh->mNumVertices);
            for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
                aiVector3D ai_normal = ai_mesh->mNormals[i];
                normals[i].x = ai_normal.x;
                normals[i].y = ai_normal.y;
                normals[i].z = ai_normal.z;
            }

            std::vector<glm::uint> indices;
            indices.reserve(ai_mesh->mNumFaces * 3); // minimum possible triangles (if any)
            for(unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
                aiFace ai_face = ai_mesh->mFaces[i];
                for(unsigned int j = 0; j < ai_face.mNumIndices; j++) {
                    indices.push_back(ai_face.mIndices[j]);
                }
            }

            auto vertex_array = std::make_shared<VertexArrayImpl>(device);
            auto mesh = Mesh(device, vertex_array);

            if (!positions.empty()) {
                mesh.set_positions(positions);
            }
            if (!normals.empty()) {
                mesh.set_normals(normals);
            }
            if (!indices.empty()) {
                mesh.set_indices(indices);
            }

            meshes.push_back(mesh);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            traverse(node->mChildren[i], scene);
        }
    };

    traverse(scene->mRootNode, scene);

    return meshes;
}
