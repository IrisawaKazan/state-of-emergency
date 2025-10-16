//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"tutorial.h"
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

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{

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

	//// サウンドの取得
	//CSound* pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON) == true)
	{// 決定キー(ENTERキー)が押された
		CManager::SetMode(MODE_GAME);
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTutorial::Draw(void)
{

}