#include "pch.h"
#include "QuitButton.h"
#include "Core.h"
#include "Texture.h"
#include "ResMgr.h"

QuitButton::QuitButton()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Quit", L"Texture\\MenuQuit.bmp");
}

QuitButton::~QuitButton()
{
}

void QuitButton::Click()
{
	if (!m_bActive) return;
	DestroyWindow(Core::GetInst()->GetHwnd());
}
