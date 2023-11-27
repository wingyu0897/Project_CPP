#include "pch.h"
#include "Gun.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "RotatableObject.h"

Gun::Gun()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Gun", L"Texture\\Sniper.bmp");
	m_hMembit = CreateCompatibleBitmap(Core::GetInst()->GetMainDC(), m_pTex->GetWidth(), m_pTex->GetWidth());
	m_hMemDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hMemDC, m_hMembit);
	m_hbackbit = CreateCompatibleBitmap(Core::GetInst()->GetMainDC(), m_pTex->GetWidth(), m_pTex->GetHeight());
	m_hbackDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hbackDC, m_hbackbit);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	TransparentBlt(m_hMemDC
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
}

Gun::~Gun()
{
	DeleteDC(m_hMemDC);
	DeleteDC(m_hbackDC);
}

void Gun::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	BitBlt(m_hMemDC, 0, 0, Width, Height, _dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2), SRCCOPY);
	TransparentBlt(m_hMemDC, 0, 0, Width, Height, m_pTex->GetDC(), 0, 0, Width, Height, RGB(255, 0, 255));
	//BitBlt(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2), Width, Height, m_hMemDC, 0, 0, SRCCOPY);
	PlgBlt(_dc, m_pPoint, m_hMemDC, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), NULL, 0, 0);
}

void Gun::CreateBullet()
{
}
