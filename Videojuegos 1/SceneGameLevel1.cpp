#include "stdafx.h"

SceneGameLevel1::SceneGameLevel1(string id):Scene(id)
{

}
SceneGameLevel1::~SceneGameLevel1()
{

}

//Main instruction to Initialize a Scene
string SceneGameLevel1::CreateScene()
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
string SceneGameLevel1::LoadResources()
{
	RB = ResourceManager::AddModel(id, "assets/LowPolyPlayer.obj", "nave");
	RB = ResourceManager::AddTexture(id, "assets/player.jpg", "TextureNave");

	RB = ResourceManager::AddModel(id, "assets/LowPolyEnemy.obj", "meshEnemy");
	RB = ResourceManager::AddTexture(id, "assets/enemy.jpg", "TextureEnemy");

	RB = ResourceManager::AddModel(id, "Sphere", "SphereMesh");
	RB = ResourceManager::AddModel(id, "assets/Sphere.obj", "SphereModel");

	RB = ResourceManager::AddModel(id, "Sphere", "Patrol");

	RB = ResourceManager::AddStage(id, "assets/Stage1.bmp", "Stage1", 256, 1024, 1024);
	RB = ResourceManager::AddTexture(id, "assets/SkyStage1Day.jpg", "World");
	RB = ResourceManager::AddTexture(id, "assets/SkyStage1Night.jpg", "WorldNight");
	RB = ResourceManager::AddTexture(id, "assets/mt1Stage1.jpg", "Layer1-Bottom");
	RB = ResourceManager::AddTexture(id, "assets/mt2Stage1.jpg", "Layer2-Mid");
	RB = ResourceManager::AddTexture(id, "assets/mt3Stage1.jpg", "Layer3-Top");
	RB = ResourceManager::AddMaterial(id, "ColorBlanco", vec3(0.2, 0.2, 0.4));
	RB = ResourceManager::AddLight(id, "Luz", vec4(0.1f, 0.8f, 0.8f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f));
	RB = ResourceManager::AddShader(id, "LambertMaterialShader", new MaterialShader("LambertTexture.vs", "LambertTexture.ps"));
	RB = ResourceManager::AddShader(id, "LambertLMaterialShader", new MaterialShader("LambertLTexture.vs", "LambertLTexture.ps", 1));

	RB = ResourceManager::AddShader(id, "MaterialPatrol", new MaterialShader("LambertMaterial.vs", "LambertMaterial.ps"));

 	RB = ResourceManager::AddShader(id, "SkydomeShader", new SkydomeShader("Skydome.vs", "Skydome.ps", 1));
	RB = ResourceManager::AddShader(id, "TerrenoShader", new TerrainShader("Terrain.vs", "Terrain.ps"));

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
string SceneGameLevel1::BuildScene()
{
	RS = ResourceManager::BuildGameObject(id, "NaveJugador", "nave", "TextureNave", "LambertMaterialShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "BotEnemy", "meshEnemy", "TextureEnemy", "LambertMaterialShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "SphereMes", "SphereMesh", "World", "LambertLMaterialShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "SphereMod", "SphereModel", "World", "SkydomeShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "Stage1", "Stage1", "", "TerrenoShader", "ColorBlanco", "Luz");

	RS = ResourceManager::BuildGameObject(id, "Patrols", "Patrol", "", "MaterialPatrol", "ColorBlanco", "Luz");

	//Addtexture
	RS = ResourceManager::AsingTextureToGameObject("SphereMod", "WorldNight");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer1-Bottom");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer2-Mid");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer3-Top");
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
string SceneGameLevel1::Start()
{
	float height = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec3(35.0f, 0.0f, 35.0f));
	vector<vec3> Posiciones;
	Posiciones.push_back(vec3(20.0f, height + 4.0f, 20.0f));
	Posiciones.push_back(vec3(40.0f, height + 4.0f, 45.0f));
	Posiciones.push_back(vec3(60.0f, height + 4.0f, 40.0f));
	Posiciones.push_back(vec3(80.0f, height + 4.0f, 75.0f));
	ResourceManager::GetObjectByName("NaveJugador")->Transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	ResourceManager::GetObjectByName("SphereMod")->Transform->SetRotation(vec3(180,0,0));
	ResourceManager::GetObjectByName("BotEnemy")->Transform->SetTranslation(vec3(50.0f, height + 4.0f, 50.0f));
	ResourceManager::DefinePositionPatrol(Posiciones);
	ResourceManager::GetObjectByName("BotEnemy")->Transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	ResourceManager::StartEnemy(1, 1, "Patrol", 1);
	ResourceManager::DefineTargetToFight("NaveJugador");
	ResourceManager::GetMyBody("BotEnemy");
	ResourceManager::GetObjectByName("Patrols")->Transform->SetTranslation(vec3(20.0f, height + 4.0f, 20.0f));
	ResourceManager::GetObjectByName("Patrols")->IsPatrol(Posiciones);

	return "S_OK";
}

//Then Process all the changes of everything and every object
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

	ResourceManager::UpdateEnemy();
	return "S_OK";
}

//Finally Render it
string SceneGameLevel1::RenderScene()
{
	vec3 posiciones[5];
	XMMATRIX viewMatrix, viewMatrix2D, *orthoMatrix,*projectionMatrix, Patrolmatrix;
	// Clear the buffers to begin the scene
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();
	SceneCamera->GetViewMatrix(viewMatrix);
	SceneCamera->GetViewMatrix2D(viewMatrix2D);
	orthoMatrix = SceneCamera->GetOrthoMatrix();
	projectionMatrix = SceneCamera->GetProjectionMatrix();

	//Fijar el Skydome a la camrara
	ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(vec3(SceneCamera->pos.x, SceneCamera->pos.y, SceneCamera->pos.z));

	GameObject* GoStage = ResourceManager::GetObjectByName("Stage1");
	GameObject* GObjModel = ResourceManager::GetObjectByName("SphereMod");
	GameObject* GOjugador = ResourceManager::GetObjectByName("NaveJugador");
	GameObject* GOPatrol = ResourceManager::GetObjectByName("Patrols");
	//GameObject*sphereColi = ResourceManager::GetObjectByName("SphereMes");
	GameObject*GOEnemy = ResourceManager::GetObjectByName("BotEnemy");

	specsDx->TurnOnAlphaBlending();
	specsDx->TurnOffCulling();
		specsDx->TurnZBufferOff();
			GObjModel->Draw(GObjModel->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
		specsDx->TurnZBufferOn();
	specsDx->TurnOnCulling();

	GOPatrol->DrawPatrol(viewMatrix,*projectionMatrix);


	GoStage->Draw(GoStage->Transform->ToMatrix(),viewMatrix,*projectionMatrix);
	vec3 trans = GOjugador->Transform->GetTranslation();
	GOjugador->Draw(GOjugador->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
	//sphereColi->Draw(XMMatrixScaling(GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio(), GOjugador->Transform->GetRadio())*XMMatrixScaling(GOjugador->Transform->GetScale().x, GOjugador->Transform->GetScale().y, GOjugador->Transform->GetScale().z)*XMMatrixTranslation(trans.x, trans.y, trans.z),viewMatrix,*projectionMatrix);
	
	trans = GOEnemy->Transform->GetTranslation();
	GOEnemy->Draw(GOEnemy->Transform->ToMatrix(), viewMatrix, *projectionMatrix);
	//sphereColi->Draw(XMMatrixScaling(GOEnemy->Transform->GetRadio(), GOEnemy->Transform->GetRadio(), GOEnemy->Transform->GetRadio())*XMMatrixScaling(GOEnemy->Transform->GetScale().x, GOEnemy->Transform->GetScale().y, GOEnemy->Transform->GetScale().z)*XMMatrixTranslation(trans.x, trans.y, trans.z), viewMatrix, *projectionMatrix);
	//Draw 2D

	//specsDx->TurnZBufferOff();
	//goTitle->Draw(XMMatrixIdentity(), viewMatrix, *orthoMatrix);
	//specsDx->TurnZBufferOn();

	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

//Destroys all the objects that were created
void SceneGameLevel1::DestroyScene()
{
	RB = DownloadResources();
	if (RB == true)
		_RPT0(0, "Game Level 1 Destroyed!\n");
	else
		_RPT0(0, "Error when try destroy Game Level 1!\n");
}

bool SceneGameLevel1::DownloadResources()
{
	bool Sucess = ResourceManager::DestroyItemsFromScene(id);
	if (Sucess == true)
		return true;
	else
		return false;
}