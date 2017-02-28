#ifndef STORM_3D__HANDLE
#define STORM_3D__HANDLE

#include <vector>

template <typename Resource, typename Manager>
class Handle
{
public:
    Handle(Manager* owner, int id): m_id(id), m_owner(owner)
    {
    }

	Handle(): m_id(-1), m_owner(nullptr)
    {        
		
    }

   // ~ResourceHandle() = default;
	Resource* operator -> ()
	{
		return m_owner->GetResource( m_id );
	}

    bool IsValid(){ return (m_id >= 0); }
	Resource* Get(){ return m_owner->GetResource( m_id ); }

private:
    int		 m_id;
	Manager* m_owner;

};

#endif