//==============================================================
//
// [pause.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _PAUSE_H_ // ���̃}�N����`������ĂȂ�������
#define _PAUSE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object2D.h"

// �|�[�Y�N���X
class CPause : public CObject2D
{
public:
	CPause(int nPriority = 2);
	~CPause();

	static HRESULT Load(void);
	static void Unload(void);

	static CPause* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetUse(bool use);
	bool GetUse(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;

	bool m_bUse;
};

#endif