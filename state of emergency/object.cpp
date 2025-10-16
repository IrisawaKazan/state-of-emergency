//==============================================================
//
// [object.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"object.h"
#include"renderer.h"
#include"object2D.h"
#include"camera.h"
#include"manager.h"

// �ÓI�����o�ϐ��錾
int CObject::m_nNumAll = NULL;
CObject* CObject::m_apObject[MAX_PRI][MAX_OBJ] = {}; // �I�u�W�F�N�g�ւ̃|�C���^

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CObject::CObject(int nPriority)
{
	m_nID = 0;
	m_type = TYPE_NONE;
	m_nPriority = 0;

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (m_apObject[nPriority][nCntObj] == nullptr)
		{
			m_apObject[nPriority][nCntObj] = this; // �������g����
			m_nPriority = nPriority;
			m_nID = nCntObj;            // �������g��ID��ۑ�
			m_nNumAll++;                // �������J�E���g�A�b�v
			break;
		}
	}
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CObject::~CObject()
{

}

//----------------------------------------
// �S�ẴI�u�W�F�N�g�̔j��
//----------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// �I������
				m_apObject[nCntPri][nCntObj]->Uninit();
			}
		}
	}
}

//----------------------------------------
// �S�ẴI�u�W�F�N�g�̍X�V����
//----------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// �X�V����
				m_apObject[nCntPri][nCntObj]->Update();
			}
		}
	}
}

//----------------------------------------
// �S�ẴI�u�W�F�N�g�̕`�揈��
//----------------------------------------
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̐ݒ�
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < MAX_PRI; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				// �`�揈��
				m_apObject[nCntPri][nCntObj]->Draw();
			}
		}
	}
}

//----------------------------------------
// �I�u�W�F�N�g�̃^�C�v�ݒ菈��
//----------------------------------------
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//----------------------------------------
// �I�u�W�F�N�g�̃^�C�v�擾����
//----------------------------------------
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}

//----------------------------------------
// �I�u�W�F�N�g�̎擾����
//----------------------------------------
CObject* CObject::GetObj(int nPriority, int nIdx)
{
	return m_apObject[nPriority][nIdx];
}

//----------------------------------------
// �I�u�W�F�N�g�̑����̎擾����
//----------------------------------------
int CObject::GetNumAll(void)
{
	return m_nNumAll;
}

//----------------------------------------
// �I�u�W�F�N�g�̔j��
//----------------------------------------
void CObject::Release(void)
{
	int nPri = this->m_nPriority;
	int nIdx = this->m_nID;

	if (m_apObject[nPri][nIdx] != nullptr)
	{
		delete m_apObject[nPri][nIdx];
		m_apObject[nPri][nIdx] = nullptr;

		m_nNumAll--; // �������J�E���g�_�E��
	}
}