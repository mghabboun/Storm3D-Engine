#ifndef MESH_H
#define	MESH_H

#include "glm/glm.hpp"
#include <map>
#include <vector>
#include <assimp2.0.863/include/assimp.h>
#include "assimp2.0.863/include/aiMesh.h"
#include "Storm3DCore/include/TextureManager.h"

struct Vertex
{	
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex() {}

    Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

class Mesh;
class SubMesh;

class MeshLoader
{
public:
    MeshLoader();
    ~MeshLoader();

    Mesh* LoadMesh(const std::string& Filename);

private:
	std::vector<SubMesh*> InitFromScene(const aiScene* pScene, const std::string& Filename);
    SubMesh* LoadSubMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry 
	{
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;
};


#endif	/* MESH_H */

