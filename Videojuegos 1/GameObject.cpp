#include "stdafx.h"

GameObject::GameObject(string name)
{
	Transform = new Transforms();
	Name = name;
}

GameObject::~GameObject()
{
}

string GameObject::GetName()
{
	return Name;
}

bool GameObject::AssignModel(Model* model)
{
	Modelo = model;
	return true;
}

bool GameObject::AssignShader(Shader* shader) {
	this->shader = shader;
	return true;
}

bool GameObject::AssignMaterial(Material * mat)
{
	material = mat;
	return true;
}

bool GameObject::AddTexture(Texture * texture)
{
	Tex.push_back(texture);
	return true;
}

void GameObject::Shutdown()
{
	/*
	delete Modelo;
	delete shader;
	*/
	delete Transform;
	
}

Model* GameObject::GetModel()
{
	return Modelo;
}

bool GameObject::ExistShader()
{
	return (shader != nullptr);
}

Material* GameObject::GetMaterial()
{
	return material;
}

void GameObject::Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	if (shader != nullptr) {
		ResourceManager::bindShader(shader);
		shader->SetShaderParameters(world, view, projection);
		switch (shader->type) {
			case ShaderType::MaterialShader:
			case ShaderType::BasicShader: {
				if (this->material != nullptr) {
					ConstantBufferTypes::MaterialBuffer materialBuffer;
					materialBuffer.ColorMaterial = vec4(this->material->color, 1.0);
					shader->SetShaderConstantBuffer("MaterialBuffer", &materialBuffer);
				}
			}break;
		}; 
	}

	for (int i = 0; i < Tex.size(); i++) {
		Tex[i]->BindTexture(i);
	}
	ResourceManager::bindModel(Modelo);
	Modelo->Draw();
}