#pragma once
#include"Object.h"
class Slider : public Object
{
public:
	Slider();
	~Slider();
public:
	void Update() override;
	void Render(HDC _dc) override;
	void SetMaxTime(float fMaxTime) { m_fMaxTime = fMaxTime; }
	const float GetMaxTime() const { return m_fMaxTime; }
private:
	float m_fMaxTime;
	float m_fCurrentTime;
};

