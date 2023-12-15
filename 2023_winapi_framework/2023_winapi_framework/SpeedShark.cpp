#include "pch.h"
#include "SpeedShark.h"
#include "Collider.h"
#include "EventMgr.h"

SpeedShark::SpeedShark(Vec2 pos)
	: SharkBase(pos)
	, isHit(false)
{
	SetSpeed(600.f);
	SetDamage(10);
}

void SpeedShark::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetOwner()->GetName()._Equal(L"Cage"))
	{
		SetDir(Vec2(-GetDir().x, -GetDir().y));
		isHit = true;
		hitTime = timeGetTime();
	}
	else
	{
		SetHP(GetHP() - 1);
		if (GetHP() <= 0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}

void SpeedShark::Update()
{
	SharkBase::Update();
	if (!isHit || hitTime + 2000 > timeGetTime()) return;
	SetDir(Vec2(-GetDir().x, -GetDir().y));
	isHit = false;
}
