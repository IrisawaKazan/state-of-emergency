//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"tutorial.h"
#include"input.h"
#include"sound.h"
#include"debugproc.h"
#include"tutorialOBJ.h"
#include"tutorialTex.h"
#include"playerTex.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{
	m_nEnterCnt = NULL;
	m_bEnter = false;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTutorial::~CTutorial()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTutorial::Init(void)
{
	// チュートリアルのテクスチャの読み込み
	CTutorialTex::Load();

	// プレイヤーのテクスチャの読み込み
	CPlayerTex::Load();

	// チュートリアルテクスチャ生成
	CTutorialTex::Create(D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f, 0.0f), (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	//// チュートリアルオブジェクトの生成
	//CTutorialObjX::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CTutorial::Uninit(void)
{
	// チュートリアルのテクスチャの破棄
	CTutorialTex::Unload();

	// プレイヤーのテクスチャの破棄
	CPlayerTex::Unload();

	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CTutorial::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON) == true && m_bEnter == false)
	{// 決定キー(ENTERキー)が押された
		m_bEnter = true;
	}

	if (m_bEnter == true)
	{
		// インクリメント
		m_nEnterCnt++;

		if (m_nEnterCnt >= 60 * 0 && m_nEnterCnt < 60 * 2)
		{
			if (m_nEnterCnt == 60 * 0 + 1)
			{
				// SE
				pSound->PlaySoundA(CSound::SOUND_LABEL_TUTORIAL_PLAYER_SE);

				// プレイヤーのテクスチャ生成
				CPlayerTex::Create(D3DXVECTOR3(-50.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f), 200.0f, 250.0f);
			}
		}
		if (m_nEnterCnt >= 60 * 2)
		{
			CManager::SetMode(MODE_GAME);

			m_bEnter = false;

			m_nEnterCnt = 0;
		}
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTutorial::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Tutorial");
	CDebugProc::Draw();

#endif
}