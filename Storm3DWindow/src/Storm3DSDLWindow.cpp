//#include <glew/include/GL/glew.h>

#include "Storm3DWindow/include/Storm3DSDLWindow.h" 

#include "Storm3DRendering/include/OpenGL.h"

#include <stdio.h>

#include "SDL/include/SDL.h" 
#include "SDL/include/SDL_opengl.h" 

SDL_Surface *screen;
SDL_Event event;

SDLWindow::SDLWindow(): keyboardEventHandler(0)
{
    m_done = false;
}
//==================================


/* A simple function that prints a message, the error code returned by SDL,
* and quits the application */
void sdldie(const char *msg)
{
    SDL_Quit();
    exit(1);
}

//==================================
void SDLWindow::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

	    /* Request opengl 3.2 context.
    * SDL doesn't have the ability to choose which profile at this time of writing,
    * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//Turn on double buffering with a 24bit Z buffer.
    //You may need to change this to 16 or 32 for your system 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

   
	mainwindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN/*| SDL_WINDOW_FULLSCREEN*/);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");

    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow); 
	glewExperimental = TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WM_GrabInput(SDL_GRAB_ON);
	
	//SDL_SetRelativeMouseMode( SDL_TRUE );
    m_engine.StartEngine();
}

//=================================================================
void SDLWindow::Render()
{
    Renderer& renderer = m_engine.GetRenderer();
    renderer.ClearBuffer();

    glViewport( 0, 0, m_width, m_height);
    renderer.Render();
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    //SDL_GL_SetSwapInterval(1);
    //Renderer& renderer = Renderer::GetInstance();

    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(mainwindow);

}

//=================================================================
void SDLWindow::Close()
{
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
}

//=================================================================
void SDLWindow::Update(float deltaTime)
{
    m_engine.m_scenes[0]->Update(deltaTime);
}

//=================================================================
void SDLWindow::LateUpdate()
{
}

/* Print modifier info */
void PrintModifiers( Uint16 mod )
{
    printf( "Modifers: " );

    /* If there are none then say so and return */
    if( mod == KMOD_NONE )
    {
        printf( "None\n" );
        return;
    }
    /* Check for the presence of each SDLMod value */
    /* This looks messy, but there really isn't    */
    /* a clearer way.                              */
    if( mod & KMOD_NUM ) printf( "NUMLOCK " );
    if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
    if( mod & KMOD_LCTRL ) printf( "LCTRL " );
    if( mod & KMOD_RCTRL ) printf( "RCTRL " );
    if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
    if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
    if( mod & KMOD_RALT ) printf( "RALT " );
    if( mod & KMOD_LALT ) printf( "LALT " );
    if( mod & KMOD_CTRL ) printf( "CTRL " );
    if( mod & KMOD_SHIFT ) printf( "SHIFT " );
    if( mod & KMOD_ALT ) printf( "ALT " );
    printf( "\n" );
}

/* Print all information about a key event */
void PrintKeyInfo( SDL_KeyboardEvent *key )
{
 //   /* Is it a release or a press? */
 //   if( key->type == SDL_KEYUP )
 //       printf( "Release:- " );
 //   else
 //       printf( "Press:- " );

 //   /* Print the hardware scancode first */
 //   printf( "Scancode: 0x%02X", key->keysym.scancode );
 //   /* Print the name of the key */
 //   printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
 //   /* We want to print the unicode info, but we need to make */
 //   /* sure its a press event first (remember, release events */
 //   /* don't have unicode info                                */
 //   if( key->type == SDL_KEYDOWN )
	//{
 //       /* If the Unicode value is less than 0x80 then the    */
 //       /* unicode value can be used to get a printable       */
 //       /* representation of the key, using (char)unicode.    */
 //       printf(", Unicode: " );
 //       if( key->keysym.unicode < 0x80 && key->keysym.unicode > 0 ){
 //           printf( "%c (0x%04X)", (char)key->keysym.unicode,
 //               key->keysym.unicode );
 //       }
 //       else
 //       {
 //           printf( "? (0x%04X)", key->keysym.unicode );
 //       }
 //   }
 //   printf( "\n" );
 //   /* Print modifier info */
 //   PrintModifiers( key->keysym.mod);
}
#include <iostream>

//=================================================================
void SDLWindow::MainLoop()
{
	float dt = 1000.0f/60.0f;
	unsigned int currentTimeMs = SDL_GetTicks();
	unsigned int lastTimeMs = 0;
	unsigned int timePassed = 34;
	while(!m_done)
	{
		//SDL_PumpEvents();	
		while(SDL_PollEvent(&event)) 
		{			
			if (event.type == SDL_QUIT) 
			{
				m_done = true;
			}
			if (event.type == SDL_KEYDOWN)
			{		
				keyboardEventHandler(&event);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN )
			{
				mouseEventHandler(&event);
			}
			if (event.type == SDL_MOUSEBUTTONUP )
			{
				mouseButtonUp(&event);
			}
			if (event.type == SDL_MOUSEMOTION )
			{
				mouseMotionHandler(&event);
			}			
		}
		
		int length;
		const Uint8 *state = SDL_GetKeyboardState(&length);
		continueKeyboardEvent( (void*)state );
		
		lastTimeMs =  currentTimeMs;
		currentTimeMs = SDL_GetTicks();		
		timePassed += currentTimeMs - lastTimeMs; 

		while ( timePassed >= dt )
		{
			timePassed  -= dt;
			Update( dt );
		}
		
		lateUpdateHandler( dt );
		
		Render();
		//LateUpdate();	
	}
}

//=================================================================
void SDLWindow::SetWindowDimensions(int width, int height)
{
    m_width = width;
    m_height= height;
}

//=================================================================
void SDLWindow::SetFullScreen (bool fullscreen)
{
    m_fullScreen = fullscreen;
	//SDL_
}


