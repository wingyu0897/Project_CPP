#pragma once
#include "Object.h"
class Texture;
class Cage : public Object
{
public:
	Cage();
	~Cage();
public:
	void Update() override;
	void Render(HDC _dc) override;
	void SetPos(Vec2 vPos) override;
	void SetScale(Vec2 vScale) override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther)  override;
	virtual void StayCollision(Collider* _pOther)  override;
private:
	Texture* m_pTex;
	int m_iHp; // Ã¼·Â
};