//==============================================================
//
// [game.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
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
CPause* CGame::m_pPause = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	m_bPause = false;
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

	// スコア
	CScore::Create(D3DXVECTOR3(1100.0f, 50.0f, 0.0f), 30.0f, 90.0f);

#ifdef _DEBUG // Debug時のみ

	// タイマー
	CTimer::Create(D3DXVECTOR3(50.0f, 675.0f, 0.0f), 30.0f, 90.0f);

#endif

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_BGM);

	m_bPause = false; // ポーズ解除

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
	//CSound* pSound = CManager::GetSound();

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
		// 現在の時刻を種として設定
		srand((unsigned int)time(nullptr));

#ifdef _DEBUG // Debug時のみ

		// サウンドの取得
		CSound* pSound = CManager::GetSound();

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

		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
		{// 決定キー(ENTERキー)が押された
			CManager::SetMode(MODE_TITLE);
		}

#endif

#ifdef NDEBUG // Release時のみ

		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
		{// 決定キー(ENTERキー)が押された
			CManager::SetMode(MODE_TITLE);
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
// ポーズの取得処理
//----------------------------------------
CPause* CGame::GetPause(void)
{
	return m_pPause;
}