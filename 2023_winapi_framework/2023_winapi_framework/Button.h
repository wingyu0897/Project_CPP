#pragma once
class Texture;
class Button
{
public:
	Button();
	~Button();
public:
	virtual void Render(HDC _dc);
	virtual void Click();
	void SetActive(bool active) { m_bActive = active; }
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }
	const Vec2 GetPos() const { return m_vPos; }
	const Vec2 GetScale() const { return m_vScale; }
private:
	Vec2 m_vPos;
	Vec2 m_vScale;
protected:
	bool m_bActive = true;
	Texture* m_pTex;
};

