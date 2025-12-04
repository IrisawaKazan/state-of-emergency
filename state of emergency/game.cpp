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
#include"player.h"
#include"objectBillboard.h"
#include"debugproc.h"
#include"effect.h"
#include"pause.h"
#include"floorBox.h"
#include"ball.h"
#include"door.h"

// 静的メンバ変数宣言
CPlayer* CGame::m_pPlayer = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	m_nCnt = NULL;
	//m_nSpawn = NULL;
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


	// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-300.0f, 10.0f, 150.0f));

	// フロアボックス
	CFloorBox::Create(D3DXVECTOR3(-200.0f, -50.0f, 100.0f));
	CFloorBox::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f));
	CFloorBox::Create(D3DXVECTOR3(250.0f, 0.0f, 0.0f));

	// ドア
	CDoor::Create(D3DXVECTOR3(GOAL_POS_X, 0.0f, GOAL_POS_Z));

	// ボール
	CBall::Create(D3DXVECTOR3(0.0f, 0.0f, BALL_POS_Z));

	// スコア
	CScore::Create(D3DXVECTOR3(1100.0f, 50.0f, 0.0f), 30.0f, 90.0f);

	// タイマー
	CTimer::Create(D3DXVECTOR3(50.0f, 675.0f, 0.0f), 30.0f, 90.0f);


	// サウンドの取得
	CSound* pSound = CManager::GetSound();

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

	// 現在の時刻を種として設定
	srand((unsigned int)time(nullptr));

	m_nCnt++;

	if (m_nCnt >= 60 * 5)
	{
		// ボール
		CBall::Create(D3DXVECTOR3(0.0f, 0.0f, BALL_POS_Z));

		m_nCnt = 0;
	}

	// ゴール
	if (m_pPlayer->GetPos().x >= GOAL_POS_X - 25.0f && m_pPlayer->GetPos().x <= GOAL_POS_X + 25.0f &&
		m_pPlayer->GetPos().z >= GOAL_POS_Z - 25.0f && m_pPlayer->GetPos().z <= GOAL_POS_Z + 25.0f)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_RESULT);
	}

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

	if (m_pPlayer->GetEnable() == false)
	{
		// デバッグ用プレイヤー復活
		if (pInputKeyboard->GetTrigger(DIK_NUMPADPLUS) == true)
		{// 10キーの+
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_RESULT);
	}

#endif

#ifdef NDEBUG // Release時のみ(リリースの場合のリザルトの飛び方にバリエーションなどをつけるため)

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