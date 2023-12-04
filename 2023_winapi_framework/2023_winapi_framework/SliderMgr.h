#pragma once
class Slider;
class SliderMgr
{
	SINGLE(SliderMgr)
public:
	void Render(HDC _dc);
	void Release();
	void AddSlider(const wstring& strKey, Slider* pSlider);
	Slider* GetSlider(const wstring& strKey);
private:
	map<wstring, Slider*> m_mapSliders;
};

