#include "stdafx.h"

Scene::Scene() {
	SceneCamera = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.01f, 100.0f);
}

Scene::~Scene() {}

string Scene::CreateScene() {
	SceneCamera->SetPosition(0.0f, 0.0f, -5.0f);
	bool res;

	//Load all objects you need First add all the resources
	//ResourceManager::AddMesh("Triangle", "SphereMesh");
	ResourceManager::AddModel("Triangle", "SphereMesh");
	ResourceManager::AddModel("Sphere.obj", "SphereModel");
	ResourceManager::AddShader();
	ResourceManager::AddTexture("tex1.jpg", "World");
	ResourceManager::AddMaterial("ColorBlanco", vec3(1, 1, 1));

	//Then Build a GameObject
	ResourceManager::BuildGameObject("SphereMod", "SphereModel", "", "Shader", "ColorBlanco");
	ResourceManager::BuildGameObject("SphereMes", "SphereMesh", "", "Shader", "ColorBlanco");

				//Descripción:
	ResourceManager::GetObjectByName("SphereMes")->Transform->SetTranslation(vec3(2, 0, 0));
				//Descripción:

	_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

string Scene::ProcessScene(double dt)
{
	vec3 rot;
	rot.y = 4 * dt;
	ResourceManager::GetObjectByName("SphereMod")->Transform->Rotate(rot);
	rot.y = 2 * dt;
	ResourceManager::GetObjectByName("SphereMes")->Transform->Rotate(rot);
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


	//Define and create all Objects
	GameObject* GObjMesh = ResourceManager::GetObjectByName("SphereMes");
	GameObject* GObjModel = ResourceManager::GetObjectByName("SphereMod");

	GObjMesh->GetShader()->SetShaderParameters(Worldobj2, viewMatrix, *projectionMatrix, GObjMesh->GetMaterial());
	ResourceManager::bindShader(GObjMesh);
	ResourceManager::bindModel(GObjModel);
	GObjMesh->GetModel()->Draw();

	GObjModel->GetShader()->SetShaderParameters(worldMatrix, viewMatrix, *projectionMatrix, GObjModel->GetMaterial());
	ResourceManager::bindShader(GObjModel);
	ResourceManager::bindModel(GObjModel);
	GObjModel->GetModel()->Draw();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void Scene::DestroyScene()
{
}