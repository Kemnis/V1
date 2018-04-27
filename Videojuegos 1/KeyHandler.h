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

	void Update(int *scene);

	vec3 GetPosition();
	vec3 GetRotation();
private:
	void KeyEventMenu(int *changeScene);
	void KeyEventLevel(int *changeScene);
	vec3 MyPos;
	vec3 MyRot;
	float forceSide, MaxForceSide, forceFront, MaxForceFront;
	float LookLR, LookLRMax, LookUD, LookUDMax;
	float TurnLR, TurnLRMax;
	double FlyUD, FlyUDMax;
	Input* Keyboard;
	KeyCode KeyCodes;

	char Sides, Front, LSide, LFront, Turn, Fly;

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void FlyUpward();
	void FlyDownward();
	void LookUpward();
	void LookDownward();
	void TurnLeft();
	void TurnRight();
	void LookLeft();
	void LookRight();
};