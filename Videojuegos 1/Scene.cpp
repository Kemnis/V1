#include "stdafx.h"
//Escena defualt para hacer desmadre en el examen
Scene::Scene(string id) {
	SceneCamera = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.1f, 1000.0f);
	this->id = id;
}

Scene::~Scene() {}

//Main instruction to Initialize a Scene
string Scene::CreateScene() {
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
string Scene::LoadResources()
{
	RB = ResourceManager::AddModel(id, "Sphere", "SphereMesh");
	RB = ResourceManager::AddModel(id, "assets/Sphere.obj", "SphereModel");
	RB = ResourceManager::AddStage(id, "assets/Stage1.bmp", "Stage1", 256, 1024, 1024);

	RB = ResourceManager::AddTexture(id, "assets/SkyStage1Day.jpg", "World");
	RB = ResourceManager::AddTexture(id, "assets/SkyStage1Night.jpg", "WorldNight");
	RB = ResourceManager::AddTexture(id, "assets/mt1Stage1.jpg", "Layer1-Bottom");
	RB = ResourceManager::AddTexture(id, "assets/mt2Stage1.jpg", "Layer2-Mid");
	RB = ResourceManager::AddTexture(id, "assets/mt3Stage1.jpg", "Layer3-Top");
	RB = ResourceManager::AddTexture(id, "assets/TreeTex.png", "ArbolTexture");
	RB = ResourceManager::AddMaterial(id, "ColorBlanco", vec3(0.2, 0.2, 0.4));

	RB = ResourceManager::AddLight(id, "Luz", vec4(0.1f, 0.8f, 0.8f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f));
	RB = ResourceManager::AddShader(id, "LambertBasicShader", new BasicShader("LambertMaterial.vs", "LambertMaterial.ps"));
	RB = ResourceManager::AddShader(id, "LambertLBasicShader", new BasicShader("LambertLMaterial.vs", "LambertLMaterial.ps", 1));
	RB = ResourceManager::AddShader(id, "LambertMaterialShader", new MaterialShader("LambertTexture.vs", "LambertTexture.ps"));
	RB = ResourceManager::AddShader(id, "LambertLMaterialShader", new MaterialShader("LambertLTexture.vs", "LambertLTexture.ps", 1));
	RB = ResourceManager::AddShader(id, "SkydomeShader", new SkydomeShader("Skydome.vs", "Skydome.ps", 1));
	RB = ResourceManager::AddShader(id, "TerrenoShader", new TerrainShader("Terrain.vs", "Terrain.ps"));
	RB = ResourceManager::AddShader(id, "GUIShader", new GUIShader("GUIShader.vsh", "GUIShader.psh"));
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
string Scene::BuildScene()
{
	RS = ResourceManager::BuildGameObject(id, "SphereMes", "SphereMesh", "World", "LambertLMaterialShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "SphereMod", "SphereModel", "World", "SkydomeShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "Stage1", "Stage1", "", "TerrenoShader", "ColorBlanco", "Luz");
	RS = ResourceManager::BuildGameObject(id, "Arbol", "Billboard", "ArbolTexture", "LambertMaterialShader", "ColorBlanco", "");
	RS = ResourceManager::BuildGameObject(id, "Arbol2", "Billboard", "ArbolTexture", "LambertMaterialShader", "ColorBlanco", "");
	RS = ResourceManager::BuildGameObject(id, "bitmapPasto", "Bitmap00", "Layer1-Bottom", "GUIShader", "ColorBlanco", "");
	RS = ResourceManager::BuildGameObject(id, "bitmapArbol", "Bitmap01", "ArbolTexture", "GUIShader", "ColorBlanco", "");

	//Addtexture
	RS = ResourceManager::AsingTextureToGameObject("SphereMod", "WorldNight");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer1-Bottom");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer2-Mid");
	RS = ResourceManager::AsingTextureToGameObject("Stage1", "Layer3-Top");

	RS = ResourceManager::LoadLetters(id, "assets/Abecedario10x10/", "AHLO");
	RS = ResourceManager::BuildWord(id, "Palabra1", "HOLA", vec2(20, 0));

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
string Scene::Start() {
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetRotation(vec3(180, 0, 0));
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(vec3(2, 0, 0));
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetScale(vec3(.5, .5, .5));

	ResourceManager::GetObjectByName("SphereMod")->Transform->SetScale(vec3(50.0f, 50.0f, 50.0f));

	ResourceManager::GetObjectByName("Arbol")->Transform->SetTranslation(vec3(15.0f, 0.0f, 15.0f));

	ResourceManager::GetObjectByName("Arbol2")->Transform->SetTranslation(vec3(30.0f, 0.0f, 30.0f));

	ResourceManager::GetObjectByName("bitmapPasto")->GetModel()->SetRect(vec4(0, 0, 200, 200));

	ResourceManager::GetObjectByName("bitmapArbol")->GetModel()->SetRect(vec4(200, 0, 200, 200));

	vec3 trans;
	trans = ResourceManager::GetObjectByName("Arbol")->Transform->GetTranslation();
	trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("Arbol")->Transform->SetTranslation(trans);

	trans = ResourceManager::GetObjectByName("Arbol2")->Transform->GetTranslation();
	trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("Arbol2")->Transform->SetTranslation(trans);


	return "S_OK";
}

//Then Process all the changes of everything and every object
string Scene::ProcessScene(double dt)
{
	vec3 rot;
	vec3 trans;
	trans.z = 0.00;
	rot.y = dt;
	//Para cambiar dia y noche
	static float ambiente = 0.0f;
	static float move = 0.0f;
	

	ResourceManager::GetMaterial("ColorBlanco")->escalar = sinf(ambiente*0.0174532925f);

	if (ambiente > 359)
		ambiente -= 359;
	ambiente += dt*10.0f;

	//ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	////ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(trans);
	//rot.y = dt;
	//move += dt*2.0f;
	//trans.x = move;
	//trans.y = 0;
	//trans.z = move;


	//trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	//ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(trans);
	

	
	return "S_OK";
}

//Finally Render it
string Scene::RenderScene()
{
	// Clear the buffers to begin the scene.
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	XMMATRIX worldMatrix, Worldobj2, StageWorld, BillboardWorld,viewMatrix2D;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix, *orthoMatrix;

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();
	SceneCamera->GetViewMatrix(viewMatrix);
	SceneCamera->GetViewMatrix2D(viewMatrix2D);
	orthoMatrix = SceneCamera->GetOrthoMatrix();
	projectionMatrix = SceneCamera->GetProjectionMatrix();

	ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Worldobj2 = ResourceManager::GetObjectByName("SphereMes")->Transform->ToMatrix();
	worldMatrix = ResourceManager::GetObjectByName("SphereMod")->Transform->ToMatrix();
	StageWorld = ResourceManager::GetObjectByName("Stage1")->Transform->ToMatrix();


	//Define and create all Objects
	GameObject* GObjMesh = ResourceManager::GetObjectByName("SphereMes");
	GameObject* GObjModel = ResourceManager::GetObjectByName("SphereMod");
	GameObject* GOStage = ResourceManager::GetObjectByName("Stage1");
	GameObject* bitmapGO = ResourceManager::GetObjectByName("bitmapPasto");
	GameObject* bitmapArbol = ResourceManager::GetObjectByName("bitmapArbol");

	if (GOStage->GetModel()->isIntoTerrain(GObjMesh->Transform->GetTranslation()))
	{
		float height = GOStage->GetModel()->GetPositionHeightMap(GObjMesh->Transform->GetTranslation());

		if (GObjMesh->Transform->GetTranslation().y<height)
		{
			GObjMesh->Transform->SetTranslation(vec3(GObjMesh->Transform->GetTranslation().x, height, GObjMesh->Transform->GetTranslation().z));
		}
	}



	
	specsDx->TurnOnAlphaBlending();
		specsDx->TurnOffCulling();
			specsDx->TurnZBufferOff();
				GObjModel->Draw(worldMatrix, viewMatrix, *projectionMatrix);
			specsDx->TurnZBufferOn();
		specsDx->TurnOnCulling();



	GObjMesh->Draw(Worldobj2, viewMatrix, *projectionMatrix);


	GameObject* GOArbol = ResourceManager::GetObjectByName("Arbol");
	GameObject* GOArbol2 = ResourceManager::GetObjectByName("Arbol2");

	//Hacer una lista de puros billboards
	GOArbol->Transform->LookCamera(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));
	BillboardWorld = GOArbol->Transform->ToMatrix();
	BillboardWorld = XMMatrixTranslation(0.0f, GOArbol->GetModel()->coordPositivo.y, 0.0f)*BillboardWorld;
	GOArbol->Draw(BillboardWorld, viewMatrix, *projectionMatrix);

	GOArbol2->Transform->LookCamera(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));
	BillboardWorld = GOArbol2->Transform->ToMatrix();
	BillboardWorld = XMMatrixTranslation(0.0f, GOArbol2->GetModel()->coordPositivo.y, 0.0f)*XMMatrixScaling(10.0f,10.0f,10.0f)*BillboardWorld;
	GOArbol2->Draw(BillboardWorld, viewMatrix, *projectionMatrix);



	GOStage->Draw(StageWorld, viewMatrix, *projectionMatrix);


	specsDx->TurnZBufferOff();
		//bitmapGO->Draw(XMMatrixIdentity(), viewMatrix2D, *orthoMatrix);
		//bitmapArbol->Draw(XMMatrixIdentity(), viewMatrix2D, *orthoMatrix);
	specsDx->TurnZBufferOn();


	//Renderizar Bitmap 2D

	//Para que los Bitmap 2D esten fijos en la pantalla se necesita un nuevo viewMatrix que siempre esten en el origen y una matrix ortografica

	//El vertexbuffer del mesh de la clase model debe de ser dinamico

	//Un shader exclusivo para el GUI

	
	// Present the rendered scene to the screen.
	specsDx->TurnZBufferOff();
	GameObject* words[10];
	int Letras = 0;
	string identifier = "Palabra1";
	while (Letras != 4)
	{
		string str = "HOLA";
		for (char& c : str) {
			words[Letras] = ResourceManager::GetObjectByName(identifier + c);
			words[Letras]->Draw(XMMatrixIdentity(), viewMatrix2D, *orthoMatrix);
			Letras++;
		}
	}
	specsDx->TurnZBufferOn();
	specsDx->EndScene();
	return "S_OK";
}

//Destroys all the objects that were created
void Scene::DestroyScene()
{
	RB = DownloadResources();
	if (RB == true)
		_RPT0(0, "Scene Test Destroyed!\n");
	else
		_RPT0(0, "Error when try destroy Scene Test!\n");
}

bool Scene::DownloadResources()
{
	bool Sucess = ResourceManager::DestroyItemsFromScene(id);
	if (Sucess == true)
		return true;
	else
		return false;
}