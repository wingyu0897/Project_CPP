#include "pch.h"
#include "GameOver_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Button.h"
#include "QuitButton.h"
#include "ButtonMgr.h"
#include "ResMgr.h"
#include "Texture.h"

GameOver_Scene::GameOver_Scene()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"ClearImage", L"Texture\\ClearImage.bmp");
}

GameOver_Scene::~GameOver_Scene()
{
}

void GameOver_Scene::Init()
{
	ButtonMgr::GetInst()->GetButton(L"Quit_Button")->SetActive(true);
}

void GameOver_Scene::Update()
{
}

void GameOver_Scene::Render(HDC _dc)
{
	Vec2 res = Core::GetInst()->GetResolution();
	Scene::Render(_dc);
	HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(13, 10, 30));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, brush);
	Rectangle(_dc, 0, 0, res.x, res.y);
	SelectObject(_dc, oldBrush);
	TransparentBlt(_dc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), m_pTex->GetDC(), 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(0, 0, 0));
	ButtonMgr::GetInst()->GetButton(L"Quit_Button")->Render(_dc);

	DeleteObject(brush);
}

void GameOver_Scene::Release()
{
}
