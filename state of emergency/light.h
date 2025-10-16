//==============================================================
//
// [light.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _LIGHT_H_ // ���̃}�N����`������ĂȂ�������
#define _LIGHT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �}�N����`
#define MAX_LIGHT (5)

// ���C�g�N���X
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];
};

#endif