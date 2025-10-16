//==============================================================
//
// [score.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"score.h"
#include"number.h"
#include"renderer.h"
#include"manager.h"
#include"object.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CScore::m_pTexture = nullptr;
CNumber* CScore::m_apNumber[MAX_SCORE] = {};
int CScore::m_nScore = NULL;

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CScore::CScore(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CScore::~CScore()
{

}

//----------------------------------------
// �e�N�X�`���̐���(�ǂݍ���)
//----------------------------------------
HRESULT CScore::Load(void)
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
void CScore::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//----------------------------------------
// �X�R�A�̐�������
//----------------------------------------
CScore* CScore::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CScore* pScore = nullptr;

	// �X�R�A�̐���
	pScore = new CScore;

	pScore->m_pos = pos;
	pScore->m_fxSize = xsize;
	pScore->m_fySize = ysize;

	// ����������
	pScore->Init();

	return pScore;
}

//----------------------------------------
// �X�R�A�̏���������
//----------------------------------------
HRESULT CScore::Init(void)
{
	m_nScore = 0; // ��������Ƃ��ɃX�R�A��0�ɖ߂�����

	// �������v�Z
	float fTexPos = m_fySize / MAX_SCORE;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->SetSize(fTexPos, m_fxSize);
		m_apNumber[nCnt]->SetPosition(m_pos);
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x + (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fxSize);

		m_apNumber[nCnt]->BindTexture(m_pTexture);
	}

	// �^�C�v�̐ݒ�
	SetType(TYPE_SCORE);

	return S_OK;
}

//----------------------------------------
// �X�R�A�̏I������
//----------------------------------------
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}

	CObject::Release();
}

//----------------------------------------
// �X�R�A�̍X�V����
//----------------------------------------
void CScore::Update(void)
{
	//for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	//{
	//	if (m_apNumber[nCnt] != nullptr)
	//	{
	//		m_apNumber[nCnt]->SetDigit(nCnt);
	//	}
	//}
}

//----------------------------------------
// �X�R�A�̕`�揈��
//----------------------------------------
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//----------------------------------------
// �X�R�A�̈ʒu�̐ݒ菈��
//----------------------------------------
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �X�R�A�̈ʒu�̎擾����
//----------------------------------------
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// �X�R�A�̉��Z����
//----------------------------------------
void CScore::AddScore(int nScore)
{
	int aPosTex[MAX_SCORE] = {};
	int nData = 10000/*0000*/;
	int nData2 = 1000/*0000*/;

	m_nScore += nScore;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aPosTex[nCnt] = m_nScore % nData / nData2;
		nData = nData / 10;
		nData2 = nData2 / 10;

		m_apNumber[nCnt]->Score(aPosTex[nCnt]);
	}
}

//----------------------------------------
// �X�R�A�̃J�E���g����
//----------------------------------------
int CScore::ScoreCount(int nScore)
{
	int nData = nScore;
	int nDigitNum = 0;

	while (nData != 0)
	{
		nData /= 10;
		nDigitNum++;
	}
	if (nScore == 0)
	{
		nDigitNum = 1;
	}

	return nDigitNum;
}