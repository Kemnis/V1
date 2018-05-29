#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "Light.h"
#include "Colision.h"

class GameObject
{
public:
	GameObject(string Name);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model* model);
	bool AssignShader(Shader* shader);
	bool AssignMaterial(Material* mat);
	bool AssignLight(Light* light);
	bool AddTexture(Texture* texture);
	void SetPosBitmap(vec2 Position);
	void SetEscBitmap(vec2 Escale);
	void SetPosBitmap(float PosX, float PosY);
	void SetEscBitmap(float EscX, float EscY);
	Model* GetModel();
	Light* GetLight();
	//Texture* GetTexture();
	bool ExistShader();
	Material* GetMaterial();
	void Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection);
	void DrawPatrol(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void PrecalculatePositions();
	void IsPatrol(vector<vec3> PosicionesPosibles);
	Shader* GetShader();
	void Shutdown();

	void AnimationDamage(double deltaTime, double time);
	void Respawn();
	Colision * GetColision();
	void Collider(GameObject*gameObject, double deltaTime);

	Transforms* Transform;


	bool FilckerBoolean;
	int CountLifes = 3;
	int CountCorazon = 3;

protected:

	string Name, Status;
	Model* Modelo;//Mesh
	std::vector<Texture*> Tex;
	Shader* shader;
	Material* material;
	Light* light;
	vector<vec3> PosPos;
	vector<XMMATRIX> multipleworlds;
	bool ispatrol = false;
	//EnemyBehaviour MyBehaviour();
	Colision * colision;
	int CountFlicker;
	int TimeFlicker = 3;
	float Time = 2;

	bool ColsionAnimation;
	bool Damage = false;
private:

	
};

#endif