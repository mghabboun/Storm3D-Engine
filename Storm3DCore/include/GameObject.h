#ifndef STORM_3D_GAME_OBJECT
#define STORM_3D_GAME_OBJECT

#include <string>

class Node;
class Mesh;
class Material;
class ObjectRenderer;
class GameObject
{
public:	
						GameObject( Node* node, const std::string& name );						

	void				AddObjectRenderer( ObjectRenderer* renderer );
	ObjectRenderer*		GetObjectRenderer();
	Node*				GetNode();
	
	Node*				m_node;
	ObjectRenderer*		m_renderer;
	std::string			m_name;
};

#endif