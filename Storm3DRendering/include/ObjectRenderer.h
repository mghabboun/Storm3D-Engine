#ifndef APP_WORLD_OBJECT_RENDERER
#define APP_WORLD_OBJECT_RENDERER

#include "Storm3DRendering/include/DrawAttribs.h"
#include "Storm3DRendering/include/HardwareBuffer.h" 


#include "Storm3DCore/include/Material.h"
#include "Storm3DCore/include/MeshManager.h"

#include "Storm3DMath/include/AABB.h"

#include <glm/glm.hpp>

/// Object renderer is responsible for linking hardware buffer and material with geomtery.
///
///
class FPSCamera;
class Mesh;
class Material;
class Node;
class Camera;
class ObjectRenderer
{

public:

    //ObjectRenderer( Node* owner );
    ObjectRenderer( Material* material, Node* owner, MeshHandle mesh );
	
    void        Initialize();
    //void        SetMesh(Mesh* mesh);
    void        SetMaterial(Material* pMat);
    void        SetOwner( Node* owner);
	void		SetFillMode( unsigned int renderMode);
	void		SetDrawMode(DrawMode mode){ m_buffer.SetDrawMode(mode); }

	
	Material*   GetMaterial(){ return m_pMaterial; }
	MeshHandle  GetMesh(){ return m_pMesh; }
    const glm::mat4& GetChachedTransform();

    void        Render( const FPSCamera& activeCamera, const  glm::mat4& transform);

	AxisAlignedBox GetBounds();
private:

	unsigned int m_mode;
    ObjectRenderer();

	Material*       m_pMaterial;
    MeshHandle      m_pMesh;
    Node*           m_owner;

    HardwareBuffer  m_buffer; 
    bool            m_isInit;
};


#endif 