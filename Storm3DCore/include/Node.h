#ifndef STORM_3D__NODE_H_
#define STORM_3D__NODE_H_

//#include "Storm3DMath/include/AppWorldMatrix4.h" 
//#include "Storm3DMath/include/AppWorldglm::quat.h" 
//#include "Storm3DCore/include/AppWorldString.h" 
#include "Storm3DRendering/include/ObjectRenderer.h"

#include <string>
#include <set>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <functional>

    /// A general node class , this class basically manages and tracks transformations. 
    //A node in the scene graph is a node in a structured tree. A node contains
    //            information about the transformation which will apply to
    //            it and all of it's children. Child nodes can have transforms of their own, which
    //            are combined with their parent's transformations.
    class PhysicsComponent;
	class SceneManager;
    class Node
    {
    public:
        
        //Internal Type Definitions 
        typedef std::map<std::string, Node*> ChildNodeMap;

        // Enumeration denoting the spaces which a transform can be relative to.
        enum TransformSpace
        {          
            TS_LOCAL,  // Transform is relative to the local space            
            TS_PARENT, // Transform is relative to the space of the parent node            
            TS_WORLD   // Transform is relative to world space.
        };

        Node(SceneManager* owner, Node* parent);
        Node(SceneManager* owner, Node* parent, const char* name);

        ~Node();

        void SetParent(Node* parent); // Only available internally - notification of parent.      
      
        //All SET methods will overrite the current value for example setPosition will set the value of position to a new value.
        //while translate function will accumelate the value.
        const glm::quat& GetOrientation()const; 
        void SetOrientation(const glm::quat& quat );
        
        const glm::vec3& GetPosition(); 
        void SetPosition(const glm::vec3& pos);

        void Translate(const glm::vec3& offset);

        void Scale (const glm::vec3 scale);

		void SetScale ( float x, float y, float z);
        void  SetScale (const glm::vec3 scale);
        const glm::vec3& GetScale();

        const glm::vec3& GetDerivedPosition();
        const glm::vec3& GetDerivedScale();
        const glm::quat& GetDerivedOrientation();

        std::string& GetName(){ return m_name; }
        //update methods
        void UpdateFromParent();
        void UpdateFromParentImpl(); 

		void AddPhysicsComponent( PhysicsComponent* component)
		{
			this->m_physicsComponent = component;
		}

        virtual const glm::mat4& GetFullTransform();
          
        virtual glm::mat3 GetLocalAxes() const;  // Gets a matrix whose columns are the local axes based on the nodes orientation relative to it's parent. 
                   
        // Creates an unnamed new Node as a child of this node.  translate and rotate it relative to parent
        virtual Node* CreateChild( const glm::vec3& translate,  const glm::quat& rotate );
        // Creates a named new Node as a child of this node.  translate and rotate it relative to parent
        virtual Node* CreateChild(const char* name, const glm::vec3& translate = glm::vec3() , const glm::quat& rotate = glm::quat() );

        virtual void _update(bool updateChildren, bool parentHasChanged);
    	
		std::function<void (float deltaTime)> OnUpdate;
		// Gets the local position, relative to this node, of the given world-space position
		virtual glm::vec3 ConvertWorldToLocalPosition( const glm::vec3 &worldPos );

		// Gets the world position of a point in the node local space
		virtual glm::vec3 ConvertLocalToWorldPosition( const glm::vec3 &localPos );

		// Gets the local orientation, relative to this node, of the given world-space orientation
		virtual glm::quat ConvertWorldToLocalOrientation( const glm::quat &worldOrientation );

		/** Gets the world orientation of an orientation in the node local space
			useful for simple transforms that don't require a child node.*/
		virtual glm::quat ConvertLocalToWorldOrientation( const glm::quat &localOrientation );
		
        /** Helper function, get the squared view depth.  */
        //Real getSquaredViewDepth(const Camera* cam) const;

        virtual void NeedUpdate(bool forceParentUpdate = false); //  
        virtual void RequestUpdate(Node* child, bool forceParentUpdate = false);// Called by children to notify their parent that they need an update. @param forceParentUpdate Even if the node thinks it has already told it's parent, tell it anyway
		virtual void CancelUpdate(Node* child); // Called by children to notify their parent that they no longer need an update.

		void Yaw( float degree );
        void AttachObjectRenderer( ObjectRenderer* renderer);      
		ObjectRenderer*			GetObjectRenderer(  );/*{ return m_objRenderer; } */   
     
private:

	protected:

        std::string m_name; // Friendly name of this node, can be automatically generated if you don't care
        Node* m_parent;		// Pointer to parent node.
        //ChildNodeMap m_children; // Collection of pointers to direct children; hashmap for efficiency
       
       
        typedef std::set<Node*> ChildUpdateSet;  // List of children which need updating, used if self is not out of date but children are     
        mutable std::deque<Node*> m_childrenToUpdate;  // List of children which need updating, used if self is not out of date but children are
  
        mutable bool			m_needParentUpdate;     // Flag to indicate own transform from parent is out of date 
        mutable bool			m_needChildUpdate;      // Flag indicating that all children need to be updated    
        mutable bool			m_parentNotified;      // Flag indicating that parent has been notified about update request   
        mutable bool			m_queuedForUpdate;     // Flag indicating that the node has been queued for update     

        //Transformations 
        glm::quat				m_orientation;  // Stores the orientation of the node relative to it's parent.
        glm::vec3				m_position;        // Stores the position/translation of the node relative to its parent.
        glm::vec3				m_scale;           // Stores the scaling factor applied to this node
       
        /* Cached combined position. These members are Transformations derived by combining the
           local transformations and those of it's parents. This is updated when _updateFromParent is called by the
           SceneManager or the nodes parent. */
        mutable glm::quat		m_derivedOrientation;
        mutable glm::vec3		m_derivedPosition;
        mutable glm::vec3		m_derivedScale;
        bool					m_inheritOrientation;
        bool					m_inheritScale;
    
        // Cached derived transform as a 4x4 matrix
        mutable glm::mat4		m_cachedTransform;
        mutable bool			m_cachedTransformOutOfDate;
        mutable bool			m_isDirty;
        
        std::vector<Node*>		m_children;
        
		PhysicsComponent*		m_physicsComponent;        
		// Components.
        ObjectRenderer*			m_objRenderer;
        SceneManager*			m_owner;

    };


#endif 