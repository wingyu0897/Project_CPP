#include "pch.h"
#include "SpeedShark.h"
#include "Collider.h"
#include "EventMgr.h"

SpeedShark::SpeedShark(Vec2 pos)
	: SharkBase(pos)
{
	SetSpeed(400.f);
}

void SpeedShark::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetOwner()->GetName()._Equal(L"Cage"))
	{
		SetDir(Vec2(-GetDir().x, -GetDir().y));
	}
	else
	{
		SetHP(GetHP() - 1);
		if (GetHP() <= 0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}
