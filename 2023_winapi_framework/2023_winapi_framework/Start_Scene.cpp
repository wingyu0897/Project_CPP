#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Gun.h"
#include "Cage.h"
#include "Monster.h"
#include "SharkBase.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "Slider.h"
#include "SceneMgr.h"
#include "Texture.h"

void Start_Scene::Init()
{
	//Object* pObj = new Player;
	//pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	//pObj->SetScale(Vec2(100.f,100.f));
	//AddObject(pObj, OBJECT_GROUP::PLAYER);

	Object* pGun = new Gun();
	pGun->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	pGun->SetScale(Vec2(125.f, 35.f));
	AddObject(pGun, OBJECT_GROUP::GUN);

	Object* pShark = new SharkBase(Vec2(100, 100));
	AddObject(pShark, OBJECT_GROUP::MONSTER);

	Object* pCage = new Cage();
	pCage->SetName(L"Cage");
	pCage->SetScale(Vec2(500.f, 500.f));
	pCage->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2 + 125.f, Core::GetInst()->GetResolution().y / 2 + 125.f })));
	AddObject(pCage, OBJECT_GROUP::CAGE);

	Slider* pSlider = new Slider();
	pSlider->SetMaxTime(150.f);
	pSlider->SetPos(Vec2({ 50, Core::GetInst()->GetResolution().y / 2 }));
	pSlider->SetScale(Vec2(30, 500));
	AddObject(pSlider, OBJECT_GROUP::UI);

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
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
