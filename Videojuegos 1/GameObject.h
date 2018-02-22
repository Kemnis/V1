#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
class GameObject
{
public:
	GameObject();
	~GameObject();

	bool AssignMesh();
	bool AssignShader();
	bool AssignTexture();

	void Shutdown();	

protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta

	
private:
};

#endif