//==============================================================
//
// [timeoverOBJ.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"timeoverOBJ.h"
#include"manager.h"
#include"renderer.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTimeoverObj::CTimeoverObj(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTimeoverObj::~CTimeoverObj()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CTimeoverObj* CTimeoverObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTimeoverObj* pTimeoverObj;

	// オブジェクトXの生成
	pTimeoverObj = new CTimeoverObj;

	// 初期化処理
	pTimeoverObj->Init();

	// 位置の設定
	pTimeoverObj->SetPosition(pos);

	// 向きの設定
	pTimeoverObj->SetRotation(rot);

	return pTimeoverObj;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTimeoverObj::Init(void)
{
	// 種類の設定処理
	CObject::SetType(TYPE_TIMEOVER_OBJ);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\timeoverOBJ.x",
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
void CTimeoverObj::Uninit(void)
{
	// テクスチャへのポインタの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

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
void CTimeoverObj::Update(void)
{

}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTimeoverObj::Draw(void)
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
void CTimeoverObj::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// 向きの設定処理
//----------------------------------------
void CTimeoverObj::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CTimeoverObj::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// 向きの取得処理
//----------------------------------------
D3DXVECTOR3 CTimeoverObj::GetRot(void)
{
	return m_rot;
}