#pragma once
class Button;
class ButtonMgr
{
	SINGLE(ButtonMgr);
public:
	void Render(HDC _dc);
	void Update();
	void Release();
	void AddButton(const wstring& strKey, Button* pSlider);
	Button* GetButton(const wstring& strKey);
	void ReleaseButton(const wstring& strKey);
private:
	map<wstring, Button*> m_mapButtons;
};

