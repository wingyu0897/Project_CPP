#include "pch.h"
#include "SharkBase.h"
#include "Texture.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Core.h"
#include "Collider.h"
#include "EventMgr.h"

SharkBase::SharkBase(Vec2 vStartPos)
	: m_fSpeed(100.f)
	, m_bMove(true)
	, m_iHp(1)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Shark", L"Texture\\Shark1.bmp");
	CreateCollider();

	SetPos(vStartPos);
	SetScale(Vec2(200.f, 90.f));
	Vec2 centerPos = Vec2(vStartPos.x - (float)Core::GetInst()->GetResolution().x / 2, vStartPos.y - (float)Core::GetInst()->GetResolution().y / 2);
	SetDir(Vec2(-centerPos.x, -centerPos.y));
	GetCollider()->SetScale(Vec2(GetScale().y * 1.2f, GetScale().y * 1.2f));
	double angle = atan2(-centerPos.y, -centerPos.x);
	Rotate(angle);

	m_hMembit = CreateCompatibleBitmap(Core::GetInst()->GetMainDC(), m_pTex->GetWidth(), m_pTex->GetWidth());
	m_hMemDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hMemDC, m_hMembit);
	m_hbackbit = CreateCompatibleBitmap(Core::GetInst()->GetMainDC(), m_pTex->GetWidth() * 2, m_pTex->GetWidth());
	m_hbackDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hbackDC, m_hbackbit);

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	HBRUSH brush = Core::GetInst()->GetBrush(BRUSH_TYPE::PURPLE);
	HBRUSH original = (HBRUSH)SelectObject(m_hbackDC, brush); //select brush into DC
	Rectangle(m_hbackDC, -5, -5, m_pTex->GetWidth() + 10, m_pTex->GetWidth() + 10);
	SelectObject(m_hbackDC, original);
}

SharkBase::~SharkBase()
{
	DeleteDC(m_hMemDC);
	DeleteDC(m_hbackDC);
}

void SharkBase::Update()
{
	if (m_bMove)
	{
		Vec2 vCurPos = GetPos();
		vCurPos.x += m_fSpeed * fDT * m_vMoveDir.x;
		vCurPos.y += m_fSpeed * fDT * m_vMoveDir.y;
		SetPos(vCurPos);
	}
}

void SharkBase::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	BitBlt(m_hMemDC, 0, 0, Width, Width, _dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.x / 2), SRCCOPY);
	PlgBlt(m_hbackDC, m_pPoint, m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), NULL, 0, 0);
	TransparentBlt(m_hMemDC, 0, 0, Width, Width, m_hbackDC, 0, 0, Width, Width, RGB(255, 0, 255));
	BitBlt(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.x / 2), Width, Width, m_hMemDC, 0, 0, SRCCOPY);
	Component_Render(_dc);
}

void SharkBase::Rotate(double angle)
{
	double deg = angle * 180 / PI;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	m_pPoint[0].x = (LONG)(vPos.x - vScale.x / 2);
	m_pPoint[0].y = (LONG)(vPos.y - vScale.y / 2);
	m_pPoint[1].x = (LONG)(vPos.x + vScale.x / 2);
	m_pPoint[1].y = (LONG)(vPos.y - vScale.y / 2);
	m_pPoint[2].x = (LONG)(vPos.x - vScale.x / 2);
	m_pPoint[2].y = (LONG)(vPos.y + vScale.y / 2);

	m_vDir[0] = Vec2(m_pPoint[0].x - vPos.x, m_pPoint[0].y - vPos.y);
	m_vDir[1] = Vec2(m_pPoint[1].x - vPos.x, m_pPoint[1].y - vPos.y);
	m_vDir[2] = Vec2(m_pPoint[2].x - vPos.x, m_pPoint[2].y - vPos.y);

	m_fDistance[0] = sqrt(pow(m_vDir[0].x, 2) + pow(m_vDir[0].y, 2));
	m_fDistance[1] = sqrt(pow(m_vDir[1].x, 2) + pow(m_vDir[0].y, 2));
	m_fDistance[2] = sqrt(pow(m_vDir[2].x, 2) + pow(m_vDir[0].y, 2));

	m_vRotatedDir[0] = Vec2(m_vDir[0].x * (float)cos(angle) - m_vDir[0].y * (float)sin(angle)
		, m_vDir[0].x * (float)sin(angle) + m_vDir[0].y * (float)cos(angle));
	m_vRotatedDir[1] = Vec2(m_vDir[1].x * (float)cos(angle) - m_vDir[1].y * (float)sin(angle)
		, m_vDir[1].x * (float)sin(angle) + m_vDir[1].y * (float)cos(angle));
	m_vRotatedDir[2] = Vec2(m_vDir[2].x * (float)cos(angle) - m_vDir[2].y * (float)sin(angle)
		, m_vDir[2].x * (float)sin(angle) + m_vDir[2].y * (float)cos(angle));

	m_pPoint[0].x = m_vRotatedDir[0].x + vScale.x / 2;
	m_pPoint[0].y = m_vRotatedDir[0].y + vScale.x / 2;
	m_pPoint[1].x = m_vRotatedDir[1].x + vScale.x / 2;
	m_pPoint[1].y = m_vRotatedDir[1].y + vScale.x / 2;
	m_pPoint[2].x = m_vRotatedDir[2].x + vScale.x / 2;
	m_pPoint[2].y = m_vRotatedDir[2].y + vScale.x / 2;
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
