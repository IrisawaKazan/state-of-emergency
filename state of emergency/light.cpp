//==============================================================
//
// [light.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"light.h"
#include"manager.h"
#include"renderer.h"

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CLight::CLight()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_aLight[nCnt] = D3DLIGHT9();
	}
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CLight::~CLight()
{

}

//----------------------------------------
// ���C�g�̏���������
//----------------------------------------
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; // ���C�g�̕����x�N�g��

	// ���C�g���N���A����
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	//=========
	// ���C�g0
	//=========
	// ���C�g0�̏���ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U����ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̕�����ݒ�
	vecDir = D3DXVECTOR3(1.5f, -1.5f, -1.5f);

	// ���K������(�傫���ʒu�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[0].Direction = vecDir;

	// ���C�g0�̐ݒ������
	pDevice->SetLight(0, &m_aLight[0]);

	// ���C�g0��L���ɂ���(ON,OFF)
	pDevice->LightEnable(0, TRUE);

	//=========
	// ���C�g1
	//=========
	// ���C�g1�̏���ݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U����ݒ�
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g1�̕�����ݒ�
	vecDir = D3DXVECTOR3(-1.5f, -1.5f, 1.5f);

	// ���K������(�傫���ʒu�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[1].Direction = vecDir;

	// ���C�g1�̐ݒ������
	pDevice->SetLight(1, &m_aLight[1]);

	// ���C�g1��L���ɂ���(ON,OFF)
	pDevice->LightEnable(1, TRUE);

	////=========
	//// ���C�g2
	////=========
	//// ���C�g2�̏���ݒ�
	//m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g2�̊g�U����ݒ�
	//m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g2�̕�����ݒ�
	//vecDir = D3DXVECTOR3(-1.5f, -1.5f, -1.5f);

	//// ���K������(�傫���ʒu�̃x�N�g���ɂ���)
	//D3DXVec3Normalize(&vecDir, &vecDir);

	//m_aLight[2].Direction = vecDir;

	//// ���C�g2�̐ݒ������
	//pDevice->SetLight(2, &m_aLight[2]);

	//// ���C�g2��L���ɂ���(ON,OFF)
	//pDevice->LightEnable(2, TRUE);

	////=========
	//// ���C�g3
	////=========
	//// ���C�g3�̏���ݒ�
	//m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g3�̊g�U����ݒ�
	//m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g3�̕�����ݒ�
	//vecDir = D3DXVECTOR3(1.5f, -1.5f, 1.5f);

	//// ���K������(�傫���ʒu�̃x�N�g���ɂ���)
	//D3DXVec3Normalize(&vecDir, &vecDir);

	//m_aLight[3].Direction = vecDir;

	//// ���C�g3�̐ݒ������
	//pDevice->SetLight(3, &m_aLight[3]);

	//// ���C�g3��L���ɂ���(ON,OFF)
	//pDevice->LightEnable(3, TRUE);

	return S_OK;
}

//----------------------------------------
// ���C�g�̏I������
//----------------------------------------
void CLight::Uninit(void)
{

}

//----------------------------------------
// ���C�g�̍X�V����
//----------------------------------------
void CLight::Update(void)
{

}