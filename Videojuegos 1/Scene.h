#pragma once
#include "Camera3D.h"
#include "Mesh3D.h"


class Scene :public DxComponent<Scene>
{
public:
	Scene(string id);
	~Scene();
	virtual string LoadResources();
	virtual string CreateScene();
	virtual string BuildScene();
	virtual string Start();
	virtual string ProcessScene(double dt);
	virtual string RenderScene();
	virtual void DestroyScene();
	virtual bool DownloadResources();
public:
	Camera3D * SceneCamera;
protected:
	string RS,id;
	bool RB;
private:
	XMMATRIX CameraMatrix;
};