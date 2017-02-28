#include <vector>
#include <assert.h>
#include "assimp2.0.863/include/assimp.hpp"
//#include "glew/include/GL/glew.h" 

#include "assimp2.0.863/include/assimp.h"
#include "assimp2.0.863/include/aiMaterial.h"
#include "assimp2.0.863/include/aiScene.h"
#include "assimp2.0.863/include/aiPostProcess.h"

#include "Storm3DRendering/include/Texture.h"
#include "Storm3DCore/include/TextureManager.h"
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"
#include "Storm3DCore/include/MaterialManager.h"


#include "glm/glm.hpp" 

#include "Storm3DModelConverter/MeshReader.h"

using namespace glm;

#define INVALID_OGL_VALUE -1
//======================================
MeshLoader::MeshEntry::MeshEntry()
{
    NumIndices  = 0;
    MaterialIndex = INVALID_MATERIAL;
};

//======================================
MeshLoader::MeshEntry::~MeshEntry()
{  
}

//======================================
void MeshLoader::MeshEntry::Init(const std::vector<Vertex>& Vertices,
                          const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();
}

//======================================
MeshLoader::MeshLoader()
{
}

//======================================
MeshLoader::~MeshLoader()
{
    Clear();
}

//======================================
void MeshLoader::Clear()
{
  /*  for (unsigned int i = 0 ; i < m_Textures.size() ; i++) 
	{
        SAFE_DELETE(m_Textures[i]);
    }*/
}

//======================================
Mesh* MeshLoader::LoadMesh(const std::string& Filename)
{
    // Release the previously loaded mesh (if it exists)
    Clear();
    
    bool Ret = false;
    Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(),  aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs| aiProcess_CalcTangentSpace );
    Mesh* mesh = nullptr;
    if (pScene)
	{
       mesh = new Mesh();
		std::vector<SubMesh*> meshes = InitFromScene(pScene, Filename);
        for (int i=0; i < meshes.size(); ++i )
          mesh->AddSubMesh( meshes[i] );
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }

	return mesh;
}

//======================================
std::vector<SubMesh*> MeshLoader::InitFromScene(const aiScene* pScene, const std::string& Filename)
{  
	std::vector<SubMesh*> meshes;
	meshes.reserve(pScene->mNumMeshes);
    m_Entries.resize(pScene->mNumMeshes);
    //m_Textures.resize(pScene->mNumMaterials);
    for (int i=0; i < pScene->mNumMaterials; ++i )
    {
      const aiMaterial* mat = pScene->mMaterials[i];

      aiString name;
      mat->Get( AI_MATKEY_NAME, name);
      Material* material =  MaterialManager::GetInstance().CreateMaterial(name.data);      
   
      //Read all material properties
      aiColor3D color (0.f,0.f,0.f);
      mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
      material->SetDiffuseColor( color.r, color.g, color.b);
    }

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) 
	{
        const aiMesh* paiMesh = pScene->mMeshes[i];
        SubMesh* m = LoadSubMesh(i, paiMesh);
		meshes.push_back(m);
    }

	return meshes;
    //return InitMaterials(pScene, Filename);
}

//======================================
SubMesh* MeshLoader::LoadSubMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

    SubMesh* newMesh = new SubMesh;
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
	{
		const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent  = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mTangents[i]) : &Zero3D;
		const aiVector3D* pBiTangent  = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero3D;
		
		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
		glm::vec2(pTexCoord->x, pTexCoord->y),
		glm::vec3(pNormal->x, pNormal->y, pNormal->z));

		//Vertices.push_back(v);
		newMesh->AddVertex( pPos->x, pPos->y, pPos->z );
		newMesh->AddNormal( pNormal->x, pNormal->y, pNormal->z );
		if ( pTexCoord )
			newMesh->AddUV0( pTexCoord->x, pTexCoord->y );
		
		newMesh->m_tangents.push_back( glm::vec4( pTangent->x, pTangent->y, pTangent->z, 0 ) );
		newMesh->AddBiTangent( glm::vec3(pBiTangent->x, pBiTangent->y, pBiTangent->z ));
	}

	for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) 
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		newMesh->AddFace( Face.mIndices[0], Face.mIndices[1], Face.mIndices[2]);
	}

	m_Entries[Index].Init(Vertices, Indices);

	newMesh->CalculateBounds();
	return newMesh;
}

//======================================
bool MeshLoader::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) 
	{
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) 
	{
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_Textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
			{
				
                std::string FullPath = Dir + "/" + Path.data;
				TextureManager::GetInstance().LoadTextureFromFile( FullPath );
                //m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

              /*  if (!m_Textures[i]->Load()) 
				{
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_Textures[i];
                    m_Textures[i] = NULL;
                    Ret = false;
                }
                else 
				{
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }*/
            }
        }

        // Load a white texture in case the model does not include its own texture
        if (!m_Textures[i]) 
		{
            /*m_Textures[i] = new Texture(GL_TEXTURE_2D, "./white.png");

            Ret = m_Textures[i]->Load();
       */}
    }

    return Ret;
}

//======================================