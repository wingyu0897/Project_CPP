#include "pch.h"
#include "Menu_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Button.h"
#include "QuitButton.h"
#include "ButtonMgr.h"
#include "ResMgr.h"
#include "Texture.h"

void Menu_Scene::Init()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"MenuImage", L"Texture\\SharksTitle.bmp");
	Button* pStartButton = new Button();
	pStartButton->SetScale(Vec2(300.f, 100.f));
	pStartButton->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 100})));
	ButtonMgr::GetInst()->AddButton(L"Start_Button", pStartButton);

	QuitButton* pQuitButton = new QuitButton();
	pQuitButton->SetScale(Vec2(300.f, 100.f));
	pQuitButton->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2  + 250})));
	ButtonMgr::GetInst()->AddButton(L"Quit_Button", pQuitButton);

	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\BGM.wav", true);
	ResMgr::GetInst()->Play(L"BGM");

	ButtonMgr::GetInst()->GetButton(L"Start_Button")->SetActive(true);
	ButtonMgr::GetInst()->GetButton(L"Quit_Button")->SetActive(true);
}

void Menu_Scene::Update()
{
	Scene::Update();
}

void Menu_Scene::Render(HDC _dc)
{
	Vec2 res = Core::GetInst()->GetResolution();
	Scene::Render(_dc);
	HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(13, 10, 30));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, brush);
	Rectangle(_dc, 0, 0, res.x, res.y);
	SelectObject(_dc, oldBrush);
	TransparentBlt(_dc, res.x / 2 - 500, res.y / 2 - 500, 1000, 500, m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(0, 0, 0));
	ButtonMgr::GetInst()->GetButton(L"Start_Button")->Render(_dc);
	ButtonMgr::GetInst()->GetButton(L"Quit_Button")->Render(_dc);

	DeleteObject(brush);
}

void Menu_Scene::Release()
{
	Scene::Release();
	ButtonMgr::GetInst()->GetButton(L"Start_Button")->SetActive(false);
	ButtonMgr::GetInst()->GetButton(L"Quit_Button")->SetActive(false); 
}
