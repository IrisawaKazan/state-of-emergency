//==============================================================
//
// [title.h]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
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
#include"titleOBJ.h"

// 静的メンバ変数宣言


//----------------------------------------
// コンストラクタ
//----------------------------------------
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{

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
	// タイトルオブジェクトの生成
	CTitleObjX::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_BGM);

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