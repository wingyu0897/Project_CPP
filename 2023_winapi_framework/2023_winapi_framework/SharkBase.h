#pragma once
#include"RotatableObject.h"

class SharkBase : public RotatableObject
{
public:
	SharkBase(Vec2 vStartPos);
	~SharkBase();
public:
	void Update() override;
	void Render(HDC _dc) override;
	void Rotate(double angle) override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther)  override;
	virtual void StayCollision(Collider* _pOther)  override;

public:
	void SetDir(Vec2 _dir) { m_vMoveDir = _dir.Normalize(); }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	const float& GetSpeed() const { return m_fSpeed; }
private:
	HDC m_hMemDC;
	HBITMAP m_hMembit;
	HDC m_hbackDC;
	HBITMAP m_hbackbit;
	Vec2 m_vMoveDir;
	bool m_bMove;
	float m_fSpeed; // 몬스터 스피드
	int m_iHp; // 체력
};

