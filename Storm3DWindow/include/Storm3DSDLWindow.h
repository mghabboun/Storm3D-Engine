#ifndef STORM_3D_SDL_WINDOW
#define STORM_3D_SDL_WINDOW


#include "Storm3DCore/include/StormEngine.h"

#include "Storm3DRendering/include/OpenGL.h"

#include "SDL/include/SDL.h" 
#include "SDL/include/SDL_opengl.h" 

typedef void (__stdcall *EventHandlerCallback)(void* pV);
typedef void (__stdcall *UpdateHandlerCallback)( float);


class SDLWindow 
{
public: 
   
                    SDLWindow   ();
    void            Initialize  ();
    void            Close       ();
    void            MainLoop    ();
    void            Render      ();
    void            Update      ( float deltaTime );
    void            LateUpdate  ();

    void            SetWindowDimensions(int width, int height);
	int				GetWindowHeight(){ return m_height; }
	int				GetWindowWidth(){ return m_width; }
    void            SetFullScreen (bool fullscreen);
	Engine&			GetEngine(){ return m_engine; }
	
	void SetKeyboardEventHandler(EventHandlerCallback  handler){ keyboardEventHandler   = handler; }
	void SetContinueKeyboardEventHandler(EventHandlerCallback  handler){ continueKeyboardEvent = handler; }
    void SetMouseEventHandler   (EventHandlerCallback  handler){ mouseEventHandler      = handler; }
    void SetMouseMotionHandler  (EventHandlerCallback  handler){ mouseMotionHandler     = handler; }
    void SetMouseButtonUpHandler(EventHandlerCallback  handler){ mouseButtonUp			= handler; }

    void SetUpdateHandler		(UpdateHandlerCallback  handler){ updateHandler			= handler; }
	void SetLateUpdateHandler	(UpdateHandlerCallback  handler){ lateUpdateHandler		= handler; }

private:

    int m_width;
    int m_height;
    bool m_done;
    bool m_fullScreen;

    SDL_Window *mainwindow;		/* Our window handle */
    SDL_GLContext maincontext;	/* Our opengl context handle */

    Engine m_engine;

    EventHandlerCallback keyboardEventHandler;
    EventHandlerCallback mouseEventHandler;
    EventHandlerCallback mouseMotionHandler;
    EventHandlerCallback mouseButtonUp;
    EventHandlerCallback continueKeyboardEvent;
    UpdateHandlerCallback lateUpdateHandler;
    UpdateHandlerCallback updateHandler;

};

#endif