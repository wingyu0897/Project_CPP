#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Gun.h"
#include "Cage.h"
#include "Monster.h"
#include "SharkBase.h"
#include "SpeedShark.h"
#include "SpinningShark.h"
#include "KeyMgr.h"
#include "SliderMgr.h"
#include "CollisionMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Slider.h"
#include "SceneMgr.h"
#include "Texture.h"

void Start_Scene::Init()
{
	m_fMaxTime = 150.f;
	lastSpawnTime = 0;
	//Object* pObj = new Player;
	//pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	//pObj->SetScale(Vec2(100.f,100.f));
	//AddObject(pObj, OBJECT_GROUP::PLAYER);

	Object* pGun = new Gun();
	pGun->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	pGun->SetScale(Vec2(125.f, 35.f));
	AddObject(pGun, OBJECT_GROUP::GUN);

	Object* pShark = new SpinningShark(Vec2(200, 200));
	AddObject(pShark, OBJECT_GROUP::MONSTER);

	Object* pCage = new Cage();
	pCage->SetName(L"Cage");
	pCage->SetScale(Vec2(500.f, 500.f));
	pCage->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 + 125.f, Core::GetInst()->GetResolution().y / 2 + 125.f })));
	AddObject(pCage, OBJECT_GROUP::CAGE);

	Slider* pSlider = new Slider();
	pSlider->SetPos(Vec2({ 50, Core::GetInst()->GetResolution().y / 2 }));
	pSlider->SetScale(Vec2(30, 500));
	pSlider->SetPercent(0.5f);
	SliderMgr::GetInst()->AddSlider(L"Slider1", pSlider);
	m_pSlider = pSlider;

	// ���� ����
	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	// �浹üũ�ؾߵǴ°͵��� ��������.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::CAGE);
}

void Start_Scene::Update()
{
	Scene::Update();
	m_fCurrentTime += fDT;
	float percent = m_fCurrentTime / m_fMaxTime;
	m_pSlider->SetPercent(percent);

	Vec2 center = Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 });

	if (percent < 1.f)
	{
		if (lastSpawnTime + 3000.f < timeGetTime())
		{
			int x = (rand() % 201) - 100;
			int y = (rand() % 201) - 100;
			Vec2 pos = Vec2(x, y).Normalize();
			pos.x = pos.x * 1000 + center.x;
			pos.y = pos.y * 1000 + center.y;
			Object* pShark = new SharkBase(pos);
			AddObject(pShark, OBJECT_GROUP::MONSTER);
			lastSpawnTime = timeGetTime();
			if (percent > 0.2f)
			{
				int r = rand() % 1001;
				if (r < 500)
				{
					int x = (rand() % 201) - 100;
					int y = (rand() % 201) - 100;
					Vec2 pos = Vec2(x, y).Normalize();
					pos.x = pos.x * 1000 + center.x;
					pos.y = pos.y * 1000 + center.y;
					Object* pShark = new SpeedShark(pos);
					AddObject(pShark, OBJECT_GROUP::MONSTER);
				}
				if (r < 200)
				{
					int x = (rand() % 201) - 100;
					int y = (rand() % 201) - 100;
					Vec2 pos = Vec2(x, y).Normalize();
					pos.x = pos.x * 1000 + center.x;
					pos.y = pos.y * 1000 + center.y;
					Object* pShark = new SpinningShark(pos);
					AddObject(pShark, OBJECT_GROUP::MONSTER);
				}
			}
		}
	}
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	SliderMgr::GetInst()->Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
