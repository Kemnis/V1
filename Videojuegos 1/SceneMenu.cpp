#include "stdafx.h"
//SceneMenu Menu Inicial del juego
SceneMenu::SceneMenu():Scene()
{
	
}

SceneMenu::~SceneMenu(){}

string SceneMenu::CreateScene()
{
	if (!created)
	{
		created = true;
		//Objects define here
		ResourceManager::AddTexture("assets/tituloGame.png", "TitleTexture");

		ResourceManager::BuildGameObject("BitmapTile", "Bitmap00", "TitleTexture", "GUIShader", "ColorBlanco", "");

	}

	Start();

	_RPT0(0, "SceneMenu Created!\n");
	return "S_OK";
}

string SceneMenu::Start()
{
	ResourceManager::GetObjectByName("BitmapTile")->GetModel()->SetRect(vec4(0, 100, 200, 50));
	return "S_OK";
}
//Frames Scene
string SceneMenu::ProcessScene(double dt)
{
	
	return "S_OK";
}

//Update Scene
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

void SceneMenu::DestroyScene()
{

}