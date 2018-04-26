#include "stdafx.h"

Scene::Scene() {
	SceneCamera = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.1f, 1000.0f);
}

Scene::~Scene() {}

string Scene::CreateScene() {
	ResourceManager::Player1 = new KeyHandler(vec3(0,0,5), vec3(0,180,0));
	bool res;
	//Load all objects you need First acubedd all the resources
	ResourceManager::AddModel("Sphere", "SphereMesh");
	ResourceManager::AddModel("assets/Sphere.obj", "SphereModel");
	ResourceManager::AddTexture("assets/skydome day1.png", "World");
	ResourceManager::AddTexture("assets/skydome night2.jpg", "WorldNight");
	ResourceManager::AddTexture("assets/terrenopasto.jpg", "Layer1-Bottom");
	ResourceManager::AddTexture("assets/terrenopiedra.jpg", "Layer2-Mid");
	ResourceManager::AddTexture("assets/terrenopasto2.png", "Layer3-Top");
	ResourceManager::AddTexture("assets/arbol.png","ArbolTexture");
	ResourceManager::AddMaterial("ColorBlanco", vec3(0.2, 0.2, 0.4));
	ResourceManager::AddLight("Primeras", vec4(0.1f, 0.8f, 0.8f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f));
	ResourceManager::AddShader("LambertBasicShader", new BasicShader("LambertMaterial.vs", "LambertMaterial.ps"));
	ResourceManager::AddShader("LambertLBasicShader", new BasicShader("LambertLMaterial.vs", "LambertLMaterial.ps",1));
	ResourceManager::AddShader("LambertMaterialShader", new MaterialShader("LambertTexture.vs", "LambertTexture.ps"));
	ResourceManager::AddShader("LambertLMaterialShader", new MaterialShader("LambertLTexture.vs", "LambertLTexture.ps", 1));
	ResourceManager::AddShader("SkydomeShader", new SkydomeShader("Skydome.vs", "Skydome.ps", 1));
	ResourceManager::AddShader("TerrenoShader", new TerrainShader("Terrain.vs", "Terrain.ps"));
	ResourceManager::AddShader("GUIShader", new GUIShader("GUIShader.vsh","GUIShader.psh"));
	ResourceManager::AddStage("assets/Stage2.bmp", "Stage1", 256, 1024, 1024);
	ResourceManager::AddBillboard("ArbolBill",vec2(1.0f,1.0f),vec2(1.0f,1.0f));

	ResourceManager::AddBitmap("Bitmap",vec4(0,0,200,200));
	ResourceManager::AddBitmap("Bitmap2", vec4(0, 0, 200, 200));
	ResourceManager::AddBitmap("Bitmap3", vec4(0, 0, 200, 200));
	ResourceManager::AddBitmap("Bitmap4", vec4(0, 0, 200, 200));
	ResourceManager::AddBitmap("Bitmap5", vec4(0, 0, 200, 200));
	ResourceManager::AddBitmap("Bitmap6", vec4(0, 0, 200, 200));
	ResourceManager::AddBitmap("Bitmap7", vec4(0, 0, 200, 200));


	//Then Build a GameObject
	ResourceManager::BuildGameObject("SphereMes", "SphereMesh", "World", "LambertLMaterialShader", "ColorBlanco","Primeras");
	//ResourceManager::BuildGameObject("SphereMod", "SphereModel", "World", "LambertMaterialShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("SphereMod", "SphereModel", "World", "SkydomeShader", "ColorBlanco", "Primeras");
	ResourceManager::BuildGameObject("Stage1", "Stage1", "", "TerrenoShader", "ColorBlanco","Primeras");
	ResourceManager::BuildGameObject("Arbol","ArbolBill","ArbolTexture","LambertMaterialShader", "ColorBlanco","");
	ResourceManager::BuildGameObject("Arbol2", "ArbolBill", "ArbolTexture", "LambertMaterialShader", "ColorBlanco", "");
	
	ResourceManager::BuildGameObject("bitmapPasto","Bitmap","Layer1-Bottom","GUIShader","ColorBlanco","");
	ResourceManager::BuildGameObject("bitmapArbol", "Bitmap2", "ArbolTexture", "GUIShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("bitmapArbol1", "Bitmap3", "ArbolTexture", "GUIShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("bitmapArbol2", "Bitmap4", "ArbolTexture", "GUIShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("bitmapArbol3", "Bitmap5", "ArbolTexture", "GUIShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("bitmapArbol4", "Bitmap6", "ArbolTexture", "GUIShader", "ColorBlanco", "");

	//Addtexture
	ResourceManager::AsingTextureToGameObject("SphereMod", "WorldNight");
	ResourceManager::AsingTextureToGameObject("Stage1", "Layer1-Bottom");
	ResourceManager::AsingTextureToGameObject("Stage1", "Layer2-Mid");
	ResourceManager::AsingTextureToGameObject("Stage1", "Layer3-Top");

				//Descripci�n:
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetRotation(vec3(180, 0, 0));
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(vec3(2, 0, 0));
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetScale(vec3(.5, .5, .5));
	ResourceManager::GetObjectByName("SphereMod")->Transform->SetScale(vec3(50.0f,50.0f,50.0f));
				//Descripci�n:
	ResourceManager::GetObjectByName("Arbol")->Transform->SetTranslation(vec3(15.0f, 0.0f, 15.0f));
	ResourceManager::GetObjectByName("Arbol2")->Transform->SetTranslation(vec3(30.0f, 0.0f, 30.0f));

	ResourceManager::GetObjectByName("bitmapPasto")->SetRect(vec4(0, 0, 200, 200));
	ResourceManager::GetObjectByName("bitmapArbol")->SetRect(vec4(200, 0, 200, 200));

	_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

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

	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	//ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(trans);
	rot.y = dt;
	move += dt*2.0f;
	trans.x = move;
	trans.y = 0;
	trans.z = move;


	trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("SphereMes")->Transform->Translate(trans);
	
	trans = ResourceManager::GetObjectByName("Arbol")->Transform->GetTranslation();
	trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("Arbol")->Transform->Translate(trans);

	trans = ResourceManager::GetObjectByName("Arbol2")->Transform->GetTranslation();
	trans.y = ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("Arbol2")->Transform->Translate(trans);
	
	return "S_OK";
}

string Scene::RenderScene()
{
	XMMATRIX worldMatrix, Worldobj2, StageWorld, BillboardWorld,viewMatrix2D;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix, *orthoMatrix;

	// Clear the buffers to begin the scene.
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);



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
	specsDx->TurnOffCulling();



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
	bitmapGO->Draw(XMMatrixIdentity(), viewMatrix2D, *orthoMatrix);
	bitmapArbol->Draw(XMMatrixIdentity(), viewMatrix2D, *orthoMatrix);
	specsDx->TurnZBufferOn();


	//Renderizar Bitmap 2D

	//Para que los Bitmap 2D esten fijos en la pantalla se necesita un nuevo viewMatrix que siempre esten en el origen y una matrix ortografica

	//El vertexbuffer del mesh de la clase model debe de ser dinamico

	//Un shader exclusivo para el GUI

	
	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void Scene::DestroyScene()
{
}