#pragma once
#include"Scene.h"
class Texture;
class GameOver_Scene
	: public Scene
{
public:
	GameOver_Scene();
	~GameOver_Scene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;
private:
	Texture* m_pTex;
};

