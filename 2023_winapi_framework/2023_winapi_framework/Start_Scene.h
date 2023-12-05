#pragma once
#include "Scene.h"
class Slider;
class Start_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    float m_fMaxTime;
    float m_fCurrentTime;
    Slider *m_pSlider;
    DWORD lastSpawnTime;
};

