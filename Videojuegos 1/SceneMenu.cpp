#include "stdafx.h"
//SceneMenu Menu Inicial del juego
SceneMenu::SceneMenu(string id):Scene(id)
{
	
}

SceneMenu::~SceneMenu(){}

//Main instruction to Initialize a Scene
string SceneMenu::CreateScene()
{
	//Load Resources of Scene
	RS = LoadResources();
	//Build GameObjects and define Multitexture or Behaviours to objects
	RS = BuildScene();
	//Define the start points of every object if it needs
	RS = Start();
	if (RS == "S_OK")
		_RPT0(0, "Scene Created!\n");
	else
		_RPT0(0, "Scene cannot be created!\n");
	return "S_OK";
}

//Load all objects you need 
string SceneMenu::LoadResources()
{
	RB = ResourceManager::AddTexture(id, "assets/tituloGame.png", "TitleTexture");
	RB = ResourceManager::AddShader(id, "GUIShader", new GUIShader("GUIShader.vsh", "GUIShader.psh"));
	RB = ResourceManager::AddMaterial(id, "ColorBlanco", vec4(0.2, 0.2, 0.4,1.0));

	if (RB != true)
	{
		_RPT0(0, "Something went wrong!\n");
		return "E_Fail";
	}
	else
	{
		_RPT0(0, "Objects Loaded from Scene 0!\n");
		return "S_OK";
	}
}

//Then Build a GameObject or Define a Behaviour of its (Also Multitextures goes here)
string SceneMenu::BuildScene()
{
	
	RS = ResourceManager::BuildGameObject(id, "BitmapTile", "Bitmap00", "TitleTexture", "GUIShader", "ColorBlanco", "");
	if (RS != "S_OK")
	{
		_RPT0(0, "Something went wrong!\n");
		return "S_OK";
	}
	else
	{
		_RPT0(0, "Objects Builded and correctly defined behaviour from Scene 0!\n");
		return "E_Fail";
	}
}

//Define the first location of EVERY Object
string SceneMenu::Start()
{
	ResourceManager::GetObjectByName("BitmapTile")->GetModel()->SetRect(vec4(0, 100, 200, 50));
	return "S_OK";
}

//Then Process all the changes of everything and every object
string SceneMenu::ProcessScene(double dt)
{
	
	return "S_OK";
}

//Finally Render it
string SceneMenu::RenderScene()
{
	XMMATRIX viewMatrix,*orthoMatrix;
	// Clear the buffers to begin the scene
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();
	SceneCamera->GetViewMatrix2D(viewMatrix);
	orthoMatrix = SceneCamera->GetOrthoMatrix();

	GameObject*goTitle = ResourceManager::GetObjectByName("BitmapTile");
	
	
	specsDx->TurnZBufferOff();
		goTitle->Draw(XMMatrixIdentity(), viewMatrix, *orthoMatrix);
	specsDx->TurnZBufferOn();

	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

//Destroys all the objects that were created
void SceneMenu::DestroyScene()
{
	RB = DownloadResources();
	if (RB == true)
		_RPT0(0, "SceneMenu Destroyed!\n");
	else
		_RPT0(0, "Error when try destroy SceneMenu!\n");
}

bool SceneMenu::DownloadResources()
{
	bool Sucess = ResourceManager::DestroyItemsFromScene(id);
	if (Sucess == true)
		return true;
	else
		return false;
}
