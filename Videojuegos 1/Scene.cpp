#include "stdafx.h"

Scene::Scene(SpecsDx* From, HWND hWnd) {
	Environment = From;
	hwnd = hWnd;
	AwakeObjects();
}

Scene::~Scene() {}

void Scene::DefineCommonShader() {

}

void Scene::AwakeObjects() {
	SceneCamera = 0;
	TestMesh3D = 0;
	TestShader = 0;
	SceneCamera = new Camera3D(Environment->GetScreenWidth(), Environment->GetScreenHeight(), 0.01f, 100.0f);
	TestMesh3D = new Mesh3D;
	TestShader = new ColorShaderClass;
}

string Scene::CreateScene() {

	// Set the initial position of the camera.
	SceneCamera->SetPosition(0.0f, 0.0f, -5.0f);
	//SceneCamera->Watch();
	/*SceneCamera->SetViewMatrix(CameraMatrix);*/

	// Initialize the model object.
	bool res = TestMesh3D->Initialize(Environment->GetDevice());
	if (!res)
		Error("No se pudo generar el triangulo");
	else
		_RPT0(0,"Triangle created!\n");

	// Initialize the color shader object.
	res = TestShader->Initialize(Environment->GetDevice(), hwnd);
	if (!res)
		Error("No se pudo inicializar el shader");
	else
		_RPT0(0, "Shader created!\n");

	_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

string Scene::ProcessScene()
{
	return "S_OK";
}

string Scene::RenderScene()
{
	XMMATRIX worldMatrix;//, viewMatrix, projectionMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX* projectionMatrix;

	// Clear the buffers to begin the scene.
	Environment->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	SceneCamera->Watch();

	//// Get the world, view, and projection matrices from the camera and d3d objects.
	//Environment->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixIdentity();
	SceneCamera->GetViewMatrix(viewMatrix);
	projectionMatrix = SceneCamera->GetProjectionMatrix();
	//SceneCamera->GetViewMatrix(viewMatrix);
	//Environment->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	TestMesh3D->Render(Environment->GetDeviceContext());

	// Render the model using the color shader.
	RB = TestShader->Render(Environment->GetDeviceContext(), TestMesh3D->GetIndexCount(), &worldMatrix, &viewMatrix, projectionMatrix);
	if (!RB)
		Error("El Shader no pudo renderizar los objetos");

	// Present the rendered scene to the screen.
	Environment->EndScene();
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