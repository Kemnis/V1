#include "stdafx.h"

SceneGameLevel1::SceneGameLevel1():Scene()
{

}
SceneGameLevel1::~SceneGameLevel1()
{

}

string SceneGameLevel1::CreateScene()
{
	if (!created)
	{
		created = true;
		//Objects define here
		
		ResourceManager::AddModel("assets/LowPolyEnemy.obj","nave");
		ResourceManager::AddTexture("assets/enemy.jpg","NaveTexture");
		ResourceManager::BuildGameObject("NaveJugador","nave","NaveTexture","LambertMaterialShader", "ColorBlanco", "Primeras");
	}

	Start();

	_RPT0(0, "SceneMenu Created!\n");
	return "S_OK";
}

string SceneGameLevel1::Start()
{

	float height = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec3(35.0f, 0.0f, 35.0f));
	ResourceManager::GetObjectByName("NaveJugador")->Transform->SetTranslation(vec3(35.0f, height + 2.0f, 35.0f));
	return "S_OK";
}
//Frames Scene
string SceneGameLevel1::ProcessScene(double dt)
{
	vec3 rot;
	rot.y = dt;
	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	return "S_OK";
}

//Update Scene
string SceneGameLevel1::RenderScene()
{
	XMMATRIX viewMatrix, viewMatrix2D, *orthoMatrix,*projectionMatrix;
	// Clear the buffers to begin the scene
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();
	SceneCamera->GetViewMatrix(viewMatrix);
	SceneCamera->GetViewMatrix2D(viewMatrix2D);
	orthoMatrix = SceneCamera->GetOrthoMatrix();
	projectionMatrix = SceneCamera->GetProjectionMatrix();

	//Fijar el Skydome a la camrara
	ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));

	GameObject*GoStage = ResourceManager::GetObjectByName("Stage1");
	GameObject* GObjModel = ResourceManager::GetObjectByName("SphereMod");
	GameObject*GOjugador = ResourceManager::GetObjectByName("NaveJugador");
	GameObject*sphereColi = ResourceManager::GetObjectByName("SphereMes");

	specsDx->TurnOnAlphaBlending();
		specsDx->TurnOffCulling();
			specsDx->TurnZBufferOff();
				GObjModel->Draw(GObjModel->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
			specsDx->TurnZBufferOn();
		specsDx->TurnOffCulling();


	GoStage->Draw(GoStage->Transform->ToMatrix(),viewMatrix,*projectionMatrix);
	vec3 trans = GOjugador->Transform->GetTranslation();
	GOjugador->Draw(GOjugador->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
	sphereColi->Draw(XMMatrixScaling(GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio())*XMMatrixTranslation(trans.x, trans.y, trans.z),viewMatrix,*projectionMatrix);
	//Draw 2D

	//specsDx->TurnZBufferOff();
	//goTitle->Draw(XMMatrixIdentity(), viewMatrix, *orthoMatrix);
	//specsDx->TurnZBufferOn();

	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void SceneGameLevel1::DestroyScene()
{

}