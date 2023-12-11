#pragma once
#include "Object.h"
#include "Collider.h"
class Texture;
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void EnterCollision(Collider* _pOther) override;
public:
    void SetDir(float _f) { m_fTheta = _f; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
    void SetSpeed(float speed) { m_fSpeed = speed; }
    void SetScale(Vec2 vec) override { Object::SetScale(vec); GetCollider()->SetScale(GetScale()); }
private:
//    float m_fDir; // �Ѿ� ����(-1 ��, 1 �Ʒ�);
    float m_fTheta; // �ﰢ�Լ� ����.
    Vec2 m_vDir;
    Texture* m_pTex;
    float m_fSpeed;
    bool m_bIsDead;
};

