#include "pch.h"
#include "Cage.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Collider.h"
#include "SceneMgr.h"
#include "SliderMgr.h"
#include "Slider.h"
#include "SharkBase.h"
#include "Object.h"

Cage::Cage()
	: m_iMaxHP(100)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Cage", L"Texture\\Cage.bmp");
	CreateCollider();
	m_iHp = m_iMaxHP;
}

Cage::~Cage()
{

}

void Cage::Update()
{

}

void Cage::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Cage::SetPos(Vec2 vPos)
{
	Object::SetPos(vPos);
	GetCollider()->SetOffSetPos(Vec2(-GetScale().x / 4.f, -GetScale().y / 4.f));
}

void Cage::SetScale(Vec2 vScale)
{
	Object::SetScale(vScale);
	GetCollider()->SetScale(Vec2(GetScale().x / 2.f, GetScale().y / 2.f));
}

void Cage::EnterCollision(Collider* _pOther)
{
	//SceneMgr::GetInst()->LoadScene(L"Game_Scene");
	SharkBase* shark = (SharkBase*)(_pOther->GetOwner());
	m_iHp -= shark->GetDamage();
	SliderMgr::GetInst()->GetSlider(L"Slider2")->SetPercent((float)m_iHp / m_iMaxHP);
}

void Cage::ExitCollision(Collider* _pOther)
{
}

void Cage::StayCollision(Collider* _pOther)
{
}
