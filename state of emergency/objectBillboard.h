//==============================================================
//
// [objectBillboard.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECTBILLBOARD_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECTBILLBOARD_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object.h"

// �I�u�W�F�N�g�r���{�[�h�N���X
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	static CObjectBillboard* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetUV(float aUV, float zUV);
	void SetSize(float sizeX, float sizeY);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius);

	D3DXVECTOR3 GetPos(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;     // �ʒu
	D3DXVECTOR3 m_rot;     // ����
	D3DXMATRIX m_mtxWorld; // ���[���h�}�g���b�N�X
	float m_fLength;
	float m_fAngle;
	float m_faUV;
	float m_fzUV;
	float m_fxSize;
	float m_fySize;
	//float m_fWidth;
	//float m_fHeight;
};

#endif