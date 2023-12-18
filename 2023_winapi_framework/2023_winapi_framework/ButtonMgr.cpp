#include "pch.h"
#include "ButtonMgr.h"
#include "Button.h"
#include "KeyMgr.h"

void ButtonMgr::Render(HDC _dc)
{
    for (auto iter : m_mapButtons)
    {
        iter.second->Render(_dc);
    }
}

void ButtonMgr::Update()
{
    if (KEY_DOWN(KEY_TYPE::LBUTTON))
    {
        POINT mousePos = KeyMgr::GetInst()->GetMousePos();
        for (auto iter : m_mapButtons)
        {
            if (mousePos.x > iter.second->GetPos().x - iter.second->GetScale().x / 2
                && mousePos.x < iter.second->GetPos().x + iter.second->GetScale().x / 2
                && mousePos.y > iter.second->GetPos().y - iter.second->GetScale().y / 2
                && mousePos.y < iter.second->GetPos().y + iter.second->GetScale().y / 2)
            {
                iter.second->Click();
            }
        }
        
    }
}

void ButtonMgr::Release()
{
    for (auto iter : m_mapButtons)
    {
        delete iter.second;
    }
}

void ButtonMgr::AddButton(const wstring& strKey, Button* pSlider)
{
    m_mapButtons.insert({ strKey,pSlider });
}

Button* ButtonMgr::GetButton(const wstring& strKey)
{
    auto iter = m_mapButtons.find(strKey);
    if (iter != m_mapButtons.end())
    {
        return iter->second;
    }
    return nullptr;
}

void ButtonMgr::ReleaseButton(const wstring& strKey)
{
    Button* btn = m_mapButtons[strKey];
    if (btn != nullptr)
    {
        m_mapButtons.erase(strKey);
        delete m_mapButtons[strKey];
    }
}
