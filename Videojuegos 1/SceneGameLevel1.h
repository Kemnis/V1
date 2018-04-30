#pragma once
#include "Scene.h"

class SceneGameLevel1:public Scene
{
public:
	SceneGameLevel1(string id);
	~SceneGameLevel1();
	string CreateScene();
	string LoadResources();
	string BuildScene();
	string Start();
	string ProcessScene(double dt);
	string RenderScene(); 
	void DestroyScene();
	bool DownloadResources();
private:
protected:
};