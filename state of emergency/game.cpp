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


//----------------------------------------
// コンストラクタ
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{

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
		CManager::SetMode(MODE_RESULT);
	}

#endif

#ifdef NDEBUG // Release時のみ

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_RESULT);
	}

#endif

}

//----------------------------------------
// 描画処理
//----------------------------------------
void CGame::Draw(void)
{
	/* ゲーム画面だけにある特別な描画があるなら記入する */
}