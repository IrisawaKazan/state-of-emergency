//==============================================================
//
// [debugproc.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"debugproc.h"
#include"manager.h"
#include"renderer.h"

// 静的メンバ変数宣言
LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_aStr[MAX_CHARACTER] = {};

//----------------------------------------
// コンストラクタ
//----------------------------------------
CDebugProc::CDebugProc()
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CDebugProc::~CDebugProc()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
void CDebugProc::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバッグ表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &m_pFont);
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CDebugProc::Uninit(void)
{
	// デバッグ表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//----------------------------------------
// printf
//----------------------------------------
void CDebugProc::Print(const char* fint, ...)
{
	va_list args; // va_listマクロを使用

	va_start(args, fint);

	vsprintf_s(m_aStr, fint, args); // vsprintfを使用する場合は #define _CRT_SECURE_WARNINGS

	va_end(args);
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CDebugProc::Draw(void)
{
	RECT rect = { 5 /* X座標の位置 */,5 /* Y座標の位置 */,SCREEN_WIDTH,SCREEN_HEIGHT };

	m_pFont->DrawTextA(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 255, 255));
}