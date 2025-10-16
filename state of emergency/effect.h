//==============================================================
//
// [effect.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _EFFECT_H_ // ���̃}�N����`������ĂȂ�������
#define _EFFECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object2D.h"

// �G�t�F�N�g�N���X
class CEffect : public CObject2D
{
public:
	CEffect(int nPriority = 7);
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);

	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife, float xsize, float ysize);

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float xsize, float ysize);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos; // �ʒu
	D3DXCOLOR m_col;   // �F
	float m_fRedius;   // ���a(�傫��)
	int m_nLife;       // ����
};

#endif