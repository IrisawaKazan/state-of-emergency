//==============================================================
//
// [input.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _INPUT_H_ // ���̃}�N����`������ĂȂ�������
#define _INPUT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �}�N����`
#define NUM_KEY_MAX (256) // �L�[�̍ő吔

// ���̓N���X
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

// �L�[�{�[�h�N���X
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

// �}�E�X�N���X
class CInputMouse : public CInput
{
public:
	// �}�E�X�̎��
	typedef enum
	{
		MOUSE_LEFTBUTTON = 0, // ���N���b�N
		MOUSE_RIGHTBUTTON,    // �E�N���b�N
		MOUSE_WHEELBUTTON,    // �z�C�[��

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

// �W���C�p�b�h�N���X
class CInputJoypad : public CInput
{
public:
	typedef enum
	{
		JOYKEY_UP = 0,        // �\���L�[(��)
		JOYKEY_DOWN,          // �\���L�[(��)
		JOYKEY_LEFT,          // �\���L�[(��)
		JOYKEY_RIGHT,         // �\���L�[(�E)
		JOYKEY_START,         // �X�^�[�g�L�[
		JOYKEY_BACK,          // �o�b�N�L�[
		JOYKEY_LS,            // L�X�e�B�b�N��������
		JOYKEY_RS,            // R�X�e�B�b�N��������
		JOYKEY_LEFT_B,        // LB�L�[
		JOYKEY_RIGHT_B,       // RB�L�[
		JOYKEY_LEFT_TRIGGER,  // LT�L�[
		JOYKEY_RIGHT_TRIGGER, // RT�L�[
		JOYKEY_A,             // A�{�^��
		JOYKEY_B,             // B�{�^��
		JOYKEY_X,             // X�{�^��
		JOYKEY_Y,             // Y�{�^��

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