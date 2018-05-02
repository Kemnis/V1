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

	Transform->SetRadio(model->GetRadio());
	
	return true;
}

bool GameObject::AssignLight(Light* light)
{
	this->light = light;
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
	delete Transform;
	Transform = 0;
}

void GameObject::SetPosBitmap(vec2 Position)
{
	Modelo->SetPosition(Position);
}

void GameObject::SetEscBitmap(vec2 Escale)
{
	Modelo->SetSize(Escale);
}

void GameObject::SetPosBitmap(float PosX,float PosY)
{
	Modelo->SetPosition(vec2(PosX,PosY));
}

void GameObject::SetEscBitmap(float EscX,float EscY)
{
	Modelo->SetSize(vec2(EscX,EscY));
}

Model* GameObject::GetModel()
{
	return Modelo;
}

Shader* GameObject::GetShader()
{
	return shader;
}

bool GameObject::ExistShader()
{
	return (shader != nullptr);
}

Material* GameObject::GetMaterial()
{
	return material;
}

Light* GameObject::GetLight()
{
	return light;
}

void GameObject::Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	if (shader != nullptr) {

		ResourceManager::bindShader(shader);
		shader->SetShaderParameters(world, view, projection);
		switch (shader->type) {
			case ShaderType::MaterialLShader:
			case ShaderType::BasicLShader:
				if (this->light != nullptr) {
					ConstantBufferTypes::LightBuffer lightBuffer;
					lightBuffer.ambientColor = vec4(this->light->Ambient);
					lightBuffer.diffuseColor = vec4(this->light->Diffuse);
					lightBuffer.lightDirection = vec3(this->light->Direction);
					shader->SetShaderConstantBuffer("LightBuffer", &lightBuffer);
				}
			case ShaderType::MaterialShader:
			case ShaderType::SkydomeShader:
			case ShaderType::BasicShader: {
				if (this->material != nullptr) {
					ConstantBufferTypes::MaterialBuffer materialBuffer;
					materialBuffer.ColorMaterial = vec4(this->material->color, 1.0);
					materialBuffer.escalar = this->material->escalar;
					shader->SetShaderConstantBuffer("MaterialBuffer", &materialBuffer);
				}
			}break;
			case ShaderType::TerrainShader:
			{
				if (this->light != nullptr)
				{
					ConstantBufferTypes::LightBuffer lightBuffer;
					lightBuffer.ambientColor = vec4(this->light->Ambient);
					lightBuffer.diffuseColor = vec4(this->light->Diffuse);
					lightBuffer.lightDirection = vec3(this->light->Direction);
					shader->SetShaderConstantBuffer("LightBuffer", &lightBuffer);
				}
				if (this->material != nullptr) {
					ConstantBufferTypes::MaterialBuffer materialBuffer;
					materialBuffer.ColorMaterial = vec4(this->material->color, 1.0);
					materialBuffer.escalar = this->material->escalar;
					shader->SetShaderConstantBuffer("MaterialBuffer", &materialBuffer);
				}
			}break;
			case ShaderType::GUIShader:
			{
				//Check update bitmap
				Modelo->UpdateBitmap();

				if (this->material != nullptr) {
					ConstantBufferTypes::MaterialBuffer materialBuffer;
					materialBuffer.ColorMaterial = vec4(this->material->color, 1.0);
					materialBuffer.escalar = this->material->escalar;
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