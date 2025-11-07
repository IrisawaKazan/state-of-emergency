//==============================================================
//
// [title.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"title.h"
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
#include"game.h"

// 静的メンバ変数宣言
//CObjectX* CTitle::m_pObjectX = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
	m_nPlay = NULL;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_nCounter[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER_F; nCnt++)
	{
		m_nFrameCounter[nCnt] = NULL;
	}

	m_nSpawnFloating = NULL;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTitle::~CTitle()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTitle::Init(void)
{
	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_TITLE_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CTitle::Uninit(void)
{
	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CTitle::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON) == true == true)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_TUTORIAL);
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTitle::Draw(void)
{

}