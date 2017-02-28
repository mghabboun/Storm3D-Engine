#ifndef APP_WORLD_SMART_PTR
#define APP_WORLD_SMART_PTR

namespace AppWorld  
{

    template<class T> 
	class SmartPtr 
    {
    public:
        //Constructer , Destructer
        SmartPtr( T* obj = NULL )
        {
            m_ptr= obj;
            if (m_ptr)
            {
                m_ptr->AddRef();
            }
        } 

        ~SmartPtr()
        {
            if (m_ptr)
            {
                m_ptr->RemoveRef();
            }
        }

        T& operator = (const SmartPtr ptr )
        {
            if (ptr != m_ptr ) 
            {
               if (ptr)
                ptr->AddRef(); 
               if (m_ptr)
                    m_ptr->RemoveRef();
             
               m_ptr = ptr; 
            }

            return *this; 
        }
        
        operator T*(){ return (T*)m_ptr; } 
        T& operator * ()const { return *m_ptr;}
        T* operator ->()const { return m_ptr; }

        bool operator == (const SmartPtr& ptr) 
        {
            return (m_ptr == ptr.m_ptr);
        }

        bool operator != (const SmartPtr& ptr) 
        {
            return (m_ptr != ptr.m_ptr);
        }

    private: 
        T* m_ptr; 

        SmartPtr( SmartPtr& smrtPtr); // disallow copying.        
    };
    
}
#endif