//==============================================================
//
// [number.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _NUMBER_H_ // ���̃}�N����`������ĂȂ�������
#define _NUMBER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �}�N����`
#define MAX_NUM (64)

// �i���o�[�N���X
class CNumber
{
public:
    CNumber();
    virtual ~CNumber();

    HRESULT Init(D3DXVECTOR3 pos, float xsize, float ysize);
    void Uninit(void);
    void Draw(void);

    void SetPosition(D3DXVECTOR3 pos);
    void SetUV(float aUV, float zUV);
    void SetSize(float xsize, float ysize);
    void SetDigit(int digit);

    void Score(int score);
    void Timer(int timer);

    void BindTexture(const LPDIRECT3DTEXTURE9 pTexture);

private:
    LPDIRECT3DTEXTURE9 m_pTexture;
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
    D3DXVECTOR3 m_pos;
    float m_faUV;
    float m_fzUV;
    float m_fxSize;
    float m_fySize;
};

#endif