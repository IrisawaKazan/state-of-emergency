//==============================================================
//
// [game.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"game.h"
#include"object2D.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"light.h"
#include"object3D.h"
#include"timer.h"
#include"objectX.h"
#include"objectBillboard.h"
#include"debugproc.h"
#include"effect.h"
#include"pause.h"

// 静的メンバ変数宣言
CObjectX* CGame::m_pObjectX = nullptr;
CPause* CGame::m_pPause = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	m_bPause = false;
	m_nSpawn = NULL;

	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
	{
		m_nFrameCounter[nCnt] = NULL;
	}

	m_nScrapCounter = NULL;
	m_nSmallThingsCounter = NULL;
	m_nBlackThingsCounter = NULL;

	m_nSmallThingsSpawn = NULL;

	m_nTransition = NULL;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CGame::~CGame()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CGame::Init(void)
{
	// エフェクトのテクスチャの読み込み
	CEffect::Load();

	// スコアのテクスチャの読み込み
	CScore::Load();

	// タイマーのテクスチャの読み込み
	CTimer::Load();

	// ポーズのテクスチャの読み込み
	CPause::Load();

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// オブジェクトXの生成(初期配置)
	m_pObjectX = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// スコア
	CScore::Create(D3DXVECTOR3(1100.0f, 50.0f, 0.0f), 30.0f, 90.0f);

#ifdef _DEBUG // Debug時のみ

	// タイマー
	CTimer::Create(D3DXVECTOR3(50.0f, 675.0f, 0.0f), 30.0f, 90.0f);

#endif

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_GAME_BGM);

	m_bPause = false; // ポーズ解除

	m_nTransition = 0;

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CGame::Uninit(void)
{
	// エフェクトのテクスチャの破棄
	CEffect::Unload();

	// スコアのテクスチャの破棄
	CScore::Unload();

	// タイマーのテクスチャの破棄
	CTimer::Unload();

	// ポーズのテクスチャの破棄
	CPause::Unload();

	CObject::Release();

	//// プレイヤーの破棄
	//if (m_pObjectX != nullptr)
	//{
	//	m_pObjectX = nullptr;
	//}
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CGame::Update(void)
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

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	//if (pInputKeyboard->GetTrigger(DIK_TAB) || pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_B) == true)
	//{// プレイヤーが生きている時にポーズキーが押された
	//	m_bPause = m_bPause ? false : true;
	//}

	//if (m_bPause == true)
	{// ポーズ中
		//m_pPause = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

		//m_pPause->Update();

		//m_pPause->Draw();
	}

	//if (m_bPause == false)
	{// ポーズ中でなければ
		// ランダム生成
		m_nSpawn++;
		m_nSmallThingsSpawn++;

		float fPosZ = (float)(rand() % 130/* 出てくる範囲 */);

		// 現在の時刻を種として設定
		srand((unsigned int)time(nullptr));

		// 多段で出ないように制限するカウンター
		for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
		{
			m_nFrameCounter[nCnt]++;
		}

#ifdef _DEBUG // Debug時のみ

		// 確認用
		// スコア加算(+1)
		if (pInputKeyboard->GetTrigger(DIK_1) == true)
		{
			// スコア加算
			CScore::AddScore(1);

			// SE
			pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
		}
		// スコア減算(-1)
		if (pInputKeyboard->GetTrigger(DIK_0) == true)
		{
			// スコア加算
			CScore::AddScore(-1);

			// SE
			pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
		}

		if (m_pObjectX->GetEnable() == false)
		{
			// デバッグ用プレイヤー復活
			if (pInputKeyboard->GetTrigger(DIK_NUMPADPLUS) == true)
			{// 10キーの+
				m_pObjectX = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}

		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
		{// 決定キー(ENTERキー)が押された
			CManager::SetMode(MODE_TITLE);
		}

#endif

#ifdef NDEBUG // Release時のみ

		if (m_pObjectX->GetEnable() == false)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
			{// 決定キー(ENTERキー)が押された
				CManager::SetMode(MODE_TITLE);
			}

			if (m_nTransition <= 60 * 6)
			{
				m_nTransition++;
			}

			if (m_nTransition >= 60 * 6)
			{
				//if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
				{// 決定キー(ENTERキー)が押された
					CManager::SetMode(MODE_TITLE);
				}
			}
		}

#endif

	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CGame::Draw(void)
{
	/* ゲーム画面だけにある特別な描画があるなら記入する */
}

//----------------------------------------
// オブジェクトXの取得処理
//----------------------------------------
CObjectX* CGame::GetObjectX(void)
{
	return m_pObjectX;
}

//----------------------------------------
// ポーズの取得処理
//----------------------------------------
CPause* CGame::GetPause(void)
{
	return m_pPause;
}

//----------------------------------------
// デストロイプレイヤー処理
//----------------------------------------
void CGame::DestoryPlayer(void)
{
	//if (m_pObjectX->GetEnable() == true)
	//{
	//	m_pObjectX->SetEnable(false);
	//}

	m_pObjectX = nullptr;
}