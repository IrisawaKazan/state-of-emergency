//==============================================================
//
// [input.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _INPUT_H_ // このマクロ定義がされてなかったら
#define _INPUT_H_ // 2重インクルード防止のマクロ定義

#include"main.h"

// マクロ定義
#define NUM_KEY_MAX (256) // キーの最大数

// 入力クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

private:

};

// キーボードクラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

// マウスクラス
class CInputMouse : public CInput
{
public:
	// マウスの種類
	typedef enum
	{
		MOUSE_LEFTBUTTON = 0, // 左クリック
		MOUSE_RIGHTBUTTON,    // 右クリック
		MOUSE_WHEELBUTTON,    // ホイール

		MOUSE_MAX
	}MOUSE;

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(MOUSE type);
	bool GetTrigger(MOUSE type);
	bool GetRelease(MOUSE type);

	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetVelocityOld();

private:
	BYTE m_MauseState;
	BYTE m_OldMauseState;
	DIMOUSESTATE m_CurrentMouseState;
	DIMOUSESTATE m_PrevMouseState;
	DIMOUSESTATE m_OldMousepos;
};

// ジョイパッドクラス
class CInputJoypad : public CInput
{
public:
	typedef enum
	{
		JOYKEY_UP = 0,        // 十字キー(上)
		JOYKEY_DOWN,          // 十字キー(下)
		JOYKEY_LEFT,          // 十字キー(左)
		JOYKEY_RIGHT,         // 十字キー(右)
		JOYKEY_START,         // スタートキー
		JOYKEY_BACK,          // バックキー
		JOYKEY_LS,            // Lスティック押し込み
		JOYKEY_RS,            // Rスティック押し込み
		JOYKEY_LEFT_B,        // LBキー
		JOYKEY_RIGHT_B,       // RBキー
		JOYKEY_LEFT_TRIGGER,  // LTキー
		JOYKEY_RIGHT_TRIGGER, // RTキー
		JOYKEY_A,             // Aボタン
		JOYKEY_B,             // Bボタン
		JOYKEY_X,             // Xボタン
		JOYKEY_Y,             // Yボタン

		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);

	bool GetPress(JOYKEY key);
	bool GetTrigger(JOYKEY key);

private:
	XINPUT_STATE m_joykeyState;
	XINPUT_STATE m_joykeyOldState;
};

#endif