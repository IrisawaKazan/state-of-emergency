//==============================================================
//
// [timeover.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"timeover.h"
#include"input.h"
#include"sound.h"
#include"debugproc.h"
#include"timeoverOBJ.h"
#include"oshirase.h"
#include"mpn.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTimeover::CTimeover() : CScene(CScene::MODE_TIMEOVER)
{
	m_nEnterCnt = NULL;
	m_bEnter = false;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTimeover::~CTimeover()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTimeover::Init(void)
{
	// タイムオーバーOBJの生成
	CTimeoverObj::Create(D3DXVECTOR3(NUM_TIMEOVER_POS_X, NUM_TIMEOVER_POS_Y, NUM_TIMEOVER_POS_Z), D3DXVECTOR3(NUM_TIMEOVER_ROT_X, NUM_TIMEOVER_ROT_Y, NUM_TIMEOVER_ROT_Z));

	// お知らせの生成
	COshirase::Create(D3DXVECTOR3(NUM_TIMEOVER_POS_X, NUM_TIMEOVER_POS_Y, NUM_TIMEOVER_POS_Z), D3DXVECTOR3(NUM_TIMEOVER_ROT_X, NUM_TIMEOVER_ROT_Y, NUM_TIMEOVER_ROT_Z));

	// MPNの生成
	CMpn::Create(D3DXVECTOR3(NUM_TIMEOVER_POS_X, NUM_TIMEOVER_POS_Y, NUM_TIMEOVER_POS_Z), D3DXVECTOR3(NUM_TIMEOVER_ROT_X, NUM_TIMEOVER_ROT_Y, NUM_TIMEOVER_ROT_Z));

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_GAMEOVER_BGM);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CTimeover::Uninit(void)
{
	CObject::Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CTimeover::Update(void)
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
void CTimeover::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Time Over");
	CDebugProc::Draw();

#endif
}