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
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model* model);
	bool AssignShader(Shader* shader);
	bool AssignMaterial(Material* mat);
	bool AssignLight(Light* light);
	bool AddTexture(Texture* texture);
	Model* GetModel();
	Light* GetLight();
	//Texture* GetTexture();
	bool ExistShader();
	Material* GetMaterial();
	void Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection);
	Shader* GetShader();
	void Shutdown();	

	//Methods bitmaps
	void SetRect(vec4 rectBitmap);
	void SetPosition(vec2 position);
	//void SetPositionCenter(vec2 position);
	void SetSize(vec2 size);
	//Methods bitmaps
	//vec4 getRect();
	//vec2 getPositon();
	//vec2 getPisitionCenter();
	//vec2 getSize();
	void UpdateBitmap();
	
	Transforms* Transform;


protected:
	
	string Name, Status;
	Model* Modelo;//Mesh
	std::vector<Texture*> Tex;
	Shader* shader;
	Material* material;
	Light* light;
private:
	//Measure
	int m_screenWidth, m_screenHeight;

	//previous
	int m_previousWidth, m_previousHeight;
	int m_previousPosX, m_previousPosY;
	int PosX, PosY;

	int m_bitmapWidth, m_bitmapHeight;
	int CenterX, CenterY;
};

#endif