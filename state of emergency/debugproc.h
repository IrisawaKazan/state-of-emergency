//==============================================================
//
// [debugproc.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _DEBUGPROC_H_ // このマクロ定義がされてなかったら
#define _DEBUGPROC_H_ // 2重インクルード防止のマクロ定義

#include"main.h"

// マクロ定義
#define MAX_CHARACTER (1024)

// デバッグクラス
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);
	static void Print(const char* fint, ...);
	static void Draw(void);

private:
	static LPD3DXFONT m_pFont;         // フォントへのポインタ
	static char m_aStr[MAX_CHARACTER]; // 文字列を格納するバッファ
};

#endif