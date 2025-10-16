//==============================================================
//
// [result.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"result.h"
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
CResult::CResult() : CScene(CScene::MODE_RESULT)
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CResult::~CResult()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CResult::Init(void)
{
	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_RESULT_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CResult::Uninit(void)
{
	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CResult::Update(void)
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
		CManager::SetMode(MODE_TITLE);
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CResult::Draw(void)
{

}