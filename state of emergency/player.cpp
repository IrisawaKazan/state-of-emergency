//==============================================================
//
// [player.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"player.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"debugproc.h"
#include"game.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();

	m_fRotation = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bJump = false;
	m_nJumpCnt = NULL;
	m_bJumpCnt = false;

	m_bUse = true;

	m_fDash = 0.0f;
	m_bDash = false;

	m_bKey = false;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer;

	// 生成
	pPlayer = new CPlayer;

	// 初期化処理
	pPlayer->Init();

	// 位置の設定
	pPlayer->SetPosition(pos);

	return pPlayer;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	// 種類の設定処理
	CObject::SetType(TYPE_PLAYER);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\rot_tester.x",
	//D3DXLoadMeshFromX("data\\MODEL\\floorBox000.x",
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
void CPlayer::Uninit(void)
{
	// テクスチャの破棄
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
void CPlayer::Update(void)
{
	//m_bUse = GetEnable();

	if (m_bUse == true)
	{
		// キーボードの取得
		CInputKeyboard* pInputKeyboard;
		pInputKeyboard = CManager::GetInputKeyboard();

		// マウスの取得
		CInputMouse* pInputMouse;
		pInputMouse = CManager::GetInputMouse();

		// パッドの取得
		CInputJoypad* pInputJoypad;
		pInputJoypad = CManager::GetInputJoypad();

		//// サウンドの取得
		//CSound* pSound = CManager::GetSound();

		// 位置の取得
		D3DXVECTOR3 pos = GetPos();

		// 前回の位置を保存
		m_posOld = m_pos;

		// 位置を更新
		m_pos.x += m_move.x; // 左右移動
		m_pos.y += m_move.y; // 落下
		m_pos.z += m_move.z; // 奥行移動

		if (m_bDash == false)
		{
			// 移動量を更新(減衰させる)
			m_move.x += (0.0f - m_move.x) * 0.25f;
			m_move.z += (0.0f - m_move.z) * 0.25f;
		}
		else
		{
			// 移動量を更新(減衰させる)
			m_move.x += (0.0f - m_move.x) * 0.2f;
			m_move.z += (0.0f - m_move.z) * 0.2f;
		}

		// 最終的には消す(床)
		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;
			m_move.y = 0.0f;
			m_bJump = false;
		}

		// 壁
		if (m_pos.x < -NUM_WALL_X)
		{
			m_pos.x = -NUM_WALL_X;
		}
		if (m_pos.x > NUM_WALL_X)
		{
			m_pos.x = NUM_WALL_X;
		}
		if (m_pos.z < -NUM_WALL_Z)
		{
			m_pos.z = -NUM_WALL_Z;
		}
		if (m_pos.z > NUM_WALL_Z)
		{
			m_pos.z = NUM_WALL_Z;
		}
		// 鍵を持っていないとき
		if (m_bKey == false)
		{
			if (m_pos.x > GOAL_POS_X - 25.0f && m_pos.z > GOAL_POS_Z)
			{
				m_pos.x = GOAL_POS_X - 25.0f;
			}
			if (m_pos.z > GOAL_POS_Z - 25.0f && m_pos.x > GOAL_POS_X)
			{
				m_pos.z = GOAL_POS_Z - 25.0f;
			}
		}

		//-----------------
		// プレイヤー移動
		//-----------------
		if ((pInputKeyboard->GetPress(DIK_D) && pInputKeyboard->GetPress(DIK_W) && pInputKeyboard->GetPress(DIK_A) && pInputKeyboard->GetPress(DIK_S)) ||
			(pInputKeyboard->GetPress(DIK_RIGHT) && pInputKeyboard->GetPress(DIK_UP) && pInputKeyboard->GetPress(DIK_LEFT) && pInputKeyboard->GetPress(DIK_DOWN)) ||
			(pInputJoypad->GetPress(pInputJoypad->JOYKEY_RIGHT) && pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) && pInputJoypad->GetPress(pInputJoypad->JOYKEY_LEFT) && pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN)) == true)
		{// 全方向押した場合
			// なし
		}
		else if ((pInputKeyboard->GetPress(DIK_D) && pInputKeyboard->GetPress(DIK_A)) ||
			(pInputKeyboard->GetPress(DIK_RIGHT) && pInputKeyboard->GetPress(DIK_LEFT)) ||
			(pInputJoypad->GetPress(pInputJoypad->JOYKEY_RIGHT) && pInputJoypad->GetPress(pInputJoypad->JOYKEY_LEFT)) == true)
		{// 東西押した場合
			if (pInputKeyboard->GetPress(DIK_W) || pInputKeyboard->GetPress(DIK_UP) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) == true)
			{// 北
				m_move.z += MAX_PLAYER_MOVE;

				m_rot.y = D3DX_PI;
			}
			else if (pInputKeyboard->GetPress(DIK_S) || pInputKeyboard->GetPress(DIK_DOWN) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN) == true)
			{// 南
				m_move.z -= MAX_PLAYER_MOVE;

				m_rot.y = 0.0f;
			}
		}
		else if ((pInputKeyboard->GetPress(DIK_W) && pInputKeyboard->GetPress(DIK_S)) ||
			(pInputKeyboard->GetPress(DIK_UP) && pInputKeyboard->GetPress(DIK_DOWN)) ||
			(pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) && pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN)) == true)
		{// 南北押した場合
			if (pInputKeyboard->GetPress(DIK_A) || pInputKeyboard->GetPress(DIK_LEFT) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_LEFT) == true)
			{// 西
				m_move.x -= MAX_PLAYER_MOVE;

				m_rot.y = D3DX_PI / 2.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) || pInputKeyboard->GetPress(DIK_RIGHT) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_RIGHT) == true)
			{// 東
				m_move.x += MAX_PLAYER_MOVE;

				m_rot.y = -D3DX_PI / 2.0f;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) || pInputKeyboard->GetPress(DIK_LEFT) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_LEFT) == true)
		{// 西方向
			if (pInputKeyboard->GetPress(DIK_W) || pInputKeyboard->GetPress(DIK_UP) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) == true)
			{// 北西
				m_move.x -= MAX_PLAYER_MOVE / (float)sqrt(2); // 三平方の定理のため√2を割る
				m_move.z += MAX_PLAYER_MOVE / (float)sqrt(2);

				m_rot.y = D3DX_PI / -0.75f;
			}
			else if (pInputKeyboard->GetPress(DIK_S) || pInputKeyboard->GetPress(DIK_DOWN) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN) == true)
			{// 南西
				m_move.x -= MAX_PLAYER_MOVE / (float)sqrt(2);
				m_move.z -= MAX_PLAYER_MOVE / (float)sqrt(2);

				m_rot.y = D3DX_PI / 4.0f;
			}
			else
			{// 西
				m_move.x -= MAX_PLAYER_MOVE;

				m_rot.y = D3DX_PI / 2.0f;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_D) || pInputKeyboard->GetPress(DIK_RIGHT) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_RIGHT) == true)
		{// 東方向
			if (pInputKeyboard->GetPress(DIK_W) || pInputKeyboard->GetPress(DIK_UP) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) == true)
			{// 北東
				m_move.x += MAX_PLAYER_MOVE / (float)sqrt(2);
				m_move.z += MAX_PLAYER_MOVE / (float)sqrt(2);

				m_rot.y = D3DX_PI / 0.75f;
			}
			else if (pInputKeyboard->GetPress(DIK_S) || pInputKeyboard->GetPress(DIK_DOWN) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN) == true)
			{// 南東
				m_move.x += MAX_PLAYER_MOVE / (float)sqrt(2);
				m_move.z -= MAX_PLAYER_MOVE / (float)sqrt(2);

				m_rot.y = -D3DX_PI / 4.0f;
			}
			else
			{// 東
				m_move.x += MAX_PLAYER_MOVE;

				m_rot.y = -D3DX_PI / 2.0f;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_W) || pInputKeyboard->GetPress(DIK_UP) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_UP) == true)
		{// 北方向
			m_move.z += MAX_PLAYER_MOVE;

			m_rot.y = D3DX_PI;
		}
		else if (pInputKeyboard->GetPress(DIK_S) || pInputKeyboard->GetPress(DIK_DOWN) || pInputJoypad->GetPress(pInputJoypad->JOYKEY_DOWN) == true)
		{// 南方向
			m_move.z -= MAX_PLAYER_MOVE;

			m_rot.y = 0.0f;
		}

		// 重力
		if (m_pos.y >= 0.0f)
		{
			m_move.y -= 0.98f;
		}
		else
		{
			// ジャンプ抑制
			m_bJump = false;
		}

		// ジャンプ
		if ((pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_A) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON)) && m_bJump == false)
		{
			m_bJump = true;

			m_bJumpCnt = true;
		}
		// ジャンプカウンターの起動
		if (m_bJumpCnt == true)
		{
			m_nJumpCnt++;
		}
		// 10フレームジャンプ
		if (m_nJumpCnt > 0 && m_nJumpCnt <= 5)
		{
			m_move.y += MAX_PLAYER_JUMP;
		}
		// 10フレーム過ぎたら
		if (m_nJumpCnt > 10)
		{
			m_nJumpCnt = 0;

			m_bJumpCnt = false;
		}

		// ダッシュ
		if (pInputKeyboard->GetPress(DIK_B) || pInputKeyboard->GetPress(DIK_LSHIFT) ||
			pInputJoypad->GetPress(pInputJoypad->JOYKEY_B) || pInputMouse->GetPress(pInputMouse->MOUSE_RIGHTBUTTON) == true)
		{
			m_fDash = MAX_DASH;

			m_bDash = true;
		}
		else
		{
			m_fDash = 1.0f;

			m_bDash = false;
		}

		// ローテーション
		m_fRotation -= 1.0f;
		m_rot.z = m_fRotation / 50.0f;
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CPlayer::Draw(void)
{
	if (m_bUse == true)
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

#ifdef _DEBUG // Debug時のみ

		// プレイヤーのpos, rot, moveをデバッグ表示
		CDebugProc::Print("\nPlayer pos: %.4f, %.4f, %.4f", m_pos.x, m_pos.y, m_pos.z);
		CDebugProc::Draw();

		CDebugProc::Print("\n\nPlayer pos: %.4f, %.4f, %.4f", m_rot.x, m_rot.y, m_rot.z);
		CDebugProc::Draw();

		CDebugProc::Print("\n\n\nPlayer move: %.4f, %.4f, %.4f", m_move.x, m_move.y, m_move.z);
		CDebugProc::Draw();

#endif
	}
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CPlayer::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// 前回の位置の設定処理
//----------------------------------------
void CPlayer::SetPositionOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//----------------------------------------
// 移動量の設定処理
//----------------------------------------
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//----------------------------------------
// 向きの設定処理
//----------------------------------------
void CPlayer::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CPlayer::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// 前回の位置の取得処理
//----------------------------------------
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

//----------------------------------------
// 移動量の取得処理
//----------------------------------------
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//----------------------------------------
// 向きの取得処理
//----------------------------------------
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//----------------------------------------
// サイズの取得処理
//----------------------------------------
D3DXVECTOR3 CPlayer::GetSize(void)
{
	return m_size;
}