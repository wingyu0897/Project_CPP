#pragma once
#include"SharkBase.h"
class SpeedShark : public SharkBase
{
public:
	SpeedShark(Vec2 pos);

public:
	void EnterCollision(Collider* _pOther) override;
	void Update() override;
private:
	DWORD hitTime;
	bool isHit;
};

