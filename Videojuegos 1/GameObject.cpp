#include "stdafx.h"

GameObject::GameObject(string name)
{
	Transform = new Transforms();
	Name = name;
	
	;
	m_previousWidth = -1;
	m_previousHeight = -1;
	m_previousPosX = -1;
	m_previousPosY = -1;
	m_screenWidth = 800;
	m_screenHeight = 600;
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

//Method Bitmap
void GameObject::SetRect(vec4 rectBitmap)
{
	CenterX = rectBitmap.x;
	CenterY = rectBitmap.y;
	m_bitmapWidth = rectBitmap.z;
	m_bitmapHeight = rectBitmap.w;

	PosX = rectBitmap.x + m_screenWidth * 0.5f - m_bitmapWidth * 0.5f;
	PosY = m_screenHeight * 0.5f - m_bitmapHeight * 0.5f - rectBitmap.y;
	return;
}
//Method Bitmap
void GameObject::SetPosition(vec2 position)
{
	CenterX = position.x;
	CenterY = position.y;
	PosX = position.x + m_screenWidth * 0.5f - m_bitmapWidth * 0.5f;
	PosY = m_screenHeight * 0.5f - m_bitmapHeight * 0.5f - position.y;
	return;
}

//Method Bitmap
void GameObject::SetSize(vec2 size)
{
	m_bitmapWidth = size.x;
	m_bitmapHeight = size.y;

	PosX = PosX + m_screenWidth * 0.5f - m_bitmapWidth * 0.5f;
	PosY = m_screenHeight * 0.5f - m_bitmapHeight * 0.5f - PosY;
}

//Update Bitmap
void GameObject::UpdateBitmap()
{
	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if ((PosX == m_previousPosX) && (PosY == m_previousPosY) && (m_bitmapWidth == m_previousWidth) && (m_bitmapHeight == m_previousHeight))
	{
		return;
	}

	// If it has changed then update the position it is being rendered to.
	m_previousPosX = PosX;
	m_previousPosY = PosY;
	m_previousWidth = m_bitmapWidth;
	m_previousHeight = m_bitmapHeight;

	Modelo->UpdateBufferBitmap(vec4(PosX, PosY, m_bitmapWidth, m_bitmapHeight), m_screenWidth, m_screenHeight);
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
				UpdateBitmap();

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