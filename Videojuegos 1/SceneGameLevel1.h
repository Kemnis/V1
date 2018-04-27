#pragma once
#include "Scene.h"

class SceneGameLevel1:public Scene
{
public:
	SceneGameLevel1();
	~SceneGameLevel1();
	string CreateScene();
	string ProcessScene(double dt);
	string RenderScene();
	string Start();
	void DestroyScene();
private:
protected:
};