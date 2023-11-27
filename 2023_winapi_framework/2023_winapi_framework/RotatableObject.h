#pragma once
#include"Object.h"

class Texture;
class RotatableObject : public Object
{
public:
    RotatableObject();
    ~RotatableObject();
public:
    void Update() override;
    void Render(HDC _dc) override;
    virtual void Rotate(double angle);
protected:
    Texture* m_pTex;
    double m_dAngle;
    POINT m_pPoint[3];
    Vec2 m_vDir[3];
    Vec2 m_vRotatedDir[3];
    float m_fDistance[3];
};
