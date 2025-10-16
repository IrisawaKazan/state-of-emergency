//==============================================================
//
// [game.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"game.h"
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

// �ÓI�����o�ϐ��錾
CObjectX* CGame::m_pObjectX = nullptr;
CPause* CGame::m_pPause = nullptr;

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	m_bPause = false;
	m_nSpawn = NULL;

	for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
	{
		m_nFrameCounter[nCnt] = NULL;
	}

	m_nScrapCounter = NULL;
	m_nSmallThingsCounter = NULL;
	m_nBlackThingsCounter = NULL;

	m_nSmallThingsSpawn = NULL;

	m_nTransition = NULL;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CGame::~CGame()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CGame::Init(void)
{
	// �G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
	CEffect::Load();

	// �X�R�A�̃e�N�X�`���̓ǂݍ���
	CScore::Load();

	// �^�C�}�[�̃e�N�X�`���̓ǂݍ���
	CTimer::Load();

	// �|�[�Y�̃e�N�X�`���̓ǂݍ���
	CPause::Load();

	// �T�E���h�̎擾
	CSound* pSound = CManager::GetSound();

	// �I�u�W�F�N�gX�̐���(�����z�u)
	m_pObjectX = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �X�R�A
	CScore::Create(D3DXVECTOR3(1100.0f, 50.0f, 0.0f), 30.0f, 90.0f);

#ifdef _DEBUG // Debug���̂�

	// �^�C�}�[
	CTimer::Create(D3DXVECTOR3(50.0f, 675.0f, 0.0f), 30.0f, 90.0f);

#endif

	// BGM
	pSound->PlaySoundA(CSound::SOUND_LABEL_GAME_BGM);

	m_bPause = false; // �|�[�Y����

	m_nTransition = 0;

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CGame::Uninit(void)
{
	// �G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::Unload();

	// �X�R�A�̃e�N�X�`���̔j��
	CScore::Unload();

	// �^�C�}�[�̃e�N�X�`���̔j��
	CTimer::Unload();

	// �|�[�Y�̃e�N�X�`���̔j��
	CPause::Unload();

	CObject::Release();

	//// �v���C���[�̔j��
	//if (m_pObjectX != nullptr)
	//{
	//	m_pObjectX = nullptr;
	//}
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CGame::Update(void)
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

	//if (pInputKeyboard->GetTrigger(DIK_TAB) || pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_B) == true)
	//{// �v���C���[�������Ă��鎞�Ƀ|�[�Y�L�[�������ꂽ
	//	m_bPause = m_bPause ? false : true;
	//}

	//if (m_bPause == true)
	{// �|�[�Y��
		//m_pPause = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

		//m_pPause->Update();

		//m_pPause->Draw();
	}

	//if (m_bPause == false)
	{// �|�[�Y���łȂ����
		// �����_������
		m_nSpawn++;
		m_nSmallThingsSpawn++;

		float fPosZ = (float)(rand() % 130/* �o�Ă���͈� */);

		// ���݂̎�������Ƃ��Đݒ�
		srand((unsigned int)time(nullptr));

		// ���i�ŏo�Ȃ��悤�ɐ�������J�E���^�[
		for (int nCnt = 0; nCnt < MAX_FRAMECOUNTER; nCnt++)
		{
			m_nFrameCounter[nCnt]++;
		}

#ifdef _DEBUG // Debug���̂�

		// �m�F�p
		// �X�R�A���Z(+1)
		if (pInputKeyboard->GetTrigger(DIK_1) == true)
		{
			// �X�R�A���Z
			CScore::AddScore(1);

			// SE
			pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
		}
		// �X�R�A���Z(-1)
		if (pInputKeyboard->GetTrigger(DIK_0) == true)
		{
			// �X�R�A���Z
			CScore::AddScore(-1);

			// SE
			pSound->PlaySoundA(CSound::SOUND_LABEL_SAMPLE_SE);
		}

		if (m_pObjectX->GetEnable() == false)
		{
			// �f�o�b�O�p�v���C���[����
			if (pInputKeyboard->GetTrigger(DIK_NUMPADPLUS) == true)
			{// 10�L�[��+
				m_pObjectX = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}

		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
		{// ����L�[(ENTER�L�[)�������ꂽ
			CManager::SetMode(MODE_TITLE);
		}

#endif

#ifdef NDEBUG // Release���̂�

		if (m_pObjectX->GetEnable() == false)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
			{// ����L�[(ENTER�L�[)�������ꂽ
				CManager::SetMode(MODE_TITLE);
			}

			if (m_nTransition <= 60 * 6)
			{
				m_nTransition++;
			}

			if (m_nTransition >= 60 * 6)
			{
				//if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(pInputJoypad->JOYKEY_START) == true)
				{// ����L�[(ENTER�L�[)�������ꂽ
					CManager::SetMode(MODE_TITLE);
				}
			}
		}

#endif

	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CGame::Draw(void)
{
	/* �Q�[����ʂ����ɂ�����ʂȕ`�悪����Ȃ�L������ */
}

//----------------------------------------
// �I�u�W�F�N�gX�̎擾����
//----------------------------------------
CObjectX* CGame::GetObjectX(void)
{
	return m_pObjectX;
}

//----------------------------------------
// �|�[�Y�̎擾����
//----------------------------------------
CPause* CGame::GetPause(void)
{
	return m_pPause;
}

//----------------------------------------
// �f�X�g���C�v���C���[����
//----------------------------------------
void CGame::DestoryPlayer(void)
{
	//if (m_pObjectX->GetEnable() == true)
	//{
	//	m_pObjectX->SetEnable(false);
	//}

	m_pObjectX = nullptr;
}