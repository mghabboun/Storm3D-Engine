#include "Storm3DCore/include/SceneManager.h" 

#include "Storm3DCore/include/Camera.h" 
#include "Storm3DCore/include/PointLight.h" 
#include "Storm3DCore/include/Node.h"
#include "Storm3DRendering/include/Renderer.h" 
#include "Storm3DCore/include/RayCaster.h"
#include "Storm3DCore/include/GameObject.h"
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"
#include "Storm3DMath/include/Triangle.h"


SceneManager::SceneManager()
{
	//m_physics = new PhysicsManager;

	m_meshManager = new MeshManager;
	m_root = new Node(this, 0,"Root");
	m_nodes.push_back(m_root);
}

//======================================
Node* SceneManager::CreateNode(const char* name)
{
	Node* n = new Node(this, 0, name); 

	m_nodes.push_back(n);
	return n;
}

//======================================
void SceneManager::AddNode(Node* node)
{
	if (!node) 
		return; 

	m_nodes.push_back(node);
}

//======================================
GameObject*	SceneManager::CreateGameObject(std::string &name)
{
	std::string nodeName = name + "Node";
	Node* node = CreateNode( nodeName.c_str() );
	return new GameObject( node, name );
}

//======================================
GameObject*	SceneManager::CreateGameObject(std::string &name, Node* node)
{	
	return new GameObject( node, name );
}

//======================================
FPSCamera* SceneManager::CreateCamera()
{
	FPSCamera* cam = new FPSCamera;
	m_cameras.push_back(cam);
	return cam;
}

//======================================
Camera* SceneManager::GetCameraByName(const std::string& name)
{
	return 0;
	for (int i=0; i < m_cameras.size(); ++i)
	{
		//  if (m_cameras[i]-> == name)
	}
}

//======================================
void   SceneManager::SetActiveCamera(FPSCamera* cam)
{
	m_activeCamera = cam; 
	Renderer& renderer = Renderer::GetInstance();
	renderer.SetActiveCamera(cam);
}

//======================================
void   SetActiveCamera(const std::string& name)
{

}        

//======================================
void SceneManager::TraverseScene()
{

}

//======================================
void SceneManager::Update(float deltaTime)
{
	//Update cameras 
	for (int i=0; i != m_cameras.size();++i)
		m_cameras[i]->Update( deltaTime );

	for (int i=0; i != m_lights.size(); ++i)
		m_lights[i]->Update( m_activeCamera->GetViewMatrix() );

	for (int i=0; i < m_nodes.size(); ++i )
	{
		if (m_nodes[i]->OnUpdate )
			m_nodes[i]->OnUpdate( deltaTime ); // execute the event
	}
	//if (m_root->isDirty())
	//m_physics->StepSimulation( deltaTime );

	// Update Transformations and Hierarchy
	m_root->_update( false, false );


}

//======================================
void SceneManager::UpdateImpl(float deltaTime)
{


}

//======================================
void SceneManager::UpdatePotentiallyVisibleSet()
{

}

//======================================
Node* SceneManager::GetRootNode()
{
	return m_root;
}

//======================================
PointLight*     SceneManager::CreateLight()
{
	PointLight* light= new PointLight; 
	m_lights.push_back(light);
	return light;
}

//======================================
MeshManager& SceneManager::GetMeshManager()
{
	return *m_meshManager;
}

//======================================
SceneManager::~SceneManager()
{
	delete m_meshManager;
}


static bool TriangleIntersect(SubMesh* mesh, Ray r, glm::vec3 intersctionPoint)
{
	// Only hack until I introduce mesh draw mode, check if indicies count divide on 3.
	if (mesh->m_triangles.size() % 3 != 0 ) return false;

	struct TriangleIdx
	{
		unsigned int i0, i1, i2;
	};

	int h = 0;
	for (int i=0; i< mesh->m_triangles.size(); i+=3)
	{
		TriangleIdx* t = (TriangleIdx*)( &mesh->m_triangles[i] );
		Triangle triangle( mesh->m_vertices[t->i0], mesh->m_vertices[t->i1], mesh->m_vertices[t->i2]);
		float dist=0;
		glm::vec3 intersection;		
		if ( triangle.RayIntersect( r.GetOrigin(), r.GetDirection(), dist, intersection) )
		{
			h++;
			return true;
		}
	}
}

//======================================
void SceneManager::CastRay( int mouseX, int mouseY )
{
	glm::vec3 mouseWorldPosition = m_rayCaster->GenerateRay( mouseX, mouseY,  800, 600, m_activeCamera->GetViewMatrix(), m_activeCamera->GetProjMatrix());
	glm::vec3 rayDir = glm::normalize(  mouseWorldPosition - glm::vec3(m_activeCamera->Position()) );
	Ray ray ( glm::vec3(m_activeCamera->Position()), rayDir );
	for (int i= 0; i< m_nodes.size(); ++i)
	{
		Node* node = m_nodes[i];
		ObjectRenderer* renderer = m_nodes[i]->GetObjectRenderer();
		if ( renderer )
		{	
			glm::mat4 m = node->GetFullTransform();
			glm::mat4 mInv = glm::inverse(m);
			AxisAlignedBox bounds = renderer->GetBounds();
			float distance = 0;

			glm::vec3 modelSpacePos = glm::vec3( mInv * m_activeCamera->Position());
			glm::vec3 modeSpaceDir = glm::vec3(mInv * glm::vec4(rayDir,0));
			glm::vec3 intersectionPoint;
			bool hit = bounds.RayIntersect( modelSpacePos, modeSpaceDir, distance, intersectionPoint );

			//Check for ray/triangle intersection
			auto mesh = renderer->GetMesh();
			
			glm::vec3 intersection;
			if ( hit && mesh.IsValid() )
			{
				/*if (TriangleIntersect(mesh.Get(), ray, intersection))
				{
					int stop = 0 ; 
				}*/
			}

			std::cout <<"\n" << node->GetName() << "hit:"<<  hit;
			int stop = 0; 
		}
	}
}

