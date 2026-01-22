//==============================================================
//
// [titleOBJ.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"titleOBJ.h"
#include"manager.h"
#include"renderer.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTitleObjX::CTitleObjX(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();

	m_fMove = 0.0f;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nMovingCounter[nCnt] = NULL;
	}
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTitleObjX::~CTitleObjX()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CTitleObjX* CTitleObjX::Create(D3DXVECTOR3 pos)
{
	CTitleObjX* pTitleObj;

	// オブジェクトXの生成
	pTitleObj = new CTitleObjX;

	// 初期化処理
	pTitleObj->Init();

	// 位置の設定
	pTitleObj->SetPosition(pos);

	return pTitleObj;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTitleObjX::Init(void)
{
	// 種類の設定処理
	CObject::SetType(TYPE_TITLE_OBJ);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(D3DX_PI / -4.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\title.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	D3DXMATERIAL* pMat = nullptr; // マテリアルへのポインタ

	// マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			// このファイル名を使用してテクスチャを読み込む


			// テクスチャの読み込み


			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture);
		}
	}

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CTitleObjX::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	CObject::Release();
	//this->Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CTitleObjX::Update(void)
{
	m_nMovingCounter[0]++;

	// 上下移動
	if (m_nMovingCounter[0] <= 60 * 2)
	{
		m_fMove += 0.05f;
	}
	else
	{
		m_nMovingCounter[1]++;

		if (m_nMovingCounter[1] <= 60)
		{
			m_fMove += 0.02f;
		}
		else
		{
			m_nMovingCounter[2]++;

			if (m_nMovingCounter[2] <= 60 * 2)
			{
				m_fMove -= 0.05f;
			}
			else
			{
				m_fMove -= 0.02f;
			}
		}
	}

	if (m_pos.z <= 0.0f)
	{
		m_nMovingCounter[0] = 0;

		m_nMovingCounter[1] = 0;

		m_nMovingCounter[2] = 0;
	}

	m_pos.z = m_fMove;
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTitleObjX::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DMATERIAL9 matDef; // 現在のマテリアル保存用

	D3DXMATERIAL* pMat; // マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture); // 今はNULL

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CTitleObjX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CTitleObjX::GetPos(void)
{
	return m_pos;
}