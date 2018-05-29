#include "stdafx.h"
KeyHandler::KeyHandler(vec3 Pos, vec3 Rot)
{
	MyPos = { Pos.x,Pos.y,Pos.z };
	MyRot = { Rot.x,Rot.y,Rot.z };
	forceSide = 0, forceFront = 0;
	MaxForceSide = 1.3,	MaxForceFront = 1.3;
	LookLR = 0, LookLRMax = 1;
	LookUD = 0, LookUDMax = 1;
	TurnLR = 0, TurnLRMax = 1.5;
	FlyUD = 0, FlyUDMax = 1;
	Keyboard = new Input();
	Keyboard->Initialize(0,0);
	Sides = 'N', Front = 'N', LSide = 'N', LFront = 'N';
	thridPerson = false;
	focus = NULL;
	focus = NULL;
}
KeyHandler::KeyHandler(XMFLOAT3 Pos, XMFLOAT3 Rot)
{
	MyPos = { Pos.x,Pos.y,Pos.z };
	MyRot = { Rot.x,Rot.y,Rot.z };
	forceSide = 0, forceFront = 0;
	MaxForceSide = 1.3, MaxForceFront = 1.3;
	LookLR = 0, LookLRMax = 1;
	LookUD = 0, LookUDMax = 1;
	TurnLR = 0, TurnLRMax = 1.5;
	FlyUD = 0, FlyUDMax = 1;
	Keyboard = new Input();
	Keyboard->Initialize(0, 0);
	Sides = 'N', Front = 'N', LSide = 'N', LFront = 'N';
	thridPerson = false;
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

void KeyHandler::Update(int * scene)
{
	Keyboard->Update();

	switch (*scene)
	{
	case 0:
		KeyEventLevel(scene);
		return;
	case 1:
		KeyEventMenu(scene);
		return;
	case 2:
		KeyEventLevel(scene);
		return;
	}
	
	return;
}

void KeyHandler::LookUpward()
{
	// Update the rotation.
	MyRot.x -= LookUD;
	LFront = 'U';
	// Keep the rotation maximum 90 degrees.
	if (MyRot.x > 90.0f)
	{
		MyRot.x = 90.0f;
	}
}

void KeyHandler::LookDownward()
{
	// Update the rotation.
	MyRot.x += LookUD;
	LFront = 'D';
	// Keep the rotation maximum 90 degrees.
	if (MyRot.x < -90.0f)
	{
		MyRot.x = -90.0f;
	}
}

void KeyHandler::LookLeft()
{
	// Update the rotation.
	MyRot.z += LookLR;
	LSide = 'L';
	// Keep the rotation maximum 90 degrees.
	if (MyRot.z > 90.0f)
	{
		MyRot.z = 90.0f;
	}
}

void KeyHandler::LookRight()
{
	// Update the rotation.
	MyRot.z -= LookLR;
	LSide = 'R';
	// Keep the rotation maximum 90 degrees.
	if (MyRot.z < -90.0f)
	{
		MyRot.z = -90.0f;
	}
}

void KeyHandler::FlyUpward()
{
	Fly = 'U';
	// Update the height position.
	MyPos.y += FlyUD;
}

void KeyHandler::FlyDownward()
{
	Fly = 'D';
	// Update the height position.
	MyPos.y -= FlyUD;
}

void KeyHandler::TurnLeft()
{
	Turn = 'L';
	// Update the rotation.
	MyRot.y -= TurnLR;

	// Keep the rotation in the 0 to 360 range.
	if (MyRot.y < 0.0f)
		MyRot.y += 360.0f;
}

void KeyHandler::TurnRight()
{
	Turn = 'R';
	// Update the rotation.
	MyRot.y += TurnLR;

	// Keep the rotation in the 0 to 360 range.
	if (MyRot.y < 360.0f)
		MyRot.y -= 360.0f;
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

void KeyHandler::KeyEventMenu(int *changeScene)
{
	if (Keyboard->KEYSDOWN[KeyCodes.Enter])
	{
		*changeScene = 2;
	}
}

void KeyHandler::KeyEventLevel(int *changeScene)
{
	if (Keyboard->KEYSDOWN[KeyCodes.Enter])
	{
		*changeScene = 1;
	}

	//Smoot Movement X
	if (Keyboard->KEYS[KeyCodes.Left] || Keyboard->KEYS[KeyCodes.Right])
	{
		if (forceSide < MaxForceSide)
			forceSide += 0.01f;
	}
	else
	{
		if (forceSide > 0.01)
		{
			if (forceSide > 0.3)
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

	//Smoot Look X
	if (Keyboard->KEYS[KeyCodes.Q] || Keyboard->KEYS[KeyCodes.E])
	{
		if (LookLR < LookLRMax)
			LookLR += 0.03f;
	}
	else
	{
		if (LookLR > 0.01)
		{
			if (LookLR > 0.3)
				LookLR -= 0.13f;
			else
				LookLR -= 0.008f;
		}
		else
		{
			LSide = 'N';
		}

		if (LSide == 'L')
			LookLeft();
		else if (LSide == 'R')
			LookRight();
	}

	//Smoot Turn X
	if (Keyboard->KEYS[KeyCodes.A] || Keyboard->KEYS[KeyCodes.D])
	{
		if (TurnLR < TurnLRMax)
			TurnLR += 0.03f;
	}
	else
	{
		if (TurnLR > 0.01)
		{
			if (TurnLR > 0.3)
				TurnLR -= 0.13f;
			else
				TurnLR -= 0.008f;
		}
		else
		{
			Turn = 'N';
		}

		if (Turn == 'L')
			TurnLeft();
		else if (Turn == 'R')
			TurnRight();
	}

	//Smoot Fly Y
	if (Keyboard->KEYS[KeyCodes.Control] || Keyboard->KEYS[KeyCodes.Z])
	{
		if (FlyUD < FlyUDMax)
			FlyUD += 0.002f;
	}
	else
	{
		if (FlyUD > 0.01f)
		{
			if (FlyUD > 0.02)
				FlyUD -= 0.02f;
			else
				FlyUD -= 0.01f;
		}
		else
		{
			Fly = 'N';
		}

		if (Fly == 'U')
			FlyUpward();
		else if (Fly == 'D')
			FlyDownward();
	}

	//Smoot Movement Z
	if (Keyboard->KEYS[KeyCodes.Up] || Keyboard->KEYS[KeyCodes.Down])
	{
		if (forceFront < MaxForceFront)
			forceFront += 0.01f;
	}
	else
	{
		if (forceFront > 0.01)
		{
			if (forceFront > 0.3)
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

	//Smoot Look Z
	if (Keyboard->KEYS[KeyCodes.W] || Keyboard->KEYS[KeyCodes.S])
	{
		if (LookUD < LookUDMax)
			LookUD += 0.03f;
	}
	else
	{
		if (LookUD > 0.01)
		{
			if (LookUD > 0.3)
				LookUD -= 0.13f;
			else
				LookUD -= 0.008f;
		}
		else
		{
			LFront = 'N';
		}
		if (LFront == 'U')
			LookUpward();
		else if (LFront == 'D')
			LookDownward();
	}

	if (/*Keyboard->KEYS[KeyCodes.A] ||*/ Keyboard->KEYS[KeyCodes.Left])
		MoveLeft();
	if (/*Keyboard->KEYS[KeyCodes.W] ||*/ Keyboard->KEYS[KeyCodes.Up])
		MoveForward();
	if (/*Keyboard->KEYS[KeyCodes.S] ||*/ Keyboard->KEYS[KeyCodes.Down])
		MoveBackward();
	if (/*Keyboard->KEYS[KeyCodes.D] ||*/ Keyboard->KEYS[KeyCodes.Right])
		MoveRight();
	if (Keyboard->KEYS[KeyCodes.Control])
		FlyUpward();
	if (Keyboard->KEYS[KeyCodes.Z])
		FlyDownward();

	if (Keyboard->KEYS[KeyCodes.Q])
		LookLeft();
	if (Keyboard->KEYS[KeyCodes.A] /*|| Keyboard->KEYS[KeyCodes.Left]*/)
		TurnLeft();
	if (Keyboard->KEYS[KeyCodes.W] /*|| Keyboard->KEYS[KeyCodes.Up]*/)
		LookUpward();
	if (Keyboard->KEYS[KeyCodes.S] /*|| Keyboard->KEYS[KeyCodes.Down]*/)
		LookDownward();
	if (Keyboard->KEYS[KeyCodes.D] /*|| Keyboard->KEYS[KeyCodes.Right]*/)
		TurnRight();
	if (Keyboard->KEYS[KeyCodes.E])
		LookRight();

	//Change Model Camera
	if (Keyboard->KEYSDOWN[KeyCodes.One])
		thridPerson = false;
	if (Keyboard->KEYSDOWN[KeyCodes.Three])
		thridPerson = true;
	if(Keyboard->KEYSDOWN[KeyCodes.Space])
	{
		if(focus==NULL)
		focus = ResourceManager::GetObjectByName("BotEnemy");
		else focus = NULL;
	}
		
}

void KeyHandler::LookAtObject(vec3 posPlayer, vec3 focus)
{
	vec3 rot = ResourceManager::LookAt(posPlayer, focus);
	MyRot.y = rot.y - 180;
	MyRot.x = rot.z - 90;
}