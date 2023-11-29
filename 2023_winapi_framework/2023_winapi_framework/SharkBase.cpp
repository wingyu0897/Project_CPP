#include "pch.h"
#include "SharkBase.h"
#include "Texture.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Core.h"
#include "Collider.h"
#include "EventMgr.h"

SharkBase::SharkBase(Vec2 vStartPos)
	: m_fSpeed(50.f)
	, m_bMove(true)
	, m_iHp(1)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Shark", L"Texture\\Shark1.bmp");
	CreateCollider();
	SetPos(vStartPos);
	SetScale(Vec2(200.f, 90.f));
	Vec2 centerPos = Vec2(vStartPos.x - (float)Core::GetInst()->GetResolution().x / 2, vStartPos.y - (float)Core::GetInst()->GetResolution().y / 2);
	SetDir(Vec2(1, 1));
	GetCollider()->SetScale(Vec2(GetScale().y, GetScale().y));
}

SharkBase::~SharkBase()
{
}

void SharkBase::Update()
{
	if (m_bMove)
	{
		Vec2 vCurPos = GetPos();
		vCurPos.x += m_fSpeed * fDT * m_vDir.x;
		vCurPos.y += m_fSpeed * fDT * m_vDir.y;
		SetPos(vCurPos);
	}
	Rotate(45 * PI / 180);
}

void SharkBase::Render(HDC _dc)
{
	RotatableObject::Render(_dc);
	Component_Render(_dc);
}

void SharkBase::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetOwner()->GetName()._Equal(L"Cage"))
	{
		m_bMove = false;
	}
	else
	{
		m_iHp--;
		if (m_iHp <= 0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}

void SharkBase::ExitCollision(Collider* _pOther)
{
}

void SharkBase::StayCollision(Collider* _pOther)
{
}
