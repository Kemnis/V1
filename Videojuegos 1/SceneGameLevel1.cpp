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
		
		ResourceManager::AddModel("assets/LowPolyPlayer.obj","nave");
		ResourceManager::AddTexture("assets/player.jpg","TextureNave");

		ResourceManager::AddModel("assets/LowPolyEnemy.obj", "meshEnemy");
		ResourceManager::AddTexture("assets/enemy.jpg", "TextureEnemy");

		ResourceManager::BuildGameObject("NaveJugador","nave","TextureNave","LambertMaterialShader", "ColorBlanco", "Primeras");

		ResourceManager::BuildGameObject("BotEnemy", "meshEnemy", "TextureEnemy", "LambertMaterialShader", "ColorBlanco", "Primeras");
		
	}

	Start();

	_RPT0(0, "SceneMenu Created!\n");
	return "S_OK";
}

string SceneGameLevel1::Start()
{

	float height = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec3(35.0f, 0.0f, 35.0f));
	ResourceManager::GetObjectByName("NaveJugador")->Transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	ResourceManager::GetObjectByName("BotEnemy")->Transform->SetTranslation(vec3(50.0f, height + 4.0f, 50.0f));
	ResourceManager::GetObjectByName("BotEnemy")->Transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	return "S_OK";
}
//Frames Scene
string SceneGameLevel1::ProcessScene(double dt)
{
	vec3 rot;
	rot.y = dt;
	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	GameObject*GoPlayer = ResourceManager::GetObjectByName("NaveJugador");
	if(ResourceManager::Player1->thridPerson)
		GoPlayer->Transform->SetTranslation(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));
	else
		GoPlayer->Transform->SetTranslation(ResourceManager::Player1->GetPosition());
	GoPlayer->Transform->SetRotation(vec3(0.0f, ResourceManager::Player1->GetRotation().y - 90,0.0f));

	//Focus GameObject
	if (ResourceManager::Player1->focus)
	{
		//Calcular angulo
		vec3 posGo = ResourceManager::Player1->focus->Transform->GetTranslation();
		vec3 posCam = vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z);
		vec3 rot;
		rot.y = (float)atan2(posCam.x - posGo.x, posCam.z - posGo.z)*(180.0 / XM_PI) - 180;
		//rot.z = (float)atan2(posCam.z - posGo.z, posCam.y - posGo.y) * (180.0 / XM_PI);
		rot.x = (float)atan2(posCam.z - posGo.z, posCam.y - posGo.y) * (180.0 / XM_PI) + 90;

		ResourceManager::Player1-> MyRot.y = rot.y;
		ResourceManager::Player1->MyRot.x = rot.x;
		//SceneCamera->LerpAngle(XMFLOAT3(),XMFLOAT3(),);
	}

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
	GameObject*GOEnemy = ResourceManager::GetObjectByName("BotEnemy");

	specsDx->TurnOnAlphaBlending();
		specsDx->TurnOffCulling();
			specsDx->TurnZBufferOff();
				GObjModel->Draw(GObjModel->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
			specsDx->TurnZBufferOn();
		specsDx->TurnOnCulling();


	GoStage->Draw(GoStage->Transform->ToMatrix(),viewMatrix,*projectionMatrix);
	vec3 trans = GOjugador->Transform->GetTranslation();
	GOjugador->Draw(GOjugador->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
	sphereColi->Draw(XMMatrixScaling(GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio())*XMMatrixScaling(GOjugador->Transform->GetScale().x, GOjugador->Transform->GetScale().y, GOjugador->Transform->GetScale().z)*XMMatrixTranslation(trans.x, trans.y, trans.z),viewMatrix,*projectionMatrix);
	
	trans = GOEnemy->Transform->GetTranslation();
	GOEnemy->Draw(GOEnemy->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
	sphereColi->Draw(XMMatrixScaling(GOEnemy->Transform->GetRadio(), GOEnemy->Transform->GetRadio(), GOEnemy->Transform->GetRadio())*XMMatrixScaling(GOEnemy->Transform->GetScale().x, GOEnemy->Transform->GetScale().y, GOEnemy->Transform->GetScale().z)*XMMatrixTranslation(trans.x, trans.y, trans.z), viewMatrix, *projectionMatrix);
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