//==============================================================
//
// [timer.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TIMER_H_ // ���̃}�N����`������ĂȂ�������
#define _TIMER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object.h"

// �O���錾
class CNumber;

// �}�N����`
#define MAX_TIMER (3)

// �^�C�}�[�N���X
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 7);
	~CTimer();

	static HRESULT Load(void);
	static void Unload(void);

	static CTimer* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);

	void AddTimer(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	float m_fxSize;
	float m_fySize;
	static CNumber* m_apNumber[MAX_TIMER];
	int m_nTimer;
	int m_nContTimer;
};

#endif