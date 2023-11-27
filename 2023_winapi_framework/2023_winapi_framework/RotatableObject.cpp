#include "pch.h"
#include "RotatableObject.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Texture.h"

RotatableObject::RotatableObject()
{
}

RotatableObject::~RotatableObject()
{
}

void RotatableObject::Update()
{
	Vec2 vPos = GetPos();
	POINT mousePos = KeyMgr::GetInst()->GetMousePos();
	mousePos.x -= vPos.x;
	mousePos.y -= vPos.y;

	m_dAngle = atan2(mousePos.y, mousePos.x);
	Rotate(m_dAngle);
}

void RotatableObject::Render(HDC _dc)
{
	assert(m_pTex != nullptr);
	PlgBlt(_dc, m_pPoint, m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), NULL, 0, 0);
}

void RotatableObject::Rotate(double angle)
{
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

	m_vRotatedDir[0] = Vec2(m_vDir[0].x * (float)cos(m_dAngle) - m_vDir[0].y * (float)sin(m_dAngle)
		, m_vDir[0].x * (float)sin(m_dAngle) + m_vDir[0].y * (float)cos(m_dAngle));
	m_vRotatedDir[1] = Vec2(m_vDir[1].x * (float)cos(m_dAngle) - m_vDir[1].y * (float)sin(m_dAngle)
		, m_vDir[1].x * (float)sin(m_dAngle) + m_vDir[1].y * (float)cos(m_dAngle));
	m_vRotatedDir[2] = Vec2(m_vDir[2].x * (float)cos(m_dAngle) - m_vDir[2].y * (float)sin(m_dAngle)
		, m_vDir[2].x * (float)sin(m_dAngle) + m_vDir[2].y * (float)cos(m_dAngle));

	m_pPoint[0].x = vPos.x + m_vRotatedDir[0].x;
	m_pPoint[0].y = vPos.y + m_vRotatedDir[0].y;

	m_pPoint[1].x = vPos.x + m_vRotatedDir[1].x;
	m_pPoint[1].y = vPos.y + m_vRotatedDir[1].y;

	m_pPoint[2].x = vPos.x + m_vRotatedDir[2].x;
	m_pPoint[2].y = vPos.y + m_vRotatedDir[2].y;
}
