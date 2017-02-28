#ifndef APP_WORLD_REF_COUNTER
#define APP_WORLD_REF_COUNTER


// This class is used to add Ref Counting functionality to any object just Inherite from this class in case you need to add RefCounting. 
// This should be used with SmartPtr implementation. 
// It can be used on its own but it should be used with caution.
class  RefCounter
{

public: 

    RefCounter()
    {
        m_refCount = 0; 
    }

    int RefCount(){ return m_refCount; }

    void AddRef()
    {
        ++m_refCount; 
    } 

    void RemoveRef()
    { 
        // delete is explicitly called so ALL OBJECTS SHOULD BE ALLOCATED USING new.
		  --m_refCount; 
    }


protected: 

    int m_refCount; 

};

#endif 