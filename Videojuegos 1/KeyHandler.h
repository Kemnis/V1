#pragma once
#include "Input.h"
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

class KeyHandler
{
public:
	KeyHandler(vec3 Pos, vec3 Rot);
	KeyHandler(XMFLOAT3 Pos, XMFLOAT3 Rot);
	~KeyHandler();

	void UpdatePosition(XMFLOAT3 XYZ);
	void UpdatePosition(vec3 XYZ);
	void UpdatePosition(float X, float Y, float Z);
	void UpdateRotation(XMFLOAT3 XYZ);
	void UpdateRotation(vec3 XYZ);
	void UpdateRotation(float X, float Y, float Z);

	void Update();

	vec3 GetPosition();
	vec3 GetRotation();
private:

	vec3 MyPos;
	vec3 MyRot;
	float forceSide, MaxForceSide, forceFront, MaxForceFront;
	Input* Keyboard;
	KeyCode KeyCodes;

	bool ML, MU, MR, MD, MF, MB;
	char Sides, Front;

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUpward();
	void MoveDownward();
};