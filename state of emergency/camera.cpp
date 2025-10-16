//==============================================================
//
// [camera.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CCamera::CCamera()
{
	m_mtxView = D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_mtxProjection = D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CCamera::~CCamera()
{

}

//----------------------------------------
// �J�����̏���������
//----------------------------------------
HRESULT CCamera::Init(void)
{
	// ���_,�����_,�������ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 375.0f, -1.0f);
	m_posR = D3DXVECTOR3(0.0f, -120.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = sqrtf((m_posR.x - m_posV.x) * (m_posR.x - m_posV.x) +
		(m_posR.y - m_posV.y) * (m_posR.y - m_posV.y) +
		(m_posR.z - m_posV.z) * (m_posR.z - m_posV.z));

	return S_OK;
}

//----------------------------------------
// �J�����̏I������
//----------------------------------------
void CCamera::Uninit(void)
{

}

//----------------------------------------
// �J�����̍X�V����
//----------------------------------------
void CCamera::Update(void)
{

}

//----------------------------------------
// �J�����̐ݒ菈��
//----------------------------------------
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}