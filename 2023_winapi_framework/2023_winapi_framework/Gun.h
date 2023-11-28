#pragma once
#include"Object.h"
#include"RotatableObject.h"

class Texture;
class Gun : public RotatableObject
{
public:
	Gun();
	~Gun();
public:
	void Update() override;
	void Render(HDC _dc) override;
	void Rotate(double angle) override;
private:
    void CreateBullet();
private:
	const DWORD CoolTime = 1000;
private:
	HDC m_hMemDC;
	HBITMAP m_hMembit;
	HDC m_hbackDC;
	HBITMAP m_hbackbit;
    wchar_t m_str[255];
	bool isRight;
	DWORD lastFireTime;
};

