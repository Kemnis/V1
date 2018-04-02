#include "stdafx.h"

Camera3D::Camera3D(int screenWidth, int screenHeight, float nearPlane, float farPlane) {
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;

	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;

	view.x = 0.0f;
	view.y = 0.0f;
	view.z = 0.0f;
	view.w = 0.0f;

	// Setup the projection matrix.
	float fieldOfView = 3.141592654f / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, nearPlane, farPlane);
}

Camera3D::~Camera3D() {}

void Camera3D::Watch()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = ResourceManager::Player1->GetPosition().x;
	position.y = ResourceManager::Player1->GetPosition().y;
	position.z = ResourceManager::Player1->GetPosition().z;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = ResourceManager::Player1->GetRotation().x * 0.0174532925f;
	yaw = ResourceManager::Player1->GetRotation().y  * 0.0174532925f;
	roll = ResourceManager::Player1->GetRotation().z  * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	
	//No se porque no funciona pero marca error de acceso a memoria... puede ser porque le falte un Transpose
	//m_projetionViewMatrix = XMMatrixMultiply(m_projectionMatrix, viewMatrix);

	XMStoreFloat4(&view, lookAtVector);

	return;
}

void Camera3D::SetPosition(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
	return;
}


void Camera3D::SetRotation(float x, float y, float z)
{
	rotX = x;
	rotY = y;
	rotZ = z;
	return;
}

XMFLOAT3 Camera3D::GetPosition()
{
	return XMFLOAT3(posX, posY, posZ);
}

XMFLOAT3 Camera3D::GetRotation()
{
	return XMFLOAT3(rotX, rotY, rotZ);
}


void Camera3D::GetViewMatrix(XMMATRIX& cameraViewMatrix)
{
	cameraViewMatrix = viewMatrix;
	return;
}

XMMATRIX * Camera3D::GetProjectionMatrix()
{

	return &m_projectionMatrix;
}

XMMATRIX * Camera3D::GetProjectionViewMatrix()
{
	return &m_projetionViewMatrix;
}

