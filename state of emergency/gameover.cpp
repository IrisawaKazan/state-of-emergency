//==============================================================
//
// [gameover.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"gameover.h"
#include"input.h"
#include"sound.h"
#include"debugproc.h"
#include"gameoverTex.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGameover::CGameover() : CScene(CScene::MODE_GAMEOVER)
{
	m_nEnterCnt = NULL;
	m_bEnter = false;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CGameover::~CGameover()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CGameover::Init(void)
{
	// ゲームオーバーのテクスチャの読み込み
	CGameoverTex::Load();

	// ゲームオーバーテクスチャ生成
	CGameoverTex::Create(D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f, 0.0f), (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_GAMEOVER_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CGameover::Uninit(void)
{
	// ゲームオーバーのテクスチャの破棄
	CGameoverTex::Unload();

	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CGameover::Update(void)
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

		}
		if (m_nEnterCnt >= 60 * 2)
		{
			CManager::SetMode(MODE_TITLE);

			m_bEnter = false;

			m_nEnterCnt = 0;
		}
	}

}

//----------------------------------------
// 描画処理
//----------------------------------------
void CGameover::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Game Over");
	CDebugProc::Draw();

#endif
}