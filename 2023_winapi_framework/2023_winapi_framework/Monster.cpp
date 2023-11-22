#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Object.h"
#include "EventMgr.h"
Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDis(50.f)
	, m_vCenterPos(Vec2(0.f,0.f))
	, m_fDir(1.f) // �����ʺ��� �̵�
	, m_iHp(5)
{
	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * fDT * m_fDir;
	
	// ���� �� �� �ִ� �Ÿ� �ִ�� ����? => ���� �ٲ��ٰž�.
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDis;
	if (fDist > 0.f)
	{
		// dir �ٲٱ�
		m_fDir *= -1;
		vCurPos.x += fDist * m_fDir;
	}
	SetPos(vCurPos);
}

void Monster::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player_Bullet")
	{
		// ����ó�����ָ��.
		m_iHp--;
		if(m_iHp<=0)
			EventMgr::GetInst()->DeleteObject(this);
	}
}

void Monster::ExitCollision(Collider* _pOther)
{
}

void Monster::StayCollision(Collider* _pOther)
{
}
