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

// �ÓI�����o�ϐ��錾
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
// �R���X�g���N�^
//----------------------------------------
CManager::CManager()
{

}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CManager::~CManager()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CManager::Init(HINSTANCE nInstance, HWND hWnd)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;

	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(nInstance, hWnd)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// �}�E�X�̐���
	m_pInputMouse = new CInputMouse;

	// �}�E�X�̏���������
	if (FAILED(m_pInputMouse->Init(nInstance, hWnd)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// �p�b�h�̐���
	m_pInputJoypad = new CInputJoypad;

	// �p�b�h�̏���������
	if (FAILED(m_pInputJoypad->Init(nInstance)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// �T�E���h�̐���
	m_pSound = new CSound;

	// �T�E���h�̏���������
	m_pSound->Init(hWnd);

	// �J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	// �f�o�b�O�̐���
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	// �G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
	CEffect::Load();

	// �X�R�A�̃e�N�X�`���̓ǂݍ���
	CScore::Load();

	// �^�C�}�[�̃e�N�X�`���̓ǂݍ���
	CTimer::Load();

	// �|�[�Y�̃e�N�X�`���̓ǂݍ���
	CPause::Load();

	SetMode(CScene::MODE_GAME);

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::Unload();

	// �X�R�A�̃e�N�X�`���̔j��
	CScore::Unload();

	// �^�C�}�[�̃e�N�X�`���̔j��
	CTimer::Unload();

	// �|�[�Y�̃e�N�X�`���̔j��
	CPause::Unload();

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = nullptr;
	}

	// �}�E�X�̔j��
	if (m_pInputMouse != nullptr)
	{
		// �I������
		m_pInputMouse->Uninit();

		delete m_pInputMouse;

		m_pInputMouse = nullptr;
	}

	// �p�b�h�̔j��
	if (m_pInputJoypad != nullptr)
	{
		// �I������
		m_pInputJoypad->Uninit();

		delete m_pInputJoypad;

		m_pInputJoypad = nullptr;
	}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = nullptr;
	}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		// �I������
		m_pSound->Uninit();

		delete m_pSound;

		m_pSound = nullptr;
	}

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		// �I������
		m_pCamera->Uninit();

		delete m_pCamera;

		m_pCamera = nullptr;
	}

	// ���C�g�̔j��
	if (m_pLight != nullptr)
	{
		// �I������
		m_pLight->Uninit();

		delete m_pLight;

		m_pLight = nullptr;
	}

	// �f�o�b�O�̔j��
	if (m_pDebugProc != nullptr)
	{
		// �I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;

		m_pDebugProc = nullptr;
	}
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CManager::Update(void)
{
	// �����_���[�̎擾
	m_pRenderer->Update();

	// �L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	// �}�E�X�̍X�V����
	m_pInputMouse->Update();

	// �p�b�h�̍X�V����
	m_pInputJoypad->Update();

	// �p�b�h�̃o�b�N�L�[�ŃE�B���h�E�I��
	if (m_pInputJoypad->GetTrigger(m_pInputJoypad->JOYKEY_BACK) == true)
	{
		// �E�B���h�E�����
		PostQuitMessage(0);
	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//----------------------------------------
// �����_���[�̎擾����
//----------------------------------------
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//----------------------------------------
// �L�[�{�[�h�̎擾����
//----------------------------------------
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//----------------------------------------
// �}�E�X�̎擾����
//----------------------------------------
CInputMouse* CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//----------------------------------------
// �p�b�h�̎擾����
//----------------------------------------
CInputJoypad* CManager::GetInputJoypad(void)
{
	return m_pInputJoypad;
}

//----------------------------------------
// �J�����̎擾����
//----------------------------------------
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

//----------------------------------------
// ���C�g�̎擾����
//----------------------------------------
CLight* CManager::GetLight(void)
{
	return m_pLight;
}

//----------------------------------------
// �f�o�b�O�̎擾����
//----------------------------------------
CDebugProc* CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//----------------------------------------
// �T�E���h�̎擾����
//----------------------------------------
CSound* CManager::GetSound(void)
{
	return m_pSound;
}

//----------------------------------------
// �X�R�A�̎擾����
//----------------------------------------
CScore* CManager::GetScore(void)
{
	return m_pScore;
}

//----------------------------------------
// �^�C�}�[�̎擾����
//----------------------------------------
CTimer* CManager::GetTimer(void)
{
	return m_pTimer;
}

//----------------------------------------
// �u�[�X�gUI�̎擾����
//----------------------------------------
CBoost* CManager::GetBoost(void)
{
	return m_pBoost;
}

//----------------------------------------
// �G�t�F�N�g�̎擾����
//----------------------------------------
CEffect* CManager::GetEffect(void)
{
	return m_pEffect;
}

//----------------------------------------
// �|�[�Y�̎擾����
//----------------------------------------
CPause* CManager::GetPause(void)
{
	return m_pPause;
}

//----------------------------------------
// ���[�h�̐ݒ菈��
//----------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pSound != nullptr)
	{
		// �T�E���h�̒�~
		m_pSound->Stop();
	}

	//// �t�F�[�h�̔j��
	//if (m_pFade != nullptr)
	//{
	//	m_pFade->Uninit();
	//}

	if (m_pScene != nullptr)
	{
		// ���݂̃��[�h�̔j��
		m_pScene->Uninit();
	}

	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);

	// �t�F�[�h�̐���

}

//----------------------------------------
// ���[�h�̎擾����
//----------------------------------------
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//----------------------------------------
// �V�[���̎擾����
//----------------------------------------
CScene* CManager::GetScene(void)
{
	return m_pScene;
}

////----------------------------------------
//// �t�F�[�h�̎擾����
////----------------------------------------
//CFade* CManager::GetFade(void)
//{
//	return m_pFade;
//}

//----------------------------------------
// �V�[���̃R���X�g���N�^
//----------------------------------------
CScene::CScene(MODE mode)
{
	m_mode = mode;
}

//----------------------------------------
// �V�[���̃f�X�g���N�^
//----------------------------------------
CScene::~CScene()
{

}

//----------------------------------------
// �V�[���̐�������
//----------------------------------------
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:    // �^�C�g�����
		pScene = new CTitle;
		//pScene->Init();
		break;

	case MODE_GAME:     // �Q�[�����
		pScene = new CGame;
		//pScene->Init();
		break;

	case MODE_TUTORIAL: // �`���[�g���A�����
		pScene = new CTutorial;
		//pScene->Init();
		break;

	case MODE_RESULT:   // ���U���g���
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
// �V�[���̏���������
//----------------------------------------
HRESULT CScene::Init(void)
{


	return S_OK;
}

//----------------------------------------
// �V�[���̏I������
//----------------------------------------
void CScene::Uninit(void)
{
}

//----------------------------------------
// �V�[���̍X�V����
//----------------------------------------
void CScene::Update(void)
{
}

//----------------------------------------
// �V�[���̕`�揈��
//----------------------------------------
void CScene::Draw(void)
{
}

//----------------------------------------
// �������z�֐��̂���
//----------------------------------------
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------------
// �������z�֐��̂���
//----------------------------------------
D3DXVECTOR3 CScene::GetPos(void)
{
	return D3DXVECTOR3();
}

//----------------------------------------
// �V�[���̎擾����
//----------------------------------------
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}