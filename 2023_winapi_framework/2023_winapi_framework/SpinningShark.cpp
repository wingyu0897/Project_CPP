#include "pch.h"
#include "SpinningShark.h"
#include "Core.h"
#include "Collider.h"
#include "EventMgr.h"

SpinningShark::SpinningShark(Vec2 pos)
	: SharkBase(pos)
{
	SetHP(1);
	SetSpeed(1500.f);
	SetDamage(10);
}

SpinningShark::~SpinningShark()
{
}

void SpinningShark::Update()
{
	Vec2 vPos = GetPos();
	Vec2 centerPos = Vec2(vPos.x - (float)Core::GetInst()->GetResolution().x / 2, vPos.y - (float)Core::GetInst()->GetResolution().y / 2);
	double angle = atan2(-centerPos.y, -centerPos.x) +(88 * PI / 180);
	SetDir(Vec2((float)cos(angle), (float)sin(angle)));
	Rotate(angle);
	SharkBase::Update();
}

void SpinningShark::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetOwner()->GetName()._Equal(L"Cage"))
	{
		SetDir(Vec2(-GetDir().x, -GetDir().y));
		EventMgr::GetInst()->DeleteObject(this);
	}
	else
	{
		SetHP(GetHP() - 1);
		if (GetHP() <= 0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}
