#include "pch.h"
#include "Slider.h"
#include "TimeMgr.h"
#include "Core.h"

Slider::Slider()
	: m_fPercent{0}
	, isHorizontal(false)
{
}

Slider::~Slider()
{

}

void Slider::Render(HDC _dc)
{
	if (isHorizontal)
	{
		float x = (m_vScale.x - 6) * m_fPercent;
		HBRUSH original = (HBRUSH)SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
		RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
		SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::RED));
		RECT_RENDER((m_vPos.x - (m_vScale.x - 6) / 2 + x / 2), m_vPos.y, x, (m_vScale.y - 6), _dc);
		SelectObject(_dc, original);
	}
	else
	{
		float y = (m_vScale.y - 6) * m_fPercent;
		HBRUSH original = (HBRUSH)SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
		RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
		SelectObject(_dc, Core::GetInst()->GetBrush(BRUSH_TYPE::BLUE));
		RECT_RENDER(m_vPos.x, (m_vPos.y + (m_vScale.y - 6) / 2 - y / 2), (m_vScale.x - 6), y, _dc);
		SelectObject(_dc, original);
	}
}
