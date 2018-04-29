#pragma once
#include "Scene.h"

class SceneMenu:public Scene
{
public:
	SceneMenu();
	~SceneMenu();
	string CreateScene();
	string ProcessScene(double dt);
	string RenderScene();
	string Start();
	void DestroyScene();
private:
protected:
};
