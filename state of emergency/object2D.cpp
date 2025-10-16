//==============================================================
//
// [object2D.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"object2D.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

// �ÓI�����o�ϐ��錾


//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_faUV = 0.0f;
	m_fzUV = 0.0f;
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
	m_nCounterAnim = NULL;
	m_nPatternAnim = NULL;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CObject2D::~CObject2D()
{

}

//----------------------------------------
// ��������
//----------------------------------------
CObject2D* CObject2D::Create(void)
{
	CObject2D* pObject2D;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D;

	// ����������
	pObject2D->Init();

	return pObject2D;
}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CObject2D::Init(void)
{
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
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

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
void CObject2D::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g(�������g)�̔j��
	this->Release();
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CObject2D::Update(void)
{
	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	m_fLength = sqrtf(m_fxSize * m_fxSize + m_fySize * m_fySize) / 2.0f;

	// �Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_fxSize, m_fySize);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
// �ʒu�̐ݒ菈��
//----------------------------------------
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �e�N�X�`���̐ݒ菈��
//----------------------------------------
void CObject2D::SetUV(float aUV, float zUV)
{
	m_faUV = aUV;
	m_fzUV = zUV;
}

//----------------------------------------
// �T�C�Y�̐ݒ菈��
//----------------------------------------
void CObject2D::SetSize(float xsize, float ysize)
{
	m_fxSize = xsize;
	m_fySize = ysize;
}

//----------------------------------------
// �G�t�F�N�g�̐ݒ菈��
//----------------------------------------
void CObject2D::SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - fRedius, pos.y - fRedius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fRedius, pos.y - fRedius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fRedius, pos.y + fRedius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fRedius, pos.y + fRedius, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// �e�N�X�`���A�j���[�V�����̏���
//----------------------------------------
void CObject2D::TextureAnimation(int texposx, int animspeed)
{
	float OffSetX = 1.0f / texposx;

	m_nCounterAnim++; // �J�E���^�[���v�Z

	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �A�j���[�V����
	if ((m_nCounterAnim % animspeed) == 0)
	{
		m_nCounterAnim = 0;                              // �J�E���^�[�������l�ɖ߂�

		m_nPatternAnim = (m_nPatternAnim + 1) % texposx; // �p�^�[��No.���X�V����

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX + OffSetX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX + OffSetX, 1.0f);
	}
}

//----------------------------------------
// �ʒu�̎擾����
//----------------------------------------
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// �A�j���[�V�����p�^�[���̎擾����
//----------------------------------------
int CObject2D::GetPtAnim(void)
{
	return m_nPatternAnim;
}

//----------------------------------------
// �A�j���[�V�����J�E���^�[�̎擾����
//----------------------------------------
int CObject2D::GetCntAnim(void)
{
	return m_nCounterAnim;
}

//----------------------------------------
// �e�N�X�`���̊��蓖��
//----------------------------------------
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}