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
	void Render(HDC _dc) override;
	void Rotate(double angle) override;
private:
    void CreateBullet();
private:
	HDC m_hMemDC;
	HBITMAP m_hMembit;
	HDC m_hbackDC;
	HBITMAP m_hbackbit;
    wchar_t m_str[255];
	bool isRight;
};

