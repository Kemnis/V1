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

bool GameObject::AssignTexture(Texture * texture)
{
	Tex = texture;
	return true;
}

void GameObject::Shutdown()
{
	delete Modelo;
	delete Tex;
	delete shader;
	delete Transform;
}

Model* GameObject::GetModel()
{
	return Modelo;
}

Texture* GameObject::GetTexture()
{
	return Tex;
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
		shader->SetShaderParameters(world, view, projection);
		if (shader->type == ShaderType::BasicShader || shader->type == ShaderType::MaterialShader) {
			if (this->material != nullptr) {
				BasicShader::MaterialBufferType materialBuffer;
				materialBuffer.ColorMaterial = vec4(this->material->color, 1.0);
				shader->SetShaderConstantBuffer("MaterialBuffer", &materialBuffer);
			}
		}
		ResourceManager::bindShader(shader);
	}

	if (Tex != nullptr) {
		Tex->BindTexture(0);
	}
	ResourceManager::bindModel(Modelo);
	Modelo->Draw();
}