#include "pch.h"
#include "Slider.h"
#include "TimeMgr.h"
#include "Core.h"

Slider::Slider()
	: m_fCurrentTime{0}
{
}

Slider::~Slider()
{
}

void Slider::Update()
{
	m_fCurrentTime += fDT;
}

void Slider::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	float per = m_fCurrentTime / m_fMaxTime;
	float y = (vScale.y - 6) * per;
	HBRUSH original = (HBRUSH)SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::BLUE));
	RECT_RENDER(vPos.x, (vPos.y + (vScale.y - 6) / 2 - y / 2), (vScale.x - 6), y, _dc);
	SelectObject(_dc, original);
}
