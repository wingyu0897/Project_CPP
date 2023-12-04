#include "pch.h"
#include "SliderMgr.h"
#include "Slider.h"

void SliderMgr::Render(HDC _dc)
{
    for (auto iter : m_mapSliders)
    {
        iter.second->Render(_dc);
    }
}

void SliderMgr::Release()
{
    for (auto iter : m_mapSliders)
    {
        delete iter.second;
    }
}

void SliderMgr::AddSlider(const wstring& strKey, Slider* pSlider)
{
    m_mapSliders.insert({ strKey,pSlider });
}

Slider* SliderMgr::GetSlider(const wstring& strKey)
{
    auto iter = m_mapSliders.find(strKey);
    if (iter != m_mapSliders.end())
    {
        return iter->second;
    }
    return nullptr;
}
