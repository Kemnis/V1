#include "stdafx.h"

Scene::Scene() {
	SceneCamera = 0;
	TestMesh3D = 0;
	TestShader = 0;
	SceneCamera = new Camera3D(specsDx->GetScreenWidth(), specsDx->GetScreenHeight(), 0.01f, 100.0f);
	TestMesh3D = new Mesh3D;
	TestShader = new ShaderClass;
}

Scene::~Scene() {}

string Scene::CreateScene() {

	SceneCamera->SetPosition(0.0f, 0.0f, -5.0f);
	bool res;
	/*res = TestMesh3D->Initialize();
	if (!res)
		ErrorFnc("No se pudo generar el triangulo");
	else
		_RPT0(0,"Triangle created!\n");*/
	ResourceManager::AddMesh("Sphere", "triangle");
	ResourceManager::BuildGameObject("triangle", -1, 0, -1, -1);
	GObj = ResourceManager::GetObjectByName("triangle");
	//ResourceManager::AddMesh(*TestMesh3D,"triangulo");
	res = TestShader->Initialize();
	if (!res)
		ErrorFnc("No se pudo inicializar el shader");
	else
		_RPT0(0, "Shader created!\n");

	_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

string Scene::ProcessScene(double dt)
{
	vec3 rot;
	rot.y = 4*dt;
	TestMesh3D->transform->Rotate(rot);

	return "S_OK";
}

string Scene::RenderScene()
{
	XMMATRIX worldMatrix;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix;

	// Clear the buffers to begin the scene.
	specsDx->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	worldMatrix = TestMesh3D->transform->ToMatrix();
	SceneCamera->GetViewMatrix(viewMatrix);
	projectionMatrix = SceneCamera->GetProjectionMatrix();

	TestShader->SetShaderParameters(worldMatrix, viewMatrix, *projectionMatrix);

	ResourceManager::bindShader(TestShader);
	//ResourceManager::AddTexture("tex1","World");
	//ResourceManager::BuildGameObject(0,0,0,"modelo1");
	ResourceManager::bindMesh(GObj->GetMesh());

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	GObj->GetMesh()->Draw();

	// Present the rendered scene to the screen.
	specsDx->EndScene();
	return "S_OK";
}

void Scene::DestroyScene()
{
	// Release the model object.
	if (TestMesh3D)
	{
		TestMesh3D->Shutdown();
		delete TestMesh3D;
		TestMesh3D = 0;
	}

	// Release the color shader object.
	if (TestShader)
	{
		TestShader->Shutdown();
		delete TestShader;
		TestShader = 0;
	}
}