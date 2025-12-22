//==============================================================
//
// [result.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"result.h"
#include"input.h"
#include"sound.h"
#include"debugproc.h"
#include"resultOBJ.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CResult::CResult() : CScene(CScene::MODE_RESULT)
{
	m_nEnterCnt = NULL;
	m_bEnter = false;
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
	// リザルトオブジェクトの生成
	CResultObjX::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// サウンドの取得
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_TITLE_RESULT_BGM);

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
			if (m_nEnterCnt == 60 * 0 + 10)
			{
				// ---の生成
				//CResultObjX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); // テスト
			}
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
void CResult::Draw(void)
{
#ifdef _DEBUG // Debug時のみ

	// 現在のモードをデバッグ表示
	CDebugProc::Print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nScene: Result");
	CDebugProc::Draw();

#endif
}