#pragma once

class Slider
{
public:
	Slider();
	~Slider();
public:
	void Render(HDC _dc);
	void SetPos(Vec2 vPos) { m_vPos = vPos; }
	void SetScale(Vec2 vScale) { m_vScale = vScale; }
	void SetPercent(float fPercent) { m_fPercent = fPercent; }
	void IsHorizontal(bool value) { isHorizontal = value; }
	const Vec2 GetPos() const { return m_vPos; }
	const Vec2 GetScale() const { return m_vScale; }
	const float GetPercent() const { return m_fPercent; }
private:
	Vec2 m_vPos;
	Vec2 m_vScale;
	float m_fPercent;
	bool isHorizontal;
};

