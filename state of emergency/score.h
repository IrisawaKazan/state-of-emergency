//==============================================================
//
// [score.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _SCORE_H_ // ���̃}�N����`������ĂȂ�������
#define _SCORE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object.h"

// �O���錾
class CNumber;

// �}�N����`
#define MAX_SCORE (4)

// �X�R�A�N���X
class CScore : public CObject
{
public:
	CScore(int nPriority = 7);
	~CScore();

	static HRESULT Load(void);
	static void Unload(void);

	static CScore* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);

	static void AddScore(int nScore);

	int ScoreCount(int nScore);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	float m_fxSize;
	float m_fySize;
	static CNumber* m_apNumber[MAX_SCORE];
	static int m_nScore;
};

#endif