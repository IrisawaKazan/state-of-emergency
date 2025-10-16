//==============================================================
//
// [main.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"renderer.h"
#include"object.h"
#include"object2D.h"
#include"manager.h"
#include"input.h"

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void FullScreen(HWND hWnd);

// グローバル変数宣言
int g_nCntFPS = NULL;
bool g_bFullscreen = false;
RECT g_windowRect = {};

//----------------------------------------
// メイン関数
//----------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	hinstancePrev = nullptr;
	lpCmdLine = nullptr;

	CManager* pManager = nullptr;

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),             // WINDCLASSEXのメモリサイズ
		CS_CLASSDC,                     // ウィンドウのスタイル
		WindowProc,                     // ウィンドウプロシージャ
		0,                              // 0にする(通常は使用しない)
		0,                              // 0にする(通常は使用しない)
		hInstance,                      // インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), // タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),     // マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;                                      // ウィンドウハンドル
	MSG msg;                                        // メッセージを格納する変数
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; // 画面サイズの構造体

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left), // ウィンドウの幅
		(rect.bottom - rect.top), // ウィンドウの高さ
		NULL,
		NULL,
		hInstance,
		NULL);

	// マネージャの生成
	pManager = new CManager;

	// マネージャの初期化処理
	pManager->Init(hInstance, hWnd);

	// 分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow); // ウィンドウの表示状態を設定
	UpdateWindow(hWnd);         // クライアント領域を更新

	DWORD dwFrameCount;  // フレームカウント
	DWORD dwFPSLastTime; // 最後にFPSを計測した時刻

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg); // 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  // ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();

			if (dwCurrentTime - dwFPSLastTime >= 500)
			{// 0.5秒経過
				// FPSを計測
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime; // FPSを測定した時刻を保存
				dwFrameCount = 0;              // フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// マネージャの更新処理
				pManager->Update();

				// マネージャの描画処理
				pManager->Draw();

				dwFrameCount++; // フレームカウントを加算
			}
		}
	}

	// レンダラーの破棄
	if (pManager != nullptr)
	{
		// 終了処理
		pManager->Uninit();

		delete pManager;

		pManager = nullptr;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//----------------------------------------
// ウィンドウプロシージャ
//----------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int nID = NULL;

	switch (uMsg)
	{
	case WM_ACTIVATE:
		return 0L;

	case WM_DESTROY:
		// WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか ?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd); // ウィンドウ破棄メッセージ
			}
			else
			{
				return 0;
			}
			break;

		case VK_F11:
			FullScreen(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------------------------
// フルスクリーン処理
//----------------------------------------
void FullScreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_bFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top, g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top, SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_bFullscreen = !g_bFullscreen;
}

//----------------------------------------
// FPSの取得処理
//----------------------------------------
int GetFPS(void)
{
	return g_nCntFPS;
}