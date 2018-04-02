#include "stdafx.h"
KeyHandler::KeyHandler(vec3 Pos, vec3 Rot)
{
	MyPos = { Pos.x,Pos.y,Pos.z };
	MyRot = { Rot.x,Rot.y,Rot.z };
	forceSide = 0, forceFront = 0;
	MaxForceSide = 1.3,	MaxForceFront = 1.3;
	Keyboard = new Input();
	ML=false, MR=false, MU=false, MD=false, MF=false, MB=false;
	Sides = 'N', Front = 'N';
}
KeyHandler::KeyHandler(XMFLOAT3 Pos, XMFLOAT3 Rot)
{
	MyPos = { Pos.x,Pos.y,Pos.z };
	MyRot = { Rot.x,Rot.y,Rot.z };
	forceSide = 0, forceFront = 0;
	MaxForceSide = 1.3, MaxForceFront = 1.3;
	Keyboard = new Input();
	ML = false, MR = false, MU = false, MD = false, MF = false, MB = false;
	Sides = 'N', Front = 'N';
}
KeyHandler::~KeyHandler() {}

void KeyHandler::UpdatePosition(XMFLOAT3 XYZ)
{
	MyPos = { XYZ.x,XYZ.y,XYZ.z };
}
void KeyHandler::UpdatePosition(vec3 XYZ) 
{
	MyPos = XYZ;
}
void KeyHandler::UpdatePosition(float X, float Y, float Z)
{
	MyPos = {X,Y,Z};
}

void KeyHandler::UpdateRotation(XMFLOAT3 XYZ)
{
	MyRot = { XYZ.x,XYZ.y,XYZ.z };
}
void KeyHandler::UpdateRotation(vec3 XYZ)
{
	MyRot = XYZ;
}
void KeyHandler::UpdateRotation(float X, float Y, float Z)
{
	MyRot = { X,Y,Z };
}

vec3 KeyHandler::GetPosition() 
{
	return MyPos;
}

vec3 KeyHandler::GetRotation()
{
	return MyRot;
}

void KeyHandler::Update()
{
	Keyboard->Update();
	//Smoot Movement X
	if (Keyboard->KEYS[KeyCodes.A] || Keyboard->KEYS[KeyCodes.Left]
		|| Keyboard->KEYS[KeyCodes.D] || Keyboard->KEYS[KeyCodes.Right])
	{
		if (forceSide < MaxForceSide)
			forceSide += 0.01f;
	}
	else
	{
		if (forceSide > 0.01)
		{
			if(forceSide > 0.26)
				forceSide -= 0.13f;
			else
				forceSide -= 0.008f;
		}
		else
		{
			Sides = 'N';
		}
		
		if (Sides == 'L')
			MoveLeft();
		else if (Sides == 'R')
			MoveRight();
	}

	//Smoot Movement Z
	if (Keyboard->KEYS[KeyCodes.W] || Keyboard->KEYS[KeyCodes.Up] ||
		Keyboard->KEYS[KeyCodes.S] || Keyboard->KEYS[KeyCodes.Down])
	{
		if (forceFront < MaxForceFront)
			forceFront += 0.01f;
	}
	else
	{
		if (forceFront > 0.01)
		{
			if (forceFront > 0.26)
				forceFront -= 0.13f;
			else
				forceFront -= 0.008f;
		}
		else
		{
			Front = 'N';
		}
		if (Front == 'F')
			MoveForward();
		else if (Front == 'B')
			MoveBackward();
	}

	if (Keyboard->KEYS[KeyCodes.A] || Keyboard->KEYS[KeyCodes.Left])
		MoveLeft();
	if (Keyboard->KEYS[KeyCodes.W] || Keyboard->KEYS[KeyCodes.Up])
		MoveForward();
	if (Keyboard->KEYS[KeyCodes.S] || Keyboard->KEYS[KeyCodes.Down])
		MoveBackward();
	if (Keyboard->KEYS[KeyCodes.D] || Keyboard->KEYS[KeyCodes.Right])
		MoveRight();
}


void KeyHandler::MoveForward()
{
	float radians;
	Front = 'F';
	// Convert degrees to radians.
	radians = MyRot.y * 0.0174532925f;

	// Update the position.
	MyPos.x += sinf(radians) * forceFront;
	MyPos.z += cosf(radians) * forceFront;
}

void KeyHandler::MoveBackward()
{
	float radians;
	Front = 'B';
	// Convert degrees to radians.
	radians = MyRot.y * 0.0174532925f;

	// Update the position.
	MyPos.x -= sinf(radians) * forceFront;
	MyPos.z -= cosf(radians) * forceFront;
}

void KeyHandler::MoveLeft()
{
	float radians;
	Sides = 'L';
	// Convert degrees to radians.
	radians = MyRot.y * 0.0174532925f;

	// Update the position.
	MyPos.x -= sinf(radians + (XM_PI*0.5f)) * forceSide;
	MyPos.z -= cosf(radians + (XM_PI*0.5f)) * forceSide;
}

void KeyHandler::MoveRight()
{
	float radians;
	Sides = 'R';
	// Convert degrees to radians.
	radians = MyRot.y * 0.0174532925f;

	// Update the position.
	MyPos.x -= sinf(radians - (XM_PI*0.5f)) * forceSide;
	MyPos.z -= cosf(radians - (XM_PI*0.5f)) * forceSide;
}

void KeyHandler::MoveUpward()
{
	// Update the height position.
	MyPos.y += forceFront;
}

void KeyHandler::MoveDownward()
{
	// Update the height position.
	MyPos.y -= forceFront;
}