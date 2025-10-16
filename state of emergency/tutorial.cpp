//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"tutorial.h"
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

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{

}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CTutorial::~CTutorial()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CTutorial::Init(void)
{
	// �T�E���h�̎擾
	CSound* pSound = CManager::GetSound();

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_BGM);

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CTutorial::Uninit(void)
{
	CObject::Release();
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CTutorial::Update(void)
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

	//// �T�E���h�̎擾
	//CSound* pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) || pInputMouse->GetTrigger(pInputMouse->MOUSE_LEFTBUTTON) == true)
	{// ����L�[(ENTER�L�[)�������ꂽ
		CManager::SetMode(MODE_GAME);
	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CTutorial::Draw(void)
{

}