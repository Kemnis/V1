#include "stdafx.h"

Scene::Scene() {
	SceneCamera = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.01f, 1000.0f);
}

Scene::~Scene() {}

string Scene::CreateScene() {
	ResourceManager::Player1 = new KeyHandler(vec3(0,0,5), vec3(0,180,0));
	bool res;

	//Load all objects you need First acubedd all the resources
	ResourceManager::AddModel("Sphere", "SphereMesh");
	ResourceManager::AddModel("assets/Sphere.obj", "SphereModel");
	ResourceManager::AddTexture("assets/skydome day1.png", "World");
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
	ResourceManager::AddShader("TerrenoShader", new TerrainShader("Terrain.vs", "Terrain.ps"));
	ResourceManager::AddStage("assets/Stage2.bmp", "Stage1", 256, 1024, 1024);
	ResourceManager::AddBillboard("ArbolBill",vec2(1.0f,1.0f),vec2(1.0f,1.0f));


	//Then Build a GameObject
	ResourceManager::BuildGameObject("SphereMes", "SphereMesh", "World", "LambertLMaterialShader", "ColorBlanco","Primeras");
	ResourceManager::BuildGameObject("SphereMod", "SphereModel", "World", "LambertMaterialShader", "ColorBlanco", "");
	ResourceManager::BuildGameObject("Stage1", "Stage1", "", "TerrenoShader", "ColorBlanco","Primeras");
	ResourceManager::BuildGameObject("Arbol","ArbolBill","ArbolTexture","LambertMaterialShader", "ColorBlanco","");


	//Addtexture
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

	//if (ambiente > 359)
	//	ambiente -= 359;
	//ambiente += dt*10.0f;

	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	//ResourceManager::GetObjectByName("SphereMod")->Transform->SetTranslation(trans);
	rot.y = dt;
	move += dt*2.0f;
	trans.x = move;
	trans.y = 0;
	trans.z = move;

	//ResourceManager::GetObjectByName("SphereMes")->Transform->Rotate(rot);
	//trans = ResourceManager::GetObjectByName("SphereMes")->Transform->GetTranslation();
	if (ResourceManager::GetObjectByName("Stage1")->GetModel()->isIntoTerrain(trans)&& trans.y<ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec2(trans.x, trans.z)))
	{
		while(trans.y < ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec2(trans.x, trans.z)))
			trans.y+=0.1f;
	}

	ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(trans);
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(trans);
	
	trans = ResourceManager::GetObjectByName("Arbol")->Transform->GetTranslation();
	if(ResourceManager::GetObjectByName("Stage1")->GetModel()->isIntoTerrain(trans) && trans.y<ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec2(trans.x, trans.z)))
	{

		while (trans.y < ResourceManager::GetObjectByName("Stage1")->GetModel()->GetPositionHeightMap(vec2(trans.x, trans.z)))
			trans.y += 0.1f;
		
	}

	ResourceManager::GetObjectByName("Arbol")->Transform->SetTranslation(trans);
	
	return "S_OK";
}

string Scene::RenderScene()
{
	XMMATRIX worldMatrix, Worldobj2, StageWorld, BillboardWorld;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix;

	// Clear the buffers to begin the scene.
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);



	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();
	SceneCamera->GetViewMatrix(viewMatrix);
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
	

	if (GOStage->GetModel()->isIntoTerrain(GObjMesh->Transform->GetTranslation()))
	{
		float height = GOStage->GetModel()->GetPositionHeightMap(vec2(GObjMesh->Transform->GetTranslation().x, GObjMesh->Transform->GetTranslation().z));

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

	//Hacer una lista de puros billboards
	GOArbol->Transform->LookCamera(vec3(SceneCamera->view.x, SceneCamera->view.y, SceneCamera->view.z));
	BillboardWorld = GOArbol->Transform->ToMatrix();
	BillboardWorld = BillboardWorld * XMMatrixTranslation(0.0f, GOArbol->GetModel()->coordPositivo.y, 0.0f);
	GOArbol->Draw(BillboardWorld, viewMatrix, *projectionMatrix);

	GOStage->Draw(StageWorld, viewMatrix, *projectionMatrix);

	
	
	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void Scene::DestroyScene()
{
}