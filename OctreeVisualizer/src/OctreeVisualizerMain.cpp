#include "Storm3DWindow/include/Storm3DSDLWindow.h"

#include "Storm3DCore/include/MeshManager.h"
#include "Storm3DCore/include/Node.h"
#include "Storm3DCore/include/TextureManager.h"
#include "Storm3DCore/include/PointLight.h"
#include "Storm3DCore/include/MaterialManager.h"
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/OctreeBuilder.h" 
#include "Storm3DCore/include/ImageLoader.h"
#include "Storm3DCore/include/OctreeMeshBuilder.h" 
#include "Storm3DCore/include/Octree.h" 

#include "PhysicsEngine/include/PhysicsManager.h"
#include "Storm3DModelConverter/MeshReader.h"
#include "Storm3DRendering/include/Shader.h"
#include "Storm3DCore/include/RayCaster.h"


#include <functional>

Material* simple;
Octree* node;
SDLWindow window;
PointLight* light;

GameObject* player;

SceneManager* scene1;

FPSCamera* mainCamera;
glm::vec3 cameraPos;
Node* coordinatesNode;
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

	case SDLK_t: 
		{
		}
	}
	//printf ( "position: x %f y %f z %f w %f\n" , childe->GetOrientation().x, childe->GetOrientation().y , childe->GetOrientation().z, childe->GetOrientation().w);
}

void __stdcall LateUpdate( float time)
{

}

void __stdcall ContKeyboardEvent( void *keyboardState )
{	
	const Uint8* keystate = (const Uint8*)keyboardState;
	if ( keystate[SDL_SCANCODE_RIGHT] )
	{
		//triangleNode->Translate( glm::vec3(0.01,0,0 ) );
	}	

	if ( keystate[SDL_SCANCODE_LEFT] )   
	{
		//triangleNode->Translate( glm::vec3(-0.01,0,0 ) );	
	}

	if ( keystate[SDL_SCANCODE_DOWN] )   
	{
		//triangleNode->Translate( glm::vec3( 0,0,0.01 ) );			
	}

	if ( keystate[SDL_SCANCODE_UP] )   
	{
		//triangleNode->Translate( glm::vec3( 0,0,-0.01 ) );			
	}

	if ( keystate[SDL_SCANCODE_W] )   
	{
		mainCamera->MoveForward(0.10f);
	}
	if ( keystate[SDL_SCANCODE_S] )
	{
		mainCamera->MoveForward(-0.10f);
	}
	if ( keystate[SDL_SCANCODE_D] )
	{
		mainCamera->Starf( 0.10f );
	}
	if ( keystate[SDL_SCANCODE_A] )   
	{
		mainCamera->Starf( -0.10f );
	}

	if ( keystate[SDL_SCANCODE_K] )
	{
		light->MoveLight( 0, 0, 0.10f );
	}
	if ( keystate[SDL_SCANCODE_I] )   
	{
		light->MoveLight( 0, 0, -0.10f );
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
			//std::cout << "Button Right";          
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
    Mesh* m = new Mesh;

	SubMesh* rayMesh = new SubMesh();
    m->AddSubMesh( rayMesh );
	rayMesh->AddVertex( rayOrigin );
	rayMesh->AddVertex( rayOrigin + rayDir*5.0f );

	rayMesh->AddVertexColor(1, 1, 1, 1);
	rayMesh->AddVertexColor( color.r, color.g, color.b, color.a );

	rayMesh->AddLine(0,1);

	ObjectRenderer* rayRenderer = Renderer::GetInstance().CreateObjectRenderer( simple, coordinatesNode, MeshManager::GetInstance().AddResource( m ) );
	rayRenderer->SetDrawMode( DrawMode::Lines );
}

void DrawCoord()
{	
    MeshHandle coordinate = MeshManager::GetInstance().AddResource( new Mesh );
    
    SubMesh* coordSubMesh = new SubMesh(); 
	coordSubMesh->AddVertex( 0.0f, 0.0f, 0.0f);
	coordSubMesh->AddVertex( 1.0f, 0.0f, 0.0f);
	coordSubMesh->AddVertexColor( 1,0,0,1 );
	coordSubMesh->AddVertexColor( 1,0,0,1 );

	coordSubMesh->AddVertex( 0.0f, 0.0f, 0.0f);
	coordSubMesh->AddVertex( 0.0f, 1.0f, 0.0f);
	coordSubMesh->AddVertexColor( 0,1,0,1 );
	coordSubMesh->AddVertexColor( 0,1,0,1 );

	coordSubMesh->AddVertex( 0.0f, 0.0f, 0.0f);
	coordSubMesh->AddVertex( 0.0f, 0.0f, 1.0f);
	coordSubMesh->AddVertexColor( 0,0,1,1 );
	coordSubMesh->AddVertexColor( 0,0,1,1 );

	coordSubMesh->AddLine( 0, 1 );
	coordSubMesh->AddLine( 2, 3 );
	coordSubMesh->AddLine( 4, 5 );
	coordinate->AddSubMesh( coordSubMesh );
	coordinatesNode= scene1->GetRootNode()->CreateChild("coordinates");
	ObjectRenderer* coordinatesRenderer = Renderer::GetInstance().CreateObjectRenderer( simple, coordinatesNode, coordinate );
	coordinatesRenderer->SetDrawMode( DrawMode::Lines );

}


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
			//scene1->CastRay( e->button.x, e->button.y );
						
			auto rayOrigin = RayCaster::GenerateRay( e->button.x, e->button.y, 800,600, scene1->GetActiveCamera()->GetViewMatrix(), scene1->GetActiveCamera()->GetProjMatrix() );
			glm::vec3 rayDir = glm::normalize( rayOrigin - glm::vec3(mainCamera->Position()) );			
			std::vector<OctreeNode*> IntersectNodes;
			DrawRay(rayOrigin, rayDir, glm::vec4(1,0,0,0) );

			node->RayTraverse( node->GetRoot(), rayOrigin, rayDir, IntersectNodes );
		
			DrawRay(rayOrigin, rayDir, glm::vec4(0,0,1,0) );		
			
			std::cout << "Nodes hit:" << IntersectNodes.size() << std::endl;
			break;
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
		//std::cout << "camera direction: " <<  (mainCamera->GetForward().x > 0)  << " " << (mainCamera->GetForward().y > 0) << " " << (mainCamera->GetForward().z > 0) << "\n";
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

//------------------------------------------------------------------
Octree* BuildOctree( MeshHandle mesh )
{
	//OctreeBuilder builder;
	AxisAlignedBox b( glm::vec3( -5,-5,-5 ), glm::vec3( 5,5,5) ); 
	AxisAlignedBox box = mesh->GetBounds().CalcCube();
	
    Mesh* m = mesh.Get();
	Octree* root = OctreeBuilder::BuildOctreeFromMesh( &(*m)[0], box.CalcCube(), 3 );
	//OctreeNode* root = builder.BuildOctree( b.CalcCube(), 1 );

	//builder.InsertMeshIntoTree( root, mesh );
	return root;
}

//------------------------------------------------------------------
void LoadScene()
{
	scene1 = window.GetEngine().CreateScene("TestScene");	

	//Load materials.
	simple = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/diffuse.xml");
	Material* constantMaterial = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/constantColorMat.xml");
	
	Material* diffuseBump = MaterialManager::GetInstance().LoadMaterial("E:/projects/Storm3DEngine/EngineDefaults/Materials/diffuseBump.xml");
	
	auto& meshManager =  MeshManager::GetInstance();	
	//meshManager.LoadMesh("E:/projects/Storm3DEngine/EngineDefaults/Models/3spheres.obj");
	//auto model = meshManager.LoadMesh("E:/projects/assets/Engine/Models/Armadillo.ply/Armadillo.obj");	
	//auto model = meshManager.LoadMesh("E:/projects/assets/Engine/Models/dabrovic-sponza/sponza.obj");
	MeshHandle model = meshManager.LoadMesh("E:/projects/assets/Engine/Models/bunny.obj");
	
	model->CalculateNormals();
	int64 t  = GetTimeMs64( );
	node = BuildOctree( model );
	//OctreeBuilder::BuildOctree( model[0]->GetBounds().CalcCube(), 3);
	int64 t2 = GetTimeMs64();
	int64 ti = t2 - t;
	std::cout << ti;
	Mesh* octreeMesh = new Mesh;    
	OctreeMeshBuilder::ConvertOctreeToMesh(node->GetRoot(), octreeMesh);
	octreeMesh->CalculateBounds();
	
	//UniformVec3* color = shader->GetUniformByName<UniformVec3>("baseColor");
	Node* modelNode = scene1->GetRootNode()->CreateChild("sphere");
    ObjectRenderer* modelRenderer = Renderer::GetInstance().CreateObjectRenderer( constantMaterial, modelNode, model );
	ObjectRenderer* modelRendererPoints = Renderer::GetInstance().CreateObjectRenderer( diffuseBump, modelNode, model );
	Node* octreeNode = scene1->GetRootNode()->CreateChild("OctreeMesh");
    MeshHandle octreeMeshH = meshManager.AddResource( octreeMesh );
	Material* mat = MaterialManager::GetInstance().GetMaterialByName("constantColor");
	ObjectRenderer* octreeRenderer = Renderer::GetInstance().CreateObjectRenderer( mat, octreeNode, octreeMeshH );
	octreeRenderer->SetFillMode(GL_LINES);
	octreeRenderer->SetDrawMode(DrawMode::LineStrip);

	DrawCoord();
	
	light = scene1->CreateLight();
	light->SetLightPosition( glm::vec3(10,20,0) );	
	
	mainCamera = new FPSCamera( glm::vec4(0,5,0,0), glm::vec4( 0, 5, 5, 0) );
	scene1->AddCamera( mainCamera );
	//cameraPos = glm::vec3( 0, 0, 0 );
	/*mainCamera->m_target*/
	//mainCamera->SetPosition( cameraPos.x, cameraPos.y, cameraPos.z );
	mainCamera->Perspective( 110.0f, 1.0f, 0.10f, 1024.0f );
	
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

	return 0;
}