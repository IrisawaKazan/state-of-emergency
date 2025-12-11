//==============================================================
//
// [ball.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"ball.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"player.h"
#include"game.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CBall::CBall(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fRotation = 0.0f;

	m_type = BALL_NONE;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CBall::~CBall()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CBall* CBall::Create(D3DXVECTOR3 pos, BALL type)
{
	CBall* pBall;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// 生成
		pBall = new CBall;

		// 初期化処理
		pBall->Init();

		// タイプの設定
		pBall->SetType(type);

		// 位置の設定
		pBall->SetPosition(pos);

		return pBall;
	}

	return nullptr;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CBall::Init(void)
{
	// 種類の設定処理
	CObject::SetType(TYPE_BALL);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\ball.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	int nNumVtx;    // 頂点数
	DWORD sizeFVF;  // 頂点フォーマットのサイズ
	BYTE* pVtxBuff; // 頂点バッファのポインタ

	// 頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点座標を比較してモデルの最小値, 最大値を取得
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}

		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}

		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}

		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}

		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	m_size = D3DXVECTOR3(m_vtxMax.x - m_vtxMin.x, m_vtxMax.y - m_vtxMin.y, m_vtxMax.z - m_vtxMin.z);

	// 頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

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
void CBall::Uninit(void)
{
	// テクスチャへのポインタの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
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
void CBall::Update(void)
{
	switch (m_type)
	{
	case BALL_000_A:
		if (m_pos.y == 0.0f)
		{
			m_pos.z -= 2.0f;
		}
		else
		{
			m_pos.y += 2.0f;
		}

		// ローテーション
		m_fRotation -= 1.0f;

		m_rot.x = m_fRotation / 15.0f;
		break;

	case BALL_000_B:
		m_pos.x += 2.0f;

		// ローテーション
		m_fRotation -= 1.0f;

		m_rot.z = m_fRotation / 15.0f;
		break;

	default:
		break;
	}

	// 外に出ると消す
	if (m_pos.z > UNINIT_POS_Z || m_pos.z < -UNINIT_POS_Z || m_pos.x < UNINIT_POS_X || m_pos.x > -UNINIT_POS_X)
	{
		Uninit();

		return;
	}

	// 当たり判定
	Collision();
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CBall::Draw(void)
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
void CBall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// 前回の位置の設定処理
//----------------------------------------
void CBall::SetPositionOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//----------------------------------------
// 向きの設定処理
//----------------------------------------
void CBall::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CBall::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CBall::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// 前回の位置の取得処理
//----------------------------------------
D3DXVECTOR3 CBall::GetPosOld(void)
{
	return m_posOld;
}

//----------------------------------------
// 向きの取得処理
//----------------------------------------
D3DXVECTOR3 CBall::GetRot(void)
{
	return m_rot;
}

//----------------------------------------
// サイズの取得処理
//----------------------------------------
D3DXVECTOR3 CBall::GetSize(void)
{
	return m_size;
}

//----------------------------------------
// 当たり判定の処理
//----------------------------------------
void CBall::Collision(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();

	// プレイヤーの位置の取得
	D3DXVECTOR3 pos = pPlayer->GetPos();

	// プレイヤーの前回の位置の取得
	D3DXVECTOR3 posOld = pPlayer->GetPosOld();

	// プレイヤーの移動量の取得
	D3DXVECTOR3 move = pPlayer->GetMove();

	// プレイヤーのサイズの取得
	D3DXVECTOR3 size = pPlayer->GetSize();

	// 左右のめり込み判定
	if (pos.z + size.z / 2.0f <	// (奥から手前)プレイヤーの今いる場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
		m_pos.z + m_vtxMax.z &&	// このモデルの今ある場所から見て, モデルの原点から見た奥へのサイズ分よりZ軸の数値が小さい(手前にいる)時且つ,
		pos.z + size.z / 2.0f >	// (手前から奥)プレイヤーの今いる場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
		m_pos.z + m_vtxMin.z)	// このモデルの今ある場所から見て, モデルの原点から見た手前へのサイズ分よりZ軸の数値が大きい(奥にいる)時はめり込んでいる
	{
		// 左から右へ
		if (posOld.x + size.x / 2.0f >	// プレイヤーの以前いた場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
			m_pos.x + m_vtxMin.x &&		// このモデルの今ある場所から見て, モデルの原点から見た左へのサイズ分よりX軸の数値が大きい(右にいる)時且つ,
			pos.x + size.x / 2.0f <		// プレイヤーのいる場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
			m_pos.x + m_vtxMax.x)		// このモデルの今ある場所から見て, モデルの原点から見た右へのサイズ分よりX軸の数値が小さい(左にいる)時はめり込んでいる
		{
			pPlayer->SetEnable(false);

			return;
		}
		// 右から左へ
		if (posOld.x + size.x / 2.0f <	// プレイヤーの以前いた場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
			m_pos.x + m_vtxMax.x &&		// このモデルの今ある場所から見て, モデルの原点から見た右へのサイズ分よりX軸の数値が小さい(左にいる)時且つ,
			pos.x + size.x / 2.0f >		// プレイヤーのいる場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
			m_pos.x + m_vtxMin.x)		// このモデルの今ある場所から見て, モデルの原点から見た左へのサイズ分よりX軸の数値が大きい(右にいる)時はめり込んでいる
		{
			pPlayer->SetEnable(false);

			return;
		}
	}

	// 奥行のめり込み判定
	if (pos.x + size.x / 2.0f <	// (左から右)プレイヤーの今いる場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
		m_pos.x + m_vtxMax.x &&	// このモデルの今ある場所から見て, モデルの原点から見た右へのサイズ分よりX軸の数値が小さい(左にいる)時且つ,
		pos.x + size.x / 2.0f >	// (右から左)プレイヤーの今いる場所から見て, プレイヤーの左右(X)のサイズの半分の数値が
		m_pos.x + m_vtxMin.x)	// このモデルの今ある場所から見て, モデルの原点から見た左へのサイズ分よりX軸の数値が大きい(右にいる)時はめり込んでいる
	{
		// 手前から奥へ
		if (posOld.z + size.z / 2.0f >	// プレイヤーの以前いた場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
			m_pos.z + m_vtxMin.z &&		// このモデルの今ある場所から見て, モデルの原点から見た手前へのサイズ分よりZ軸の数値が大きい(奥にいる)時且つ,
			pos.z + size.z / 2.0f <		// プレイヤーの以前いた場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
			m_pos.z + m_vtxMax.z)		// このモデルの今ある場所から見て, モデルの原点から見た奥へのサイズ分よりZ軸の数値が小さい(手前にいる)時はめり込んでいる
		{
			pPlayer->SetEnable(false);

			return;
		}
		// 奥から手前へ
		if (posOld.z + size.z / 2.0f <	// プレイヤーの以前いた場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
			m_pos.z + m_vtxMax.z &&		// このモデルの今ある場所から見て, モデルの原点から見た奥へのサイズ分よりZ軸の数値が小さい(手前にいる)時且つ,
			pos.z + size.z / 2.0f >		// プレイヤーの以前いた場所から見て, プレイヤーの奥行(Z)のサイズの半分の数値が
			m_pos.z + m_vtxMin.z)		// このモデルの今ある場所から見て, モデルの原点から見た手前へのサイズ分よりZ軸の数値が大きい(奥にいる)時はめり込んでいる
		{
			pPlayer->SetEnable(false);

			return;
		}
	}
}