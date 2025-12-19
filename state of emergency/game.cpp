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
#include"bottle.h"
#include"bottle_rare.h"
#include"wall.h"
#include"meshfield.h"
#include"tunnel.h"
#include"key.h"
#include"door_center.h"
#include"pipe.h"
#include"traffic_lights.h"
#include"punch.h"
#include"blood.h"

// 静的メンバ変数宣言
CPlayer* CGame::m_pPlayer = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	for (int nCnt = 0; nCnt < MAX_BALLCOUNTER; nCnt++)
	{
		m_nCnt[nCnt] = NULL;
	}

	m_nSpawn = NULL;

	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
	{
		m_nFrameCounter[nCnt] = NULL;
	}

	m_nKeyCnt = NULL;

	m_nEscapeCnt = NULL;

	m_nKeyNum = NULL;

	m_nGameOverCnt = NULL;
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
	// スコアのテクスチャの読み込み
	CScore::Load();

	// タイマーのテクスチャの読み込み
	CTimer::Load();

	// 血のテクスチャの読み込み
	CBlood::Load();


	// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-NUM_WALL_X + 25.0f, 10.0f, NUM_WALL_Z - 50.0f));

	// フロアボックス
	//CFloorBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	

	// ドア
	CDoor::Create(D3DXVECTOR3(GOAL_POS_X, 0.0f, GOAL_POS_Z));
	CDoorCenter::Create(D3DXVECTOR3(GOAL_POS_X - 14.0f, 0.0f, GOAL_POS_Z));

	// パイプ型トンネル
	CTunnel::Create(D3DXVECTOR3(BALL_DEPTH_POS_X, -150.0f, BALL_DEPTH_POS_Z + 10.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f));
	CTunnel::Create(D3DXVECTOR3(BALL_BESIDE_POS_X - 20.0f, -150.0f, BALL_BESIDE_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI / 0.5f, 0.0f));
	CTunnel::Create(D3DXVECTOR3(BALL_DEPTH_POS_X - 175.0f, -150.0f, BALL_DEPTH_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f));
	CTunnel::Create(D3DXVECTOR3(BALL_BESIDE_POS_X - 20.0f, -150.0f, BALL_BESIDE_POS_Z - 75.0f), D3DXVECTOR3(0.0f, D3DX_PI / 0.5f, 0.0f));

	// パイプ
	CPipe::Create(D3DXVECTOR3(0.0f, -150.0f, -360.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f));
	CPipe::Create(D3DXVECTOR3(460.0f, -150.0f, BALL_BESIDE_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPipe::Create(D3DXVECTOR3(-175.0f, -150.0f, -360.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f));
	CPipe::Create(D3DXVECTOR3(460.0f, -150.0f, BALL_BESIDE_POS_Z - 75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// パンチ
	CPunch::Create(D3DXVECTOR3(350.0f, 0.0f, 250.0f), D3DXVECTOR3(0.0f, D3DX_PI / 4.0f, 0.0f), CPunch::PUNCH_000_A);
	CPunch::Create(D3DXVECTOR3(-350.0f, 0.0f, 250.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 4.0f, 0.0f), CPunch::PUNCH_000_B);
	CPunch::Create(D3DXVECTOR3(350.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, D3DX_PI / -0.75f, 0.0f), CPunch::PUNCH_000_C);
	CPunch::Create(D3DXVECTOR3(-350.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, D3DX_PI / 0.75f, 0.0f), CPunch::PUNCH_000_D);

	//// 信号機
	//CTrafficLights::Create(D3DXVECTOR3(-250.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// スコア
	CScore::Create(D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f - 67.5f, 35.0f, 0.0f), 30.0f, 90.0f);

	// フィールド
	CMeshfield::Create(D3DXVECTOR3(0.0f, -25.0f, 0.0f));

	// テスト配置
	{
		// ボール
		CBall::Create(D3DXVECTOR3(BALL_DEPTH_POS_X, BALL_DEPTH_POS_Y, BALL_DEPTH_POS_Z), CBall::BALL_000_A);
		CBall::Create(D3DXVECTOR3(BALL_BESIDE_POS_X, BALL_BESIDE_POS_Y, BALL_BESIDE_POS_Z), CBall::BALL_000_B);

		// ボトル
		CBottle::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));

		// レアボトル
		CBottleRare::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
	}

#ifdef _DEBUG // Debug時のみ

	// タイマー
	CTimer::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 200.0f, 675.0f, 0.0f), 30.0f, 90.0f);

#endif

#ifdef NDEBUG // Release時のみ

	// タイマー
	CTimer::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 200.0f, 675.0f, 0.0f), 30.0f, 90.0f);

#endif

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_GAME_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CGame::Uninit(void)
{
	// スコアのテクスチャの破棄
	CScore::Unload();

	// タイマーのテクスチャの破棄
	CTimer::Unload();

	// 血のテクスチャの破棄
	CBlood::Unload();

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

	if (m_pPlayer->GetEnable() == true)
	{
		// ボール生成用カウンターのインクリメント
		for (int nCnt = 0; nCnt < MAX_BALLCOUNTER; nCnt++)
		{
			m_nCnt[nCnt]++;
		}

		if (m_nCnt[0] >= 60 * 5)
		{
			// ボール
			CBall::Create(D3DXVECTOR3(BALL_DEPTH_POS_X, BALL_DEPTH_POS_Y, BALL_DEPTH_POS_Z), CBall::BALL_000_A);

			m_nCnt[0] = 0;
		}
		if (m_nCnt[1] >= 60 * 7)
		{
			// ボール
			CBall::Create(D3DXVECTOR3(BALL_BESIDE_POS_X, BALL_BESIDE_POS_Y, BALL_BESIDE_POS_Z), CBall::BALL_000_B);

			m_nCnt[1] = 0;
		}
		if (m_nCnt[2] >= 60 * 11)
		{
			// ボール
			CBall::Create(D3DXVECTOR3(BALL_DEPTH_POS_X - 175.0f, BALL_DEPTH_POS_Y, BALL_DEPTH_POS_Z), CBall::BALL_000_A);

			m_nCnt[2] = 0;
		}
		if (m_nCnt[3] >= 60 * 13)
		{
			// ボール
			CBall::Create(D3DXVECTOR3(BALL_BESIDE_POS_X, BALL_BESIDE_POS_Y, BALL_BESIDE_POS_Z - 75.0f), CBall::BALL_000_B);

			m_nCnt[3] = 0;
		}

		// ランダム生成
		m_nSpawn++;

		float fPosX = (float)(rand() % (int)NUM_WALL_X - 25/* 出てくる範囲 */);
		float fPosZ = (float)(rand() % (int)NUM_WALL_Z - 25/* 出てくる範囲 */);

		// 多段で出ないように制限するカウンター
		for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
		{
			m_nFrameCounter[nCnt]++;
		}

		if (m_pPlayer->GetKey() == false)
		{
			// ボトル
			if (m_nSpawn >= rand() / MAX_SPAWN && m_nFrameCounter[0] >= NUM_FRAME_CNT)
			{
				CBottle::Create(D3DXVECTOR3(fPosX, 0.0f, fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[0] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN && m_nFrameCounter[1] >= NUM_FRAME_CNT)
			{
				CBottle::Create(D3DXVECTOR3(-fPosX, 0.0f, fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[1] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN && m_nFrameCounter[2] >= NUM_FRAME_CNT)
			{
				CBottle::Create(D3DXVECTOR3(fPosX, 0.0f, -fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[2] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN && m_nFrameCounter[3] >= NUM_FRAME_CNT)
			{
				CBottle::Create(D3DXVECTOR3(-fPosX, 0.0f, -fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[3] = 0;
			}

			// レアボトル
			if (m_nSpawn >= rand() / MAX_SPAWN_RARE && m_nFrameCounter[4] >= NUM_FRAME_CNT_RARE)
			{
				CBottleRare::Create(D3DXVECTOR3(fPosX, 0.0f, fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[4] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN_RARE && m_nFrameCounter[5] >= NUM_FRAME_CNT_RARE)
			{
				CBottleRare::Create(D3DXVECTOR3(-fPosX, 0.0f, fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[5] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN_RARE && m_nFrameCounter[6] >= NUM_FRAME_CNT_RARE)
			{
				CBottleRare::Create(D3DXVECTOR3(fPosX, 0.0f, -fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[6] = 0;
			}
			if (m_nSpawn >= rand() / MAX_SPAWN_RARE && m_nFrameCounter[7] >= NUM_FRAME_CNT_RARE)
			{
				CBottleRare::Create(D3DXVECTOR3(-fPosX, 0.0f, -fPosZ));

				m_nSpawn = 0;
				m_nFrameCounter[7] = 0;
			}
		}

		//// 鍵のカウンター
		//if (m_nKeyCnt <= 60 * KEY_TIME)
		//{
		//	m_nKeyCnt++;
		//}
		//if (m_nKeyCnt == 60 * KEY_TIME)
		//{
		//	// 鍵
		//	CKey::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//}

		// 基準のポイントで鍵が出る
		if (m_pPlayer->GetPoint() >= KEY_POINT)
		{
			if (m_nKeyNum == 0)
			{
				// 鍵
				CKey::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nKeyNum = 1;
			}
		}

		// 強制終了までのカウンター
		if (m_nEscapeCnt <= 60 * TIME_OUT)
		{
			m_nEscapeCnt++;
		}
		if (m_nEscapeCnt == 60 * TIME_OUT)
		{
			CManager::SetMode(MODE_GAMEOVER);

			return;
		}
	}

	// ゴール
	if (m_pPlayer->GetPos().x >= GOAL_POS_X - 25.0f && m_pPlayer->GetPos().x <= GOAL_POS_X + 25.0f &&
		m_pPlayer->GetPos().z >= GOAL_POS_Z - 25.0f && m_pPlayer->GetPos().z <= GOAL_POS_Z + 25.0f && m_pPlayer->GetKey() == true)
	{
		CManager::SetMode(MODE_RESULT);

		return;
	}

#ifdef _DEBUG // Debug時のみ

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// 確認用
	// スコア加算(+100)
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		// スコア加算
		CScore::AddScore(100);

		m_pPlayer->SetPoint(100);

		// SE
		pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
	}
	// スコア減算(-10)
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		// スコア加算
		CScore::AddScore(-10);

		m_pPlayer->SetPoint(-10);

		// SE
		pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
	}

	if (m_pPlayer->GetEnable() == false)
	{
		// デバッグ用プレイヤー復活
		if (pInputKeyboard->GetTrigger(DIK_NUMPADPLUS) == true)
		{// 10キーの+
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_nKeyNum = 0;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_GAMEOVER);

		return;
	}

#endif

#ifdef NDEBUG // Release時のみ(リリースの場合のリザルトの飛び方にバリエーションなどをつけるため)

	if (m_pPlayer->GetEnable() == false)
	{
		m_nGameOverCnt++;

		if (m_nGameOverCnt >= 60 * 0 && m_nGameOverCnt < 60 * 2)
		{
			if (m_nGameOverCnt == 60 * 0 + 10)
			{
				CBlood::Create(D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f, 0.0f), (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			}
		}
		if (m_nGameOverCnt >= 60 * 2)
		{
			CManager::SetMode(MODE_GAMEOVER);

			return;
		}
	}

#endif
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CGame::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	if (m_pPlayer->GetEnable() == true)
	{
		CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n*-------------------------------------------*");
		CDebugProc::Draw();

		//// 鍵が出るまでのカウンターをデバッグ表示
		//CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nKey counter [%dで出現]: %d", KEY_TIME, m_nKeyCnt / 60);
		//CDebugProc::Draw();

		// 鍵が出るまでのカウンターをデバッグ表示
		CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n強制終了 [%dで遷移]: %d", TIME_OUT, m_nEscapeCnt / 60);
		CDebugProc::Draw();
	}

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Game");
	CDebugProc::Draw();

#endif
}