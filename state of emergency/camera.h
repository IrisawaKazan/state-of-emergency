//==============================================================
//
// [camera.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _CAMERA_H_ // ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �J�����N���X
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

private:
	D3DXMATRIX m_mtxView;       // �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection; // �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;         // ���_
	D3DXVECTOR3 m_posR;         // �����_
	D3DXVECTOR3 m_vecU;         // ������x�N�g��
	D3DXVECTOR3 m_rot;          // ����(�p�x)
	float m_fDistance;          // ���_���璍���_�܂ł̋���
};

#endif