//==============================================================
//
// [object3D.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"object3D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = D3DXMATRIX();
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CObject3D::~CObject3D()
{

}

//----------------------------------------
// ��������
//----------------------------------------
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D* pObject3D;

	// �I�u�W�F�N�g3D�̐���
	pObject3D = new CObject3D;

	// ����������
	pObject3D->Init();

	// �ʒu�̐ݒ�
	pObject3D->SetPosition(pos);

	return pObject3D;
}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CObject3D::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-MAX_POLYGONPOS, 0.0f, MAX_POLYGONPOS);
	pVtx[1].pos = D3DXVECTOR3(MAX_POLYGONPOS, 0.0f, MAX_POLYGONPOS);
	pVtx[2].pos = D3DXVECTOR3(-MAX_POLYGONPOS, 0.0f, -MAX_POLYGONPOS);
	pVtx[3].pos = D3DXVECTOR3(MAX_POLYGONPOS, 0.0f, -MAX_POLYGONPOS);

	// �e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
void CObject3D::Uninit(void)
{
	// �e�N�X�`���̉��
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
void CObject3D::Update(void)
{
	CInputKeyboard* pInputKeyboard;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.z += 5.0f;
	}
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//LPDIRECT3DTEXTURE9 pTexMT;

	//// �}���`�^�[�Q�b�g�p�̃e�N�X�`���̎擾
	//pTexMT = CManager::GetRenderer()->GetTextureMT();

	// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, pTexMT);

	// �v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

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

	// �e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
// �ʒu�̐ݒ菈��
//----------------------------------------
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// �ʒu�̎擾����
//----------------------------------------
D3DXVECTOR3 CObject3D::GetPos(void)
{
	return m_pos;
}