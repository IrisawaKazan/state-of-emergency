//==============================================================
//
// [object.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"object.h"
#include"renderer.h"
#include"object2D.h"
#include"camera.h"
#include"manager.h"

// 静的メンバ変数宣言
int CObject::m_nNumAll = NULL;
CObject* CObject::m_apObject[MAX_PRI][MAX_OBJ] = {}; // オブジェクトへのポインタ

//----------------------------------------
// コンストラクタ
//----------------------------------------
CObject::CObject(int nPriority)
{
	m_nID = 0;
	m_type = TYPE_NONE;
	m_nPriority = 0;

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (m_apObject[nPriority][nCntObj] == nullptr)
		{
			m_apObject[nPriority][nCntObj] = this; // 自分自身を代入
			m_nPriority = nPriority;
			m_nID = nCntObj;            // 自分自身のIDを保存
			m_nNumAll++;                // 総数をカウントアップ
			break;
		}
	}
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CObject::~CObject()
{

}

//----------------------------------------
// 全てのオブジェクトの破棄
//----------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// 終了処理
				m_apObject[nCntPri][nCntObj]->Uninit();
			}
		}
	}
}

//----------------------------------------
// 全てのオブジェクトの更新処理
//----------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// 更新処理
				m_apObject[nCntPri][nCntObj]->Update();
			}
		}
	}
}

//----------------------------------------
// 全てのオブジェクトの描画処理
//----------------------------------------
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();

	// カメラの設定
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// 描画処理
				m_apObject[nCntPri][nCntObj]->Draw();
			}
		}
	}
}

//----------------------------------------
// オブジェクトのタイプ設定処理
//----------------------------------------
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//----------------------------------------
// オブジェクトのタイプ取得処理
//----------------------------------------
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}

//----------------------------------------
// オブジェクトの取得処理
//----------------------------------------
CObject* CObject::GetObj(int nPriority, int nIdx)
{
	return m_apObject[nPriority][nIdx];
}

//----------------------------------------
// オブジェクトの総数の取得処理
//----------------------------------------
int CObject::GetNumAll(void)
{
	return m_nNumAll;
}

//----------------------------------------
// オブジェクトの破棄
//----------------------------------------
void CObject::Release(void)
{
	int nPri = this->m_nPriority;
	int nIdx = this->m_nID;

	if (m_apObject[nPri][nIdx] != nullptr)
	{
		delete m_apObject[nPri][nIdx];
		m_apObject[nPri][nIdx] = nullptr;

		m_nNumAll--; // 総数をカウントダウン
	}
}