//==============================================================
//
// [number.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"number.h"
#include"manager.h"
#include"renderer.h"

// �ÓI�����o�ϐ��錾


//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CNumber::CNumber()
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_faUV = 0.0f;
	m_fzUV = 0.0f;
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CNumber::~CNumber()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CNumber::Init(D3DXVECTOR3 pos, float xsize, float ysize)
{
	m_pos = pos;
	m_faUV = 0.1f;
	m_fzUV = 1.0f;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - xsize, m_pos.y - ysize, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + xsize, m_pos.y - ysize, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - xsize, m_pos.y + ysize, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + xsize, m_pos.y + ysize, m_pos.z);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_faUV, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_fzUV);
	pVtx[3].tex = D3DXVECTOR2(m_faUV, m_fzUV);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CNumber::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CNumber::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
// �ʒu�̐ݒ菈��
//----------------------------------------
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �e�N�X�`���̐ݒ菈��
//----------------------------------------
void CNumber::SetUV(float aUV, float zUV)
{
	m_faUV = aUV;
	m_fzUV = zUV;
}

//----------------------------------------
// �T�C�Y�̐ݒ菈��
//----------------------------------------
void CNumber::SetSize(float xsize, float ysize)
{
	m_fxSize = xsize;
	m_fySize = ysize;
}

//----------------------------------------
// �����̐ݒ菈��
//----------------------------------------
void CNumber::SetDigit(int digit)
{
	float tex = digit * 0.1f;

	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_faUV + tex, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(tex, m_fzUV);
	pVtx[3].tex = D3DXVECTOR2(m_faUV + tex, m_fzUV);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// �X�R�A���Z����
//----------------------------------------
void CNumber::Score(int score)
{
	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * score, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * score), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * score, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * score), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// �^�C�}�[���Z����
//----------------------------------------
void CNumber::Timer(int timer)
{
	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * timer, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * timer), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * timer, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * timer), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// �e�N�X�`���̊��蓖��
//----------------------------------------
void CNumber::BindTexture(const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}