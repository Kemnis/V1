#pragma once
#ifndef _Camera3D_H_
#define _Camera3D_H_
using namespace DirectX;

class Camera3D
{
public:
	Camera3D(int screenWidth, int screenHeight, float near, float far);
	~Camera3D();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void GetViewMatrix(XMMATRIX&);
	XMMATRIX* GetProjectionMatrix();
	XMMATRIX* GetProjectionViewMatrix();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Watch();
	XMFLOAT4 view;
protected:
	

	
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	XMMATRIX viewMatrix;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_projetionViewMatrix;

};

#endif