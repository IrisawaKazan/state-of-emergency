#pragma once
//==============================================================
//
// [object3D.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECT3D_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object.h"

// �}�N����`
#define MAX_POLYGONPOS (40.0f)

// �I�u�W�F�N�g3D�N���X
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();

	static CObject3D* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPos(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif