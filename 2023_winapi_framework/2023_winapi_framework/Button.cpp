#include "pch.h"
#include "Button.h"
#include "SceneMgr.h"
#include "Texture.h"
#include "ResMgr.h"

Button::Button()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Play", L"Texture\\MenuPlay.bmp");
}

Button::~Button()
{
}

void Button::Render(HDC _dc)
{
	//HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	//HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, brush);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	//RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	//SelectObject(_dc, oldBrush);
	//DeleteObject(brush);
	TransparentBlt(_dc, vPos.x - vScale.x / 2, vPos.y - vScale.y / 2, vScale.x, vScale.y,
		m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(0, 0, 0));
}

void Button::Click()
{
	if (!m_bActive) return;
	SceneMgr::GetInst()->LoadScene(L"Start_Scene");
}
