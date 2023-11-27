#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Gun.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Texture.h"
void Start_Scene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Object* pGun = new Gun();
	pGun->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	pGun->SetScale(Vec2(200.f, 80.f));
	AddObject(pGun, OBJECT_GROUP::GUN);

	// ���� ���� �������� ��ġ�� �غ��ô�.

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Monster* pMonster = nullptr;
	int iMonster = 10;		// ���� �� 
	float fMoveDist = 30.f; // ������ �Ÿ�
	float fMonsterScale = 50.f; // ���� ũ��
	// �ػ�x - ( ������ �Ÿ� + ������Ʈ ũ�� /2) * 2 / ���ͼ� -1 
	float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2) / (float)(iMonster -1);

	for (int i = 0; i < iMonster; ++i)
	{
		pMonster = new Monster;
		pMonster->SetPos(Vec2(
			(fMoveDist + fMonsterScale / 2.f) + i* fTerm
			,300.f));
		pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
		pMonster->SetCenterPos(pMonster->GetPos());
		pMonster->SetMoveDis(fMoveDist);
		AddObject(pMonster, OBJECT_GROUP::MONSTER);
	}
	// ���� ����
	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	// �浹üũ�ؾߵǴ°͵��� ��������.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
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
