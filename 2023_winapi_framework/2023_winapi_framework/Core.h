#pragma once
// �ϳ���, ��𼭵� �����־����.
// �̱����� �����ϴ� ����� ��û ����
// 1�б⶧ �ߴ��� ���̳��� �̱��� = �����Ҵ�
// ����: �������� �ʴ��� �ٽ� ������ �� �ִ�.
// ����: �������� �Ҵ��ϱ⿡ ���Ÿ� ������Ѵ�.
//private:
//	static Core* m_pInst;
//public:
//	static Core* GetInst()
//	{
//		if (m_pInst == nullptr)
//			m_pInst = new Core;
//		return m_pInst;
//	}
//public:
//	static void DestroyInst()
//	{
//		SAFE_DELETE(m_pInst);

// ����(static)�Ҵ�.
#include "define.h"
#include "Object.h"
class Core
{
	SINGLE(Core);
public:
	bool Init(HWND _hwnd, POINT _ptResolution);
	void GameLoop();
	void Release();
public:
	const HWND& GetHwnd() const { return m_hWnd; }
	const POINT& GetResolution() const 
	{ return m_ptResolution; }
	const HDC& GetMainDC() const
	{
		return m_hDC;
	}
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_arrBrush[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_arrPen[(UINT)_eType];
	}
private:
	void Update();
	void Render();
	void CreateGDI();
private:
	HWND	m_hWnd;
	HDC		m_hDC; // ���� DC
	HDC		m_hbackDC; // �� ���� DC
	HBITMAP	m_hbackbit; // �� ���ۿ� �׸� ��Ʈ��
	POINT	m_ptResolution; // �ػ�
	HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    m_arrPen[(UINT)PEN_TYPE::END];
};

