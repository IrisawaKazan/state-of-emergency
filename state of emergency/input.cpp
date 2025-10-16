//==============================================================
//
// [input.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"input.h"

// 静的メンバ変数宣言
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CInput::CInput()
{
	m_pDevice = nullptr;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CInput::~CInput()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance)
{
	if (m_pInput == nullptr)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CInput::Uninit(void)
{
	// 入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire(); // アクセス権を破棄
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//----------------------------------------
// キーボードのコンストラクタ
//----------------------------------------
CInputKeyboard::CInputKeyboard()
{
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyStatePress[nCount] = NULL;
		m_aKeyStateTrigger[nCount] = NULL;
	}
}

//----------------------------------------
// キーボードのデストラクタ
//----------------------------------------
CInputKeyboard::~CInputKeyboard()
{

}

//----------------------------------------
// キーボードの初期化処理
//----------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	// デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//----------------------------------------
// キーボードの終了処理
//----------------------------------------
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//----------------------------------------
// キーボードの更新処理
//----------------------------------------
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; // キーボードの入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
		{
			m_aKeyStateTrigger[nCount] = (m_aKeyStatePress[nCount] ^ aKeyState[nCount]) & aKeyState[nCount];
			m_aKeyStatePress[nCount] = aKeyState[nCount]; // キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); // キーボードへのアクセス権を獲得
	}
}

//----------------------------------------
// キーボードのプレス情報取得処理
//----------------------------------------
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//----------------------------------------
// キーボードのトリガー情報取得処理
//----------------------------------------
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//----------------------------------------
// マウスのコンストラクタ
//----------------------------------------
CInputMouse::CInputMouse()
{
	m_MauseState = NULL;
	m_OldMauseState = NULL;
	m_CurrentMouseState = DIMOUSESTATE();
	m_PrevMouseState = DIMOUSESTATE();
	m_OldMousepos = DIMOUSESTATE();
}

//----------------------------------------
// マウスのデストラクタ
//----------------------------------------
CInputMouse::~CInputMouse()
{

}

//----------------------------------------
// マウスの初期化処理
//----------------------------------------
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	// デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を取得
	m_pDevice->Acquire();

	return S_OK;
}

//----------------------------------------
// マウスの終了処理
//----------------------------------------
void CInputMouse::Uninit(void)
{
	// 入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire(); // アクセス権を破棄
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//----------------------------------------
// マウスの更新処理
//----------------------------------------
void CInputMouse::Update(void)
{
	m_OldMousepos = m_CurrentMouseState;

	// 最新のマウス情報を保存する
	m_PrevMouseState = m_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hresult = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	if (FAILED(hresult))
	{
		m_pDevice->Acquire();
		hresult = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);
	}

	POINT point;

	GetCursorPos(&point);

	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &point);

	m_CurrentMouseState.lX = point.x;
	m_CurrentMouseState.lY = point.y;
}

//----------------------------------------
// マウスのプレス情報取得処理
//----------------------------------------
bool CInputMouse::GetPress(MOUSE type)
{
	return (m_PrevMouseState.rgbButtons[type] & 0x80) ? true : false;
}

//----------------------------------------
// マウスの押された処理
//----------------------------------------
bool CInputMouse::GetTrigger(MOUSE type)
{
	if (!(m_PrevMouseState.rgbButtons[type] & (0x80)) &&
		m_CurrentMouseState.rgbButtons[type] & (0x80))
	{
		return true;
	}

	return false;
}

//----------------------------------------
// マウスの離された処理
//----------------------------------------
bool CInputMouse::GetRelease(MOUSE type)
{
	if (m_PrevMouseState.rgbButtons[type] & 0x80 &&
		!(m_CurrentMouseState.rgbButtons[type] & 0x80))
	{
		return true;
	}

	return false;
}

//----------------------------------------
// 
//----------------------------------------
D3DXVECTOR2 CInputMouse::GetVelocity()
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

//----------------------------------------
// 
//----------------------------------------
D3DXVECTOR2 CInputMouse::GetVelocityOld()
{
	return D3DXVECTOR2((float)m_OldMousepos.lX, (float)m_OldMousepos.lY);
}

//----------------------------------------
// ジョイパッドのコンストラクタ
//----------------------------------------
CInputJoypad::CInputJoypad()
{
	m_joykeyState = XINPUT_STATE();
	m_joykeyOldState = XINPUT_STATE();
}

//----------------------------------------
// ジョイパッドのデストラクタ
//----------------------------------------
CInputJoypad::~CInputJoypad()
{

}

//----------------------------------------
// ジョイパッドの初期化処理
//----------------------------------------
HRESULT CInputJoypad::Init(HINSTANCE hInstance)
{
	CInput::Init(hInstance);

	memset(&m_joykeyState, 0, sizeof(XINPUT_STATE));

	XInputEnable(true);

	return S_OK;
}

//----------------------------------------
// ジョイパッドの終了処理
//----------------------------------------
void CInputJoypad::Uninit(void)
{
	CInput::Uninit();
}

//----------------------------------------
// ジョイパッドの更新処理
//----------------------------------------
void CInputJoypad::Update(void)
{
	XINPUT_STATE joypadState;

	int nCntJoy;

	for (nCntJoy = 0; nCntJoy < NUM_KEY_MAX; nCntJoy++)
	{
		m_joykeyOldState = m_joykeyState;
	}

	if (XInputGetState(0, &joypadState) == ERROR_SUCCESS)
	{
		m_joykeyState = joypadState;
	}
}

//----------------------------------------
// ジョイパッドのプレス情報取得処理
//----------------------------------------
bool CInputJoypad::GetPress(JOYKEY key)
{
	return(m_joykeyState.Gamepad.wButtons & (0x01 << key));
}

//----------------------------------------
// ジョイパッドのトリガー情報取得処理
//----------------------------------------
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	bool bUse = false;

	if (m_joykeyState.Gamepad.wButtons & (0x01 << key) && !(m_joykeyOldState.Gamepad.wButtons & (0x01 << key)))
	{
		bUse = true;
	}

	return bUse;
}

//----------------------------------------
// 
//----------------------------------------
D3DXVECTOR2 GetVelocityOld()
{
	return D3DXVECTOR2();
}