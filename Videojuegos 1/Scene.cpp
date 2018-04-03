#include "stdafx.h"

Scene::Scene() {
	SceneCamera = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.01f, 100.0f);
}

Scene::~Scene() {}

string Scene::CreateScene() {
	ResourceManager::Player1 = new KeyHandler(vec3(0,0,5), vec3(0,180,0));
	bool res;

	//Load all objects you need First acubedd all the resources
	ResourceManager::AddModel("Cube", "SphereMesh");
	ResourceManager::AddModel("Sphere.obj", "SphereModel");
	//ResourceManager::LoadShaders();
	ResourceManager::AddTexture("tex1.jpg", "World");
	ResourceManager::AddMaterial("ColorBlanco", vec3(.5, .5, .5));
	//ResourceManager::AddShader("TestShader", Shader("test.vs", "test.ps"));
	ResourceManager::AddShader("TestBasicShader", new BasicShader("testMaterial.vs", "testMaterial.ps"));
	ResourceManager::AddShader("TestMaterialShader", new MaterialShader("testTexture.vs", "testTexture.ps"));

	//ResourceManager::AddStage("Stage1",4,3,12);


	//Then Build a GameObject
	ResourceManager::BuildGameObject("SphereMod", "SphereModel", "World", "TestMaterialShader", "ColorBlanco");
	ResourceManager::BuildGameObject("SphereMes", "SphereMesh", "World", "TestMaterialShader", "ColorBlanco");

				//Descripción:
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(vec3(2, 0, 0));
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetScale(vec3(.5, .5, .5));
				//Descripción:

	_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

string Scene::ProcessScene(double dt)
{
	vec3 rot;
	vec3 trans;
	trans.z = 0.00;
	rot.y = 2 * dt;
	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	ResourceManager::GetObjectByName("SphereMod")->Transform->Translate(trans);
	rot.y = 2 * dt;
	ResourceManager::GetObjectByName("SphereMes")->Transform->Rotate(rot);
	ResourceManager::GetObjectByName("SphereMes")->Transform->Translate(trans);
	return "S_OK";
}

string Scene::RenderScene()
{
	XMMATRIX worldMatrix, Worldobj2;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix;

	// Clear the buffers to begin the scene.
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	worldMatrix = ResourceManager::GetObjectByName("SphereMod")->Transform->ToMatrix();
	Worldobj2 = ResourceManager::GetObjectByName("SphereMes")->Transform->ToMatrix();
	SceneCamera->GetViewMatrix(viewMatrix);
	projectionMatrix = SceneCamera->GetProjectionMatrix();

	//specsDx->TurnOffCulling();
	specsDx->TurnOnAlphaBlending();
	specsDx->TurnZBufferOn();

	//Define and create all Objects
	GameObject* GObjMesh = ResourceManager::GetObjectByName("SphereMes");
	GameObject* GObjModel = ResourceManager::GetObjectByName("SphereMod");

	GObjMesh->Draw(Worldobj2, viewMatrix, *projectionMatrix);
	//Lo ultimo que movi fue el buffer del initialize de MaterialShader para que existieran 3 posiciones incluyendo el 
	//apartado del texture... debe estar ahi el problema de rendereo... intentar con solo hacer calculos con texture
	//sin usar el color del material.

	GObjModel->Draw(worldMatrix, viewMatrix, *projectionMatrix);

	
	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void Scene::DestroyScene()
{
}