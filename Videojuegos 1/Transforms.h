#pragma once
#ifndef _Transforms_H_
#define _Transforms_H_
#include "glm/glm.hpp"
using namespace glm;
#include <directxmath.h>
using namespace DirectX;
class Transforms
{
public:
	Transforms();
	Transforms(vec3 esc, vec3 rot, vec3 tran);
	~Transforms();
	void Translate(vec3 Translation);
	void Rotate(vec3 Rotation);
	void Scale(vec3 Scale);
	void Identity();

	void SetScale(vec3 Scale);
	void SetRotation(vec3 Rotation);
	void SetTranslation(vec3 Translation);
	void LookCamera(vec3 position);
	vec3 GetScale();
	vec3 GetRotation();
	vec3 GetTranslation();
	void SetTransforms(vec3 Translation, vec3 Rotation, vec3 Scale);
	void ToMatrix(vec3 Scale, vec3 Rotation, vec3 Translation);
	XMMATRIX ToMatrix();
	XMMATRIX GetMatrix();
private:
	vec3 rot, tran, esc;
	XMMATRIX TransformMatrix;
};
#endif