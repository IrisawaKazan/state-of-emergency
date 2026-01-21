//==============================================================
//
// [meshfield.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"meshfield.h"
#include"renderer.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CMeshfield::CMeshfield(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CMeshfield::~CMeshfield()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CMeshfield* CMeshfield::Create(D3DXVECTOR3 pos)
{
	CMeshfield* pMeshfield;

	// 生成
	pMeshfield = new CMeshfield;

	// 初期化処理
	pMeshfield->Init();

	// 位置の設定
	pMeshfield->SetPosition(pos);

	return pMeshfield;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CMeshfield::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\baiitairuno-bi.jpg",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-MAX_POLYGONPOS_X, 0.0f, MAX_POLYGONPOS_Z);
	pVtx[1].pos = D3DXVECTOR3(MAX_POLYGONPOS_X, 0.0f, MAX_POLYGONPOS_Z);
	pVtx[2].pos = D3DXVECTOR3(-MAX_POLYGONPOS_X, 0.0f, -MAX_POLYGONPOS_Z);
	pVtx[3].pos = D3DXVECTOR3(MAX_POLYGONPOS_X, 0.0f, -MAX_POLYGONPOS_Z);

	// 各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CMeshfield::Uninit(void)
{
	// テクスチャの解放
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// 頂点バッファの解放
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CMeshfield::Update(void)
{

}

//----------------------------------------
// 描画処理
//----------------------------------------
void CMeshfield::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

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

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CMeshfield::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CMeshfield::GetPos(void)
{
	return m_pos;
}