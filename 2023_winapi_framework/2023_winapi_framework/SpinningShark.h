#pragma once
#include"SharkBase.h"
class SpinningShark : public SharkBase
{
public:
	SpinningShark(Vec2 pos);
	~SpinningShark();
public:
	void Update() override;	
	void EnterCollision(Collider* _pOther) override;
};