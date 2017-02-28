#include "Storm3DCore/include/GameObject.h"

//===================================================
GameObject::GameObject( Node* transform, const std::string& name  ):m_node(NULL), m_renderer(NULL)
{
	m_name = name; 
}

//===================================================
void	GameObject::AddObjectRenderer( ObjectRenderer* renderer )
{
	m_renderer = renderer; 
}

//===================================================
ObjectRenderer*		GameObject::GetObjectRenderer()
{
	return m_renderer;
}

//===================================================
Node*	GameObject::GetNode()
{
	return m_node;
}