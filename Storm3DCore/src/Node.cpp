#include "Storm3DCore/include/Node.h" 

#include "Storm3DRendering/include/ObjectRenderer.h"
#include "Storm3DRendering/include/Renderer.h"
#include "Storm3DCore/include/SceneManager.h"


//================================================================
Node::Node(SceneManager* owner, Node* parent)
    :m_parent(parent),
    m_needParentUpdate(false),
    m_needChildUpdate(false),
    m_parentNotified(false),
    m_queuedForUpdate(false),
    m_orientation(),
    m_position(),
    m_scale(1.0f, 1.0f, 1.0f),
    m_derivedOrientation(),
    m_derivedPosition(),
    m_derivedScale( 1.0f, 1.0f, 1.0f ),
    m_cachedTransformOutOfDate(true),
    m_objRenderer(NULL),
    m_isDirty(true)
{
    m_owner = owner;
    NeedUpdate();
}


//================================================================
Node::Node(SceneManager* owner, Node* parent, const char* name)
    :m_parent(parent),
    m_needParentUpdate(false),
    m_needChildUpdate(false),
    m_parentNotified(false),
    m_queuedForUpdate(false),
    m_orientation(),
    m_position(),
    m_scale(1.0f, 1.0f, 1.0f),
    m_derivedOrientation(),
    m_derivedPosition(),
    m_derivedScale(1.0f, 1.0f, 1.0f),
    m_cachedTransformOutOfDate(true),
    m_name(name),
    m_isDirty(true),
    m_objRenderer(NULL)
{
    m_owner = owner;
    NeedUpdate();
}


//================================================================
void Node::SetParent(Node* parent)
{
    if (parent != m_parent )
    {
        parent = m_parent; 
        //m_parent
        NeedUpdate();
    }
    //TODO: Add notification to update. 
}

//================================================================
Node* Node::CreateChild( const glm::vec3& translate, const glm::quat& rotate)
{
    // m_children.
    Node* child = new Node(m_owner, this);
    m_children.push_back( child );
	m_owner->AddNode( child );
    return child;
}

// Creates a named new Node as a child of this node.  translate and rotate it relative to parent
//================================================================
Node* Node::CreateChild(const char* name, const glm::vec3& translate, const glm::quat& rotate )
{
     Node* child =  new Node(m_owner, this, name);
     m_children.push_back( child );
	 m_owner->AddNode( child );
     return child;
}

//================================================================
glm::mat3 Node::GetLocalAxes()const
{
    assert( false && "not implemented yet");
    glm::mat3 m;
    return m;
}

//================================================================
const glm::quat& Node::GetOrientation()const 
{ 
    return m_orientation;
}

//================================================================
void Node::SetOrientation(const glm::quat& quat )
{
	//assert ( !quat.IsNaN() && "invalid glm::quat");
	m_orientation = quat;
	m_orientation= glm::normalize(m_orientation);
	NeedUpdate();
}

//================================================================
const glm::vec3& Node::GetPosition()
{
    return m_position;
}

//================================================================
void Node::SetPosition(const glm::vec3& pos)
{
    //assert ( !pos.IsNaN() && "invalid vector");
    m_position = pos; 
    NeedUpdate();
}

//================================================================
void Node::SetScale (const glm::vec3 scale)
{
    //assert ( !scale.IsNaN() && "invalid vector");
    m_scale = scale; 
    NeedUpdate();
}

//================================================================
void Node::SetScale ( float x, float y, float z)
{
	SetScale( glm::vec3(x,y,z) );
}

//================================================================
void Node::Scale (const glm::vec3 scale)
{
    //assert ( !scale.IsNaN() && "invalid vector");
    m_scale *= scale; 
    NeedUpdate();
}

void Node::Translate(const glm::vec3& offset)
{
    m_position += offset;
    NeedUpdate();
}

//================================================================
const glm::vec3& Node::GetScale()
{
    return m_scale; 
}

//================================================================
const glm::mat4& Node::GetFullTransform()
{
    if( m_cachedTransformOutOfDate)
    {
       // m_cachedTransform.MakeTransform( m_derivedPosition, m_derivedScale, m_derivedOrientation);
        m_cachedTransform =  glm::translate( m_derivedPosition)*glm::toMat4( m_derivedOrientation )* glm::scale( m_derivedScale ) ;

		//m_physicsComponent.

  /*     m_cachedTransform[0][3] = m_derivedPosition.x;
       m_cachedTransform[1][3] = m_derivedPosition.y;
       m_cachedTransform[2][3] = m_derivedPosition.z;*/
      
        //glm::tra
        m_cachedTransformOutOfDate = false;
    }
    return m_cachedTransform;
}

//================================================================
const glm::vec3& Node::GetDerivedPosition()
{
    return m_derivedPosition;
}

//================================================================
const glm::vec3& Node::GetDerivedScale()
{
    return m_derivedScale;
}

//================================================================
const glm::quat& Node::GetDerivedOrientation()
{
    return m_derivedOrientation;
}

//================================================================
// Update methods.
void Node::UpdateFromParent()
{
    if (m_parent)
    {
        // Update orientation
        const glm::quat& parentOrientation = m_parent->GetDerivedOrientation();
        if (m_inheritOrientation)
        {
            // Combine orientation with that of parent
            m_derivedOrientation = parentOrientation * m_orientation;
        }
        else
        {
            // No inheritence
            m_derivedOrientation = m_orientation;
        }

        // Update scale
        const glm::vec3& parentScale = m_parent->GetDerivedScale();
        if (m_inheritScale)
        {
            // Scale own position by parent scale, NB just combine
            // as equivalent axes, no shearing
            m_derivedScale = parentScale * m_scale;
        }
        else
        {
            // No inheritence
            m_derivedScale = m_scale;
        }

        // Change position vector based on parent's orientation & scale
        m_derivedPosition = parentOrientation * ( parentScale * m_position );
        // Add altered position vector to parents
        m_derivedPosition += m_parent->GetDerivedPosition();
    }
    else
    {
        // Root node, no parent
        m_derivedOrientation = m_orientation;
        m_derivedPosition = m_position;
        m_derivedScale = m_scale;
        
    }

    m_cachedTransformOutOfDate = true;  // Should create new transformation matrix
    m_needParentUpdate = false;
}

//============================================================================
void Node::_update(bool updateChildren, bool parentHasChanged)
{
    std::string name = this->GetName();
    if ( m_isDirty || updateChildren)
    {
        this->UpdateFromParent();
        m_isDirty = false;
        m_childrenToUpdate.clear();
        
		// TODO FIX THIS LOGIC
        for (int i=0; i< this->m_children.size(); ++i )
        {
            m_children[i]->_update(true, parentHasChanged );           
        }
    }
    else
    { 
        while ( !m_childrenToUpdate.empty() )
        {
            m_childrenToUpdate.front()->_update( updateChildren, parentHasChanged);
            m_childrenToUpdate.pop_front();
        }
    }
      m_parentNotified = false;
}

//============================================================================
glm::vec3 Node::ConvertWorldToLocalPosition( const glm::vec3 &worldPos )
{
    if (m_needParentUpdate)
    {
        UpdateFromParent();
    }

    return glm::inverse( m_derivedOrientation ) * ( (worldPos - m_derivedPosition) / m_derivedScale );
    //return m_derivedOrientation.Inverse().Rotate( (worldPos - m_derivedPosition) / m_derivedScale );
}

//============================================================================
glm::vec3 Node::ConvertLocalToWorldPosition( const glm::vec3 &localPos )
{
    if (m_needParentUpdate)
    {
        UpdateFromParent();
    }
    return m_derivedOrientation * (localPos * m_derivedScale) + m_derivedPosition;
}

//============================================================================
glm::quat Node::ConvertWorldToLocalOrientation( const glm::quat &worldOrientation )
{
    if (m_needParentUpdate)
    {
        UpdateFromParent();
    }
    return glm::inverse (m_derivedOrientation) * worldOrientation;
}

//============================================================================
glm::quat Node::ConvertLocalToWorldOrientation( const glm::quat &localOrientation )
{
    if (m_needParentUpdate)
    {
        UpdateFromParent();
    }
    return m_derivedOrientation * localOrientation;
}

//============================================================================    
void Node::NeedUpdate( bool forceParentUpdate ) //  
{
   m_isDirty= true;
   m_cachedTransformOutOfDate = true;

    //request update from parent.. if its not a root
    if( m_parent && !m_parentNotified && !m_queuedForUpdate )
    {
        m_parent->RequestUpdate(this, forceParentUpdate);
        m_parentNotified = true;
    }
}

//============================================================================
void Node::RequestUpdate(Node* child, bool forceParentUpdate)
{
    m_cachedTransformOutOfDate = true;
    if ( !m_queuedForUpdate )
    {
        m_childrenToUpdate.push_back(child);
		if ( m_parent && forceParentUpdate )
		{
			m_parent->RequestUpdate( this, forceParentUpdate );
		}
    }
}

//============================================================================
void Node::CancelUpdate(Node* child)
{
    
}

////============================================================================
//void Node::AttachMesh(Mesh* pMesh)
//{
//    if( !pMesh)
//        return; 
//
//    if (!m_objRenderer)
//    {
//        m_objRenderer  = Renderer::GetInstance().CreateObjectRenderer();    
//        m_objRenderer->SetOwner(this);
//   }
//
//    m_objRenderer->SetMesh(pMesh);    
//}

//============================================================================
void Node::AttachObjectRenderer( ObjectRenderer* renderer)
{
    m_objRenderer = renderer;
    if ( m_objRenderer != nullptr )
        m_objRenderer->SetOwner(this);
}

////============================================================================
void Node::Yaw( float degree )
{	 
	m_orientation = m_orientation *  glm::angleAxis( degree, glm::vec3(0,1,0) );
	m_orientation = glm::normalize( m_orientation );
	NeedUpdate( true );
}

 
////============================================================================
ObjectRenderer* Node::GetObjectRenderer( )
{
	return m_objRenderer;
}
////============================================================================
//void Node::AddMaterial( Material* pMaterial)
//{
//    if( !pMaterial)
//        return; 
//
//    if (!m_objRenderer)
//    {
//        m_objRenderer  = Renderer::GetInstance().CreateObjectRenderer();
//        m_objRenderer->SetOwner( this);
//    }
//    
//    m_objRenderer->SetMaterial(pMaterial);
//
//}