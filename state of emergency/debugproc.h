//==============================================================
//
// [debugproc.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _DEBUGPROC_H_ // ���̃}�N����`������ĂȂ�������
#define _DEBUGPROC_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �}�N����`
#define MAX_CHARACTER (1024)

// �f�o�b�O�N���X
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);
	static void Print(const char* fint, ...);
	static void Draw(void);

private:
	static LPD3DXFONT m_pFont;         // �t�H���g�ւ̃|�C���^
	static char m_aStr[MAX_CHARACTER]; // ��������i�[����o�b�t�@
};

#endif