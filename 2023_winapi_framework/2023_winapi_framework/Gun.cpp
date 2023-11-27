#include "pch.h"
#include "Gun.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "RotatableObject.h"

Gun::Gun()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Sniper1", L"Texture\\Sniper1.bmp");
	ResMgr::GetInst()->TexLoad(L"Sniper2", L"Texture\\Sniper2.bmp");
	isRight = true;

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
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255)); //create brush
	SelectObject(m_hbackDC, brush); //select brush into DC
	Rectangle(m_hbackDC, -5, -5, m_pTex->GetWidth() + 10, m_pTex->GetWidth() + 10);
}

Gun::~Gun()
{
	DeleteDC(m_hMemDC);
	DeleteDC(m_hbackDC);
}

void Gun::Rotate(double angle)
{
	double deg = angle * 180 / PI;
	if (isRight && abs(deg) > 90)
	{
		isRight = false;
		m_pTex = ResMgr::GetInst()->TexFind(L"Sniper2");
	}
	else if (!isRight && abs(deg) <= 90)
	{
		isRight = true;
		m_pTex = ResMgr::GetInst()->TexFind(L"Sniper1");
	}

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

	//m_pPoint[0].x = vPos.x + m_vRotatedDir[0].x;
	//m_pPoint[0].y = vPos.y + m_vRotatedDir[0].y;

	//m_pPoint[1].x = vPos.x + m_vRotatedDir[1].x;
	//m_pPoint[1].y = vPos.y + m_vRotatedDir[1].y;

	//m_pPoint[2].x = vPos.x + m_vRotatedDir[2].x;
	//m_pPoint[2].y = vPos.y + m_vRotatedDir[2].y;

	//m_pPoint[0].x = m_vRotatedDir[0].x + m_pTex->GetWidth() / 2;
	//m_pPoint[0].y = m_vRotatedDir[0].y + m_pTex->GetWidth() / 2;

	//m_pPoint[1].x = m_vRotatedDir[1].x + m_pTex->GetWidth() / 2;
	//m_pPoint[1].y = m_vRotatedDir[1].y + m_pTex->GetWidth() / 2;

	//m_pPoint[2].x = m_vRotatedDir[2].x + m_pTex->GetWidth() / 2;
	//m_pPoint[2].y = m_vRotatedDir[2].y + m_pTex->GetWidth() / 2;
	 
	m_pPoint[0].x = m_vRotatedDir[0].x + vScale.x / 2;
	m_pPoint[0].y = m_vRotatedDir[0].y + vScale.x / 2;

	m_pPoint[1].x = m_vRotatedDir[1].x + vScale.x / 2;
	m_pPoint[1].y = m_vRotatedDir[1].y + vScale.x / 2;

	m_pPoint[2].x = m_vRotatedDir[2].x + vScale.x / 2;
	m_pPoint[2].y = m_vRotatedDir[2].y + vScale.x / 2;
}

void Gun::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	BitBlt(m_hMemDC, 0, 0, Width, Width, _dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.x / 2), SRCCOPY);
	PlgBlt(m_hbackDC, m_pPoint, m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), NULL, 0, 0);
	TransparentBlt(m_hMemDC, 0, 0, Width, Width, m_hbackDC, 0, 0, Width, Width, RGB(255, 0, 255));
	BitBlt(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.x / 2), Width, Width, m_hMemDC, 0, 0, SRCCOPY);
}

void Gun::CreateBullet()
{
}
