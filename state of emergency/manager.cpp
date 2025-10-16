//==============================================================
//
// [manager.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"manager.h"
#include"game.h"
#include"title.h"
#include"tutorial.h"
#include"result.h"
#include"object2D.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"light.h"
#include"object3D.h"
#include"timer.h"
#include"objectBillboard.h"
#include"debugproc.h"
#include"effect.h"
#include"pause.h"

// 静的メンバ変数宣言
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;
CInputMouse* CManager::m_pInputMouse = nullptr;
CInputJoypad* CManager::m_pInputJoypad = nullptr;
CSound* CManager::m_pSound = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CDebugProc* CManager::m_pDebugProc = nullptr;

CScore* CManager::m_pScore = nullptr;
CTimer* CManager::m_pTimer = nullptr;
CBoost* CManager::m_pBoost = nullptr;
CEffect* CManager::m_pEffect = nullptr;
CPause* CManager::m_pPause = nullptr;

CScene* CManager::m_pScene = nullptr;

//CFade* CManager::m_pFade = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CManager::CManager()
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CManager::~CManager()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CManager::Init(HINSTANCE nInstance, HWND hWnd)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;

	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;

	// キーボードの初期化処理
	if (FAILED(m_pInputKeyboard->Init(nInstance, hWnd)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// マウスの生成
	m_pInputMouse = new CInputMouse;

	// マウスの初期化処理
	if (FAILED(m_pInputMouse->Init(nInstance, hWnd)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// パッドの生成
	m_pInputJoypad = new CInputJoypad;

	// パッドの初期化処理
	if (FAILED(m_pInputJoypad->Init(nInstance)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// サウンドの生成
	m_pSound = new CSound;

	// サウンドの初期化処理
	m_pSound->Init(hWnd);

	// カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	// デバッグの生成
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	// エフェクトのテクスチャの読み込み
	CEffect::Load();

	// スコアのテクスチャの読み込み
	CScore::Load();

	// タイマーのテクスチャの読み込み
	CTimer::Load();

	// ポーズのテクスチャの読み込み
	CPause::Load();

	SetMode(CScene::MODE_GAME);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CManager::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();

	// エフェクトのテクスチャの破棄
	CEffect::Unload();

	// スコアのテクスチャの破棄
	CScore::Unload();

	// タイマーのテクスチャの破棄
	CTimer::Unload();

	// ポーズのテクスチャの破棄
	CPause::Unload();

	// キーボードの破棄
	if (m_pInputKeyboard != nullptr)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = nullptr;
	}

	// マウスの破棄
	if (m_pInputMouse != nullptr)
	{
		// 終了処理
		m_pInputMouse->Uninit();

		delete m_pInputMouse;

		m_pInputMouse = nullptr;
	}

	// パッドの破棄
	if (m_pInputJoypad != nullptr)
	{
		// 終了処理
		m_pInputJoypad->Uninit();

		delete m_pInputJoypad;

		m_pInputJoypad = nullptr;
	}

	// レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		// 終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = nullptr;
	}

	// サウンドの破棄
	if (m_pSound != nullptr)
	{
		// 終了処理
		m_pSound->Uninit();

		delete m_pSound;

		m_pSound = nullptr;
	}

	// カメラの破棄
	if (m_pCamera != nullptr)
	{
		// 終了処理
		m_pCamera->Uninit();

		delete m_pCamera;

		m_pCamera = nullptr;
	}

	// ライトの破棄
	if (m_pLight != nullptr)
	{
		// 終了処理
		m_pLight->Uninit();

		delete m_pLight;

		m_pLight = nullptr;
	}

	// デバッグの破棄
	if (m_pDebugProc != nullptr)
	{
		// 終了処理
		m_pDebugProc->Uninit();

		delete m_pDebugProc;

		m_pDebugProc = nullptr;
	}
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CManager::Update(void)
{
	// レンダラーの取得
	m_pRenderer->Update();

	// キーボードの更新処理
	m_pInputKeyboard->Update();

	// マウスの更新処理
	m_pInputMouse->Update();

	// パッドの更新処理
	m_pInputJoypad->Update();

	// パッドのバックキーでウィンドウ終了
	if (m_pInputJoypad->GetTrigger(m_pInputJoypad->JOYKEY_BACK) == true)
	{
		// ウィンドウを閉じる
		PostQuitMessage(0);
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//----------------------------------------
// レンダラーの取得処理
//----------------------------------------
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//----------------------------------------
// キーボードの取得処理
//----------------------------------------
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//----------------------------------------
// マウスの取得処理
//----------------------------------------
CInputMouse* CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//----------------------------------------
// パッドの取得処理
//----------------------------------------
CInputJoypad* CManager::GetInputJoypad(void)
{
	return m_pInputJoypad;
}

//----------------------------------------
// カメラの取得処理
//----------------------------------------
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

//----------------------------------------
// ライトの取得処理
//----------------------------------------
CLight* CManager::GetLight(void)
{
	return m_pLight;
}

//----------------------------------------
// デバッグの取得処理
//----------------------------------------
CDebugProc* CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//----------------------------------------
// サウンドの取得処理
//----------------------------------------
CSound* CManager::GetSound(void)
{
	return m_pSound;
}

//----------------------------------------
// スコアの取得処理
//----------------------------------------
CScore* CManager::GetScore(void)
{
	return m_pScore;
}

//----------------------------------------
// タイマーの取得処理
//----------------------------------------
CTimer* CManager::GetTimer(void)
{
	return m_pTimer;
}

//----------------------------------------
// ブーストUIの取得処理
//----------------------------------------
CBoost* CManager::GetBoost(void)
{
	return m_pBoost;
}

//----------------------------------------
// エフェクトの取得処理
//----------------------------------------
CEffect* CManager::GetEffect(void)
{
	return m_pEffect;
}

//----------------------------------------
// ポーズの取得処理
//----------------------------------------
CPause* CManager::GetPause(void)
{
	return m_pPause;
}

//----------------------------------------
// モードの設定処理
//----------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pSound != nullptr)
	{
		// サウンドの停止
		m_pSound->Stop();
	}

	//// フェードの破棄
	//if (m_pFade != nullptr)
	//{
	//	m_pFade->Uninit();
	//}

	if (m_pScene != nullptr)
	{
		// 現在のモードの破棄
		m_pScene->Uninit();
	}

	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();

	// 新しいモードの生成
	m_pScene = CScene::Create(mode);

	// フェードの生成

}

//----------------------------------------
// モードの取得処理
//----------------------------------------
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//----------------------------------------
// シーンの取得処理
//----------------------------------------
CScene* CManager::GetScene(void)
{
	return m_pScene;
}

////----------------------------------------
//// フェードの取得処理
////----------------------------------------
//CFade* CManager::GetFade(void)
//{
//	return m_pFade;
//}

//----------------------------------------
// シーンのコンストラクタ
//----------------------------------------
CScene::CScene(MODE mode)
{
	m_mode = mode;
}

//----------------------------------------
// シーンのデストラクタ
//----------------------------------------
CScene::~CScene()
{

}

//----------------------------------------
// シーンの生成処理
//----------------------------------------
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:    // タイトル画面
		pScene = new CTitle;
		//pScene->Init();
		break;

	case MODE_GAME:     // ゲーム画面
		pScene = new CGame;
		//pScene->Init();
		break;

	case MODE_TUTORIAL: // チュートリアル画面
		pScene = new CTutorial;
		//pScene->Init();
		break;

	case MODE_RESULT:   // リザルト画面
		pScene = new CResult;

		break;
	}

	pScene->Init();

	if (pScene != nullptr)
	{
		return pScene;
	}
	else
	{
		return nullptr;
	}
}

//----------------------------------------
// シーンの初期化処理
//----------------------------------------
HRESULT CScene::Init(void)
{


	return S_OK;
}

//----------------------------------------
// シーンの終了処理
//----------------------------------------
void CScene::Uninit(void)
{
}

//----------------------------------------
// シーンの更新処理
//----------------------------------------
void CScene::Update(void)
{
}

//----------------------------------------
// シーンの描画処理
//----------------------------------------
void CScene::Draw(void)
{
}

//----------------------------------------
// 純粋仮想関数のため
//----------------------------------------
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------------
// 純粋仮想関数のため
//----------------------------------------
D3DXVECTOR3 CScene::GetPos(void)
{
	return D3DXVECTOR3();
}

//----------------------------------------
// シーンの取得処理
//----------------------------------------
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}