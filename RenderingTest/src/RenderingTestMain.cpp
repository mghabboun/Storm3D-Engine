#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#include "Storm3DWindow/include/Storm3DSDLWindow.h"

#include "Storm3DRendering/include/Shader.h"
#include "Storm3DCore/include/MeshManager.h"
#include "Storm3DCore/include/Node.h"

#include "Storm3DCore/include/TextureManager.h"
#include "Storm3DCore/include/PointLight.h"
#include "Storm3DCore/include/MaterialManager.h"
#include "PhysicsEngine/include/PhysicsManager.h"
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"

#include "Storm3DModelConverter/MeshReader.h"
#include "Storm3DCore/include/OctreeBuilder.h" 
#include "Storm3DCore/include/ImageLoader.h"
#include "Storm3DCore/include/OctreeMeshBuilder.h" 
#include "Storm3DCore/include/RayCaster.h"
#include "Storm3DCore/include/ResourceManager.h"

#include "SDL/include/SDL.h" 
#include "SDL/include/SDL_opengl.h" 
#include <functional>

SDLWindow window;

PointLight* light;
Material* simple;

Node* sphere = NULL;
Node* tankNode = NULL;
Node* turret = NULL;
GameObject* player;
Material* constantColor = NULL;
SceneManager* scene1;
glm::vec3 targetPosition;
FPSCamera* mainCamera = nullptr;
glm::vec3 cameraPos;

using namespace Storm3D;

//bool mouseDown= false;
void __stdcall KeyboardEvent( void *pV )
{
  //std::cout << "Keyboard event\n";
	if(pV == NULL)
		return;

	SDL_Event* e =(SDL_Event*)(pV);
	switch( e->key.keysym.sym )
	{
	case SDLK_ESCAPE:
		exit(0);
		break;
	}
	//printf ( "position: x %f y %f z %f w %f\n" , childe->GetOrientation().x, childe->GetOrientation().y , childe->GetOrientation().z, childe->GetOrientation().w);
}

void __stdcall LateUpdate( float time )
{
}

void __stdcall ContKeyboardEvent( void *keyboardState )
{	
	const Uint8* keystate = (const Uint8*)keyboardState;
	if ( keystate[SDL_SCANCODE_RIGHT] )
	{
		tankNode->Translate( glm::vec3( 1.0f, 0.0f, 0.0f) );
	}	

	if ( keystate[SDL_SCANCODE_LEFT] )   
	{
		tankNode->Translate( glm::vec3(-1.0f, 0.0f, 0.0f) );
	}

	if ( keystate[SDL_SCANCODE_DOWN] )   
	{
		tankNode->Translate( glm::vec3( 0.0f, 0.0f, 1.0f) );
	}

	if ( keystate[SDL_SCANCODE_UP] )   
	{
		tankNode->Translate( glm::vec3(0, 0.0f, -1.0f) );
	}

	if ( keystate[SDL_SCANCODE_W] )   
	{
		mainCamera->MoveForward(1.0f);
	}
	if ( keystate[SDL_SCANCODE_S] )
	{
		mainCamera->MoveForward(-1.0f);
	}
	if ( keystate[SDL_SCANCODE_D] )
	{
		mainCamera->Starf( 1.0f );
	}
	if ( keystate[SDL_SCANCODE_A] )   
	{
		mainCamera->Starf( -1.0f );
	}

	if ( keystate[SDL_SCANCODE_K] )
	{
		light->MoveLight( 0, 0, 1.0f );
	}
	if ( keystate[SDL_SCANCODE_I] )   
	{
		light->MoveLight( 0, 0, -1.0f );
	}
}

int xstart=0;
int ystart=0;
bool   startCameraRot = false; 
bool   startCameraMov = false;
void __stdcall MouseEvent( void *pV )
{
	if(pV == NULL)
		return;

	SDL_Event* e =(SDL_Event*)(pV);

	switch(e->button.button)
	{
	case SDL_BUTTON_LEFT:
		{
			//mainCamera->RotateY( 1.0f);
			int x = e->button.x;
			int y = e->button.y;

			startCameraRot = true;
			break;
		}
	case SDL_BUTTON_RIGHT:
		{
			//mainCamera->RotateY(-1.0f);
			std::cout << "Button Right";          
			//OnRButtonDown(e->button.x, e->button.y);
			break;
		}
	case SDL_BUTTON_MIDDLE: 
		{
			//OnMButtonDown(e->button.x, e->button.y);
			break;
		}
	}
}

void DrawRay(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec4 color)
{
	// Render the ray
	std::cout << rayDir.x << " " << rayDir.y << " " << rayDir.z << " " << std::endl;
	std::cout << rayOrigin.x << " " << rayOrigin.y << " " << rayOrigin.z << " " << std::endl;

	SubMesh* rayMesh = new SubMesh();
	rayMesh->AddVertex( rayOrigin );
	rayMesh->AddVertex( rayOrigin + rayDir*1000.0f );

	rayMesh->AddVertexColor(1, 1, 1, 1);
	rayMesh->AddVertexColor( color.r, color.g, color.b, color.a );

	rayMesh->AddLine(0,1);

	//ObjectRenderer* rayRenderer = Renderer::GetInstance().CreateObjectRenderer( constantColor, groundNode, MeshManager::GetInstance().AddResource( rayMesh ) );
	//rayRenderer->SetDrawMode( DrawMode::Lines );
}

glm::vec3 intersection;
void __stdcall MouseButtonUp( void *pV )
{
	if(pV == NULL)
		return;

	SDL_Event* e =(SDL_Event*)(pV);

	switch( e->button.button )
	{
	case SDL_BUTTON_LEFT: 
		{
			startCameraRot = false;
			break;
		}
	case SDL_BUTTON_RIGHT:
		{
			intersection = glm::vec3();
			int count = 0;
			scene1->CastRay( e->button.x, e->button.y );

			auto rayOrigin = RayCaster::GenerateRay( e->button.x, e->button.y, 800,600, scene1->GetActiveCamera()->GetViewMatrix(), scene1->GetActiveCamera()->GetProjMatrix() );
			glm::vec3 rayDir = glm::normalize( rayOrigin - glm::vec3(mainCamera->Position()) );		
			std::cout << "direction: " <<  rayDir.x << " " << rayDir.y << " " << rayDir.z << " " << std::endl;

			std::vector<OctreeNode*> IntersectNodes;
			//node->RayTraverse( node->GetRoot(), rayOrigin, rayDir, IntersectNodes );
			float minDistance = 9999999 ;
			std::cout << "Nodes hit " << IntersectNodes.size();
			
			int stop = 0;

			DrawRay(rayOrigin, rayDir, glm::vec4(0,0,1,0) );		
		}
	case SDL_BUTTON_MIDDLE:
		{
			break;
		}
	}
}



void __stdcall MouseMotion( void *pV )
{
	if(pV == NULL)
		return;

	SDL_Event* e =(SDL_Event*)(pV);
	if ( startCameraRot ) 
	{	
		mainCamera->Yaw( -e->motion.xrel );
		mainCamera->Pitch( -e->motion.yrel );
		glm::quat q = glm::angleAxis( (-e->motion.xrel)*1.0f, glm::vec3( 0,1,0) );
	}
}

//------------------------------------------------------------------
typedef long long int64; 
typedef unsigned long long uint64;
int64 GetTimeMs64()
{
	FILETIME ft;
	LARGE_INTEGER li;
	/* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
	* to a LARGE_INTEGER structure. */
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	uint64 ret = li.QuadPart;
	ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
	ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

	return ret;
}

//Node* CreateGameObject( MeshConvertor& convertor, const char* meshFile, Node* parent, const char* childName, Material* material)
//{
//	std::vector<Mesh*> mesh = convertor.LoadMesh(meshFile);	
//	tankNode->SetScale(1.0f,1.0f,1.0f);
//	Node* node = parent->CreateChild(childName);
//
//	ObjectRenderer* bodyRenderer = Renderer::GetInstance().CreateObjectRenderer( material, node );
//	bodyRenderer->SetMesh( mesh[0] );
//
//	return node;
//}

void TankUpdate( float deltaTime )
{
	glm::vec3 pos= glm::lerp( tankNode->GetPosition(), intersection, deltaTime/100 );
	tankNode->SetPosition( pos );	
}


//
//void DrawCoord()
//{	
//	auto coordinateMesh = MeshManager::GetInstance().AddResource( new Mesh );
//    SubMesh*  coordinate = new SubMesh();
//	coordinate->AddVertex( 0.0f, 0.0f, 0.0f);
//	coordinate->AddVertex( 1000.0f, 0.0f, 0.0f);
//	coordinate->AddVertexColor( 1,0,0,1 );
//	coordinate->AddVertexColor( 1,0,0,1 );
//
//	coordinate->AddVertex( 0.0f, 0.0f, 0.0f);
//	coordinate->AddVertex( 0.0f, 1000.0f, 0.0f);
//	coordinate->AddVertexColor( 0,1,0,1 );
//	coordinate->AddVertexColor( 0,1,0,1 );
//
//	coordinate->AddVertex( 0.0f, 0.0f, 0.0f);
//	coordinate->AddVertex( 0.0f, 0.0f, 1000.0f);
//	coordinate->AddVertexColor( 0,0,1,1 );
//	coordinate->AddVertexColor( 0,0,1,1 );
//
//	coordinate->AddLine( 0, 1 );
//	coordinate->AddLine( 2, 3 );
//	coordinate->AddLine( 4, 5 );
//	
//	Node* coordinatesNode = scene1->GetRootNode()->CreateChild("coordinates");
//	ObjectRenderer* coordinatesRenderer = Renderer::GetInstance().CreateObjectRenderer( simple, coordinatesNode, coordinate );
//	coordinatesRenderer->SetDrawMode( DrawMode::Lines );
//}


//------------------------------------------------------------------
void LoadScene()
{
	ResourceManager resourceManager;
	resourceManager.AddSearchPath("E:/projects/Storm3DEngine/EngineDefaults/Textures");
	resourceManager.AddSearchPath("E:/projects/Storm3DEngine/EngineDefaults/Materials");
	resourceManager.AddSearchPath("../EngineDefaults/Textures");

	scene1 = window.GetEngine().CreateScene("TestScene");
	//window.m_engine.GetRenderer().CreateFrameBufferObject();
	int64 t  = GetTimeMs64( );
	int64 t2 = GetTimeMs64();
	int64 ti = t2 - t;
	std::cout << ti;
	
	ImageLoader loader;
	Image* image = loader.LoadImage( "E:/projects/Storm3DEngine/EngineDefaults/Textures/HeightMap2.jpg" );
	
	MeshLoader meshLoader;
	auto& meshManager =  MeshManager::GetInstance();	
	
 	Material* diffuse = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/diffuse.xml");
 	constantColor = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/constantColorMat.xml");
	simple = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/simpleMat.xml");

	Material* diffuseBump = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/diffuseColorMat.xml");
    //diffuse->SetDiffuseColor
	Node* root = scene1->GetRootNode();
	tankNode = root->CreateChild("tankNode");

	 //MeshHandle car  = meshManager.LoadMesh("E:\\projects\\assets\\Engine\\Models\\sphere.obj");
	//MeshHandle car = meshManager.LoadMesh("E:/projects/assets/Engine/Models/MercedesBenzSLSAMG/sls_amg.dae");
	MeshHandle car = meshManager.LoadMesh("E:/projects/assets/Engine/Models/Lamborgini/Avent.obj");    
	//tankNode->SetScale(5.0f,5.0f,5.0f);
	Node* body = tankNode->CreateChild("body");
	car->CalculateNormals();
    ObjectRenderer* bodyRenderer = Renderer::GetInstance().CreateObjectRenderer( diffuse, body, car );
    
	player = scene1->CreateGameObject(std::string("TankObject"), tankNode );

	//DrawCoord();	
	tankNode->OnUpdate =  &TankUpdate;

	light = scene1->CreateLight();
	light->SetLightPosition( glm::vec3(10,20,0) );
	
	mainCamera = new FPSCamera( glm::vec4(0,0,0,0), glm::vec4( 0, 0, 1, 0) );
	scene1->AddCamera( mainCamera );
	cameraPos = glm::vec3( 0, 0, 10 );
	
	/*mainCamera->m_target*/
	mainCamera->SetPosition( cameraPos.x, cameraPos.y, cameraPos.z );
	mainCamera->Perspective( 90.0f, 1.0f, 1.0f, 1024.0f );
	
	scene1->SetActiveCamera( mainCamera );
}

//--------------------------------------
void UnloadScene()
{

}

//--------------------------------------
int main( int argc, char *argv[] )
{	
	window.SetWindowDimensions( 800, 600 );
	//window.SetWindowDimensions( 1920, 1080 );
	GLenum  e = glGetError();
	window.SetFullScreen( false );
	window.Initialize();

	// Register callback functions 
	window.SetKeyboardEventHandler  ( KeyboardEvent   );
	window.SetMouseEventHandler     ( MouseEvent      );
	window.SetMouseMotionHandler    ( MouseMotion     );
	window.SetMouseButtonUpHandler  ( MouseButtonUp   );
	window.SetContinueKeyboardEventHandler(ContKeyboardEvent);
	window.SetLateUpdateHandler     ( LateUpdate ); 
	LoadScene();
	window.MainLoop();
	window.Close();

	_CrtDumpMemoryLeaks();
	return 0;
}