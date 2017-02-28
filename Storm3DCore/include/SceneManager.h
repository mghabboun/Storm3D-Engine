#ifndef APP_WORLD_SCENE_MANAGER_H_
#define APP_WORLD_SCENE_MANAGER_H_

#include "Storm3DCore/include/FPSCamera.h" 
#include "MeshManager.h"
#include "PointLight.h"
//#include "PhysicsEngine/include/PhysicsManager.h"

//#include "Containment/include/AABB.h"

#include <vector> 
#include <queue>

class GameObject;
class RayCaster;
class Node;
class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	FPSCamera*      CreateCamera();
	//GameObject*		CreateGameObject();
	GameObject*		CreateGameObject(std::string &name);
	GameObject*		CreateGameObject(std::string &name, Node* node);

	void			AddCamera( FPSCamera* cam){ m_cameras.push_back( cam); }
	Camera*         GetCameraByName(const std::string& name);
	FPSCamera*		GetActiveCamera(){ return m_activeCamera; }

	void            SetActiveCamera(FPSCamera* cam); 
	void            SetActiveCamera(const std::string& name);
	void            AddNode(Node* node);
	void			CastRay( int mouseX, int mouseY );

	void            Update(float deltaTime);
	void            UpdateImpl(float deltaTime);
	virtual void    UpdatePotentiallyVisibleSet();

	void			TraverseScene();
	Node*           GetRootNode();
	PointLight*     CreateLight();

	MeshManager&    GetMeshManager();
	//PhysicsManager& GetPhysicsManager(){ return *m_physics; }


private:

	Node*           CreateNode(const char* name);

protected: 

	// Camera management
	FPSCamera*					m_activeCamera; 
	std::vector<FPSCamera*>		m_cameras; 
	//std::vector<GameObject*>	m_gameObjects;
	// Node management
	std::vector<Node*>			m_nodes;
	std::vector<PointLight*>	m_lights;	


	std::string					m_name; // scene name
	Node*						m_root;
	RayCaster*					m_rayCaster;
	MeshManager*				m_meshManager; 
	//PhysicsManager*			m_physics;
	//Octree*					m_octree;

};


#endif