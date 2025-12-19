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
#include"title_arrow.h"

// 静的メンバ変数宣言


//----------------------------------------
// コンストラクタ
//----------------------------------------
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
	m_nEnterCnt = NULL;
	m_bEnter = false;
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
	CTitleObjX::Create(D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// タイトルアローの生成
	CTitleArrow::Create(D3DXVECTOR3(0.0f, 350.0f, -225.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_TITLE_RESULT_BGM);

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
				pSound->PlaySoundA(CSound::SOUND_LABEL_ARROW_SE);
			}
		}
		if (m_nEnterCnt >= 60 * 2)
		{
			CManager::SetMode(MODE_TUTORIAL);

			m_bEnter = false;

			m_nEnterCnt = 0;
		}
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTitle::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Title");
	CDebugProc::Draw();

#endif
}