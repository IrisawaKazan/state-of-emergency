//==============================================================
//
// [title.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"title.h"
#include"object2D.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"light.h"
#include"object3D.h"
#include"timer.h"
#include"objectX.h"
#include"objectBillboard.h"
#include"debugproc.h"
#include"effect.h"
#include"pause.h"
#include"game.h"

// �ÓI�����o�ϐ��錾
//CObjectX* CTitle::m_pObjectX = nullptr;

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
{
	m_nPlay = NULL;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_nCounter[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER_F; nCnt++)
	{
		m_nFrameCounter[nCnt] = NULL;
	}

	m_nSpawnFloating = NULL;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CTitle::~CTitle()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CTitle::Init(void)
{
	// �T�E���h�̎擾
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_TITLE_BGM);

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CTitle::Uninit(void)
{
	CObject::Release();
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CTitle::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �}�E�X�̎擾
	CInputMouse* pInputMouse;
	pInputMouse = CManager::GetInputMouse();

	// �p�b�h�̎擾
	CInputJoypad* pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// �T�E���h�̎擾
	CSound* pSound = CManager::GetSound();

	// �����_���Đ�
	m_nPlay++;

	// ���i�ŏo�Ȃ��悤�ɐ�������J�E���^�[
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_nCounter[nCnt]++;
	}

	// ���݂̎�������Ƃ��Đݒ�
	srand((unsigned int)time(nullptr));

	// �m�C�Y
	if (m_nPlay >= rand() / 20 && m_nCounter[0] >= NUM_SEPLAY_FRAME_CNT)
	{
		pSound->PlaySoundA(CSound::SOUND_LABEL_NOISE_SE);

		m_nPlay = 0;
		m_nCounter[0] = 0;
	}

	// �M��
	if (m_nPlay >= rand() / 20 && m_nCounter[1] >= NUM_SEPLAY_FRAME_CNT + 60 * 10)
	{
		pSound->PlaySoundA(CSound::SOUND_LABEL_MORSE_SE);

		m_nPlay = 0;
		m_nCounter[1] = 0;
	}

	m_nSpawnFloating++;

	float fPosX = (float)(rand() % 500/* �o�Ă���͈� */);

	// ���݂̎�������Ƃ��Đݒ�
	srand((unsigned int)time(nullptr));

	// ���i�ŏo�Ȃ��悤�ɐ�������J�E���^�[
	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER_F; nCnt++)
	{
		m_nFrameCounter[nCnt]++;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON) == true == true)
	{// ����L�[(ENTER�L�[)�������ꂽ
		CManager::SetMode(MODE_TUTORIAL);
	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CTitle::Draw(void)
{

}