//==============================================================
//
// [timer.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"timer.h"
#include"number.h"
#include"renderer.h"
#include"manager.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CTimer::m_pTexture = nullptr;
CNumber* CTimer::m_apNumber[MAX_TIMER] = {};

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
	m_nTimer = NULL;
	m_nContTimer = NULL;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CTimer::~CTimer()
{

}

//----------------------------------------
// �e�N�X�`���̐���(�ǂݍ���)
//----------------------------------------
HRESULT CTimer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̏���������
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// �e�N�X�`���̔j��
//----------------------------------------
void CTimer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//----------------------------------------
// �^�C�}�[�̐�������
//----------------------------------------
CTimer* CTimer::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CTimer* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		pTimer = new CTimer;
	}

	pTimer->m_pos = pos;
	pTimer->m_fxSize = xsize;
	pTimer->m_fySize = ysize;

	pTimer->Init();

	return pTimer;
}

//----------------------------------------
// �^�C�}�[�̏���������
//----------------------------------------
HRESULT CTimer::Init(void)
{
	m_nContTimer = 0; // �����^�C��

	float fTexPos = m_fySize / MAX_TIMER;

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->SetSize(fTexPos, m_fxSize);
		m_apNumber[nCnt]->SetPosition(m_pos);
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x + (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fxSize);

		m_apNumber[nCnt]->BindTexture(m_pTexture);
	}

	// �^�C�v�̐ݒ�
	SetType(TYPE_TIMER);

	return S_OK;
}

//----------------------------------------
// �^�C�}�[�̏I������
//----------------------------------------
void CTimer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}

	CObject::Release();
}

//----------------------------------------
// �^�C�}�[�̍X�V����
//----------------------------------------
void CTimer::Update(void)
{
	AddTimer();
}

//----------------------------------------
// �^�C�}�[�̕`�揈��
//----------------------------------------
void CTimer::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//----------------------------------------
// �^�C�}�[�̈ʒu�̐ݒ菈��
//----------------------------------------
void CTimer::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �^�C�}�[�̈ʒu�̎擾����
//----------------------------------------
D3DXVECTOR3 CTimer::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// �^�C�}�[�̉��Z����
//----------------------------------------
void CTimer::AddTimer(void)
{
	int texU[MAX_TIMER] = { NULL };

	m_nTimer++;

	if (m_nTimer >= 60)
	{
		//m_nContTimer--; // �J�E���g�_�E��
		m_nContTimer++; // �J�E���g�A�b�v
		m_nTimer = 0;
	}

	texU[0] = m_nContTimer % 1000 / 100;
	texU[1] = m_nContTimer % 100 / 10;
	texU[2] = m_nContTimer % 10 / 1;

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		m_apNumber[nCnt]->Timer(texU[nCnt]);
	}
}