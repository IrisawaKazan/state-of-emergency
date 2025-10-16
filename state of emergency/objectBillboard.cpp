//==============================================================
//
// [objectBillboard.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"objectBillboard.h"
#include"manager.h"
#include"renderer.h"

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CObjectBillboard::CObjectBillboard(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_faUV = 0.0f;
	m_fzUV = 0.0f;
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
	//m_fWidth = 0.0f;
	//m_fHeight = 0.0f;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CObjectBillboard::~CObjectBillboard()
{

}

//----------------------------------------
// ��������
//----------------------------------------
CObjectBillboard* CObjectBillboard::Create(void)
{
	CObjectBillboard* pObjectBillboard;

	// �I�u�W�F�N�g�r���{�[�h�̐���
	pObjectBillboard = new CObjectBillboard;

	// ����������
	pObjectBillboard->Init();

	// �ʒu�̐ݒ�
	//pObjectBillboard->SetPosition(pos);

	//pObjectBillboard->m_fWidth = fWidth;
	//pObjectBillboard->m_fHeight = fHeight;

	return pObjectBillboard;
}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CObjectBillboard::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\wood.png",
	//	&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, m_pos.z);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, m_pos.z);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, m_pos.z);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, m_pos.z);
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, -100.0f, 0.0f);

	// �e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CObjectBillboard::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̉��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject::Release();
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CObjectBillboard::Update(void)
{
	VERTEX_3D* pVtx; // ���_���ւ̃|�C���^

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
void CObjectBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------------------------------------
// �ʒu�̐ݒ菈��
//----------------------------------------
void CObjectBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �e�N�X�`���̐ݒ菈��
//----------------------------------------
void CObjectBillboard::SetUV(float aUV, float zUV)
{
	m_faUV = aUV;
	m_fzUV = zUV;
}

//----------------------------------------
// �T�C�Y�̐ݒ菈��
//----------------------------------------
void CObjectBillboard::SetSize(float sizeX, float sizeY)
{
	m_fxSize = sizeX;
	m_fySize = sizeY;
}

//----------------------------------------
// �G�t�F�N�g�̐ݒ菈��
//----------------------------------------
void CObjectBillboard::SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius)
{
	VERTEX_3D* pVtx;  // ���_���ւ̃|�C���^

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
// �ʒu�̎擾����
//----------------------------------------
D3DXVECTOR3 CObjectBillboard::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// �e�N�X�`���̊��蓖��
//----------------------------------------
void CObjectBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}