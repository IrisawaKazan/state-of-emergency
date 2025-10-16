//==============================================================
//
// [input.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"input.h"

// �ÓI�����o�ϐ��錾
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CInput::CInput()
{
	m_pDevice = nullptr;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CInput::~CInput()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance)
{
	if (m_pInput == nullptr)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CInput::Uninit(void)
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire(); // �A�N�Z�X����j��
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//----------------------------------------
// �L�[�{�[�h�̃R���X�g���N�^
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
// �L�[�{�[�h�̃f�X�g���N�^
//----------------------------------------
CInputKeyboard::~CInputKeyboard()
{

}

//----------------------------------------
// �L�[�{�[�h�̏���������
//----------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	// �f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//----------------------------------------
// �L�[�{�[�h�̏I������
//----------------------------------------
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//----------------------------------------
// �L�[�{�[�h�̍X�V����
//----------------------------------------
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; // �L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
		{
			m_aKeyStateTrigger[nCount] = (m_aKeyStatePress[nCount] ^ aKeyState[nCount]) & aKeyState[nCount];
			m_aKeyStatePress[nCount] = aKeyState[nCount]; // �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//----------------------------------------
// �L�[�{�[�h�̃v���X���擾����
//----------------------------------------
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//----------------------------------------
// �L�[�{�[�h�̃g���K�[���擾����
//----------------------------------------
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//----------------------------------------
// �}�E�X�̃R���X�g���N�^
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
// �}�E�X�̃f�X�g���N�^
//----------------------------------------
CInputMouse::~CInputMouse()
{

}

//----------------------------------------
// �}�E�X�̏���������
//----------------------------------------
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	// �f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
	m_pDevice->Acquire();

	return S_OK;
}

//----------------------------------------
// �}�E�X�̏I������
//----------------------------------------
void CInputMouse::Uninit(void)
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire(); // �A�N�Z�X����j��
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//----------------------------------------
// �}�E�X�̍X�V����
//----------------------------------------
void CInputMouse::Update(void)
{
	m_OldMousepos = m_CurrentMouseState;

	// �ŐV�̃}�E�X����ۑ�����
	m_PrevMouseState = m_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
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
// �}�E�X�̃v���X���擾����
//----------------------------------------
bool CInputMouse::GetPress(MOUSE type)
{
	return (m_PrevMouseState.rgbButtons[type] & 0x80) ? true : false;
}

//----------------------------------------
// �}�E�X�̉����ꂽ����
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
// �}�E�X�̗����ꂽ����
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
// �W���C�p�b�h�̃R���X�g���N�^
//----------------------------------------
CInputJoypad::CInputJoypad()
{
	m_joykeyState = XINPUT_STATE();
	m_joykeyOldState = XINPUT_STATE();
}

//----------------------------------------
// �W���C�p�b�h�̃f�X�g���N�^
//----------------------------------------
CInputJoypad::~CInputJoypad()
{

}

//----------------------------------------
// �W���C�p�b�h�̏���������
//----------------------------------------
HRESULT CInputJoypad::Init(HINSTANCE hInstance)
{
	CInput::Init(hInstance);

	memset(&m_joykeyState, 0, sizeof(XINPUT_STATE));

	XInputEnable(true);

	return S_OK;
}

//----------------------------------------
// �W���C�p�b�h�̏I������
//----------------------------------------
void CInputJoypad::Uninit(void)
{
	CInput::Uninit();
}

//----------------------------------------
// �W���C�p�b�h�̍X�V����
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
// �W���C�p�b�h�̃v���X���擾����
//----------------------------------------
bool CInputJoypad::GetPress(JOYKEY key)
{
	return(m_joykeyState.Gamepad.wButtons & (0x01 << key));
}

//----------------------------------------
// �W���C�p�b�h�̃g���K�[���擾����
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