//==============================================================
//
// [result.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _RESULT_H_ // ���̃}�N����`������ĂȂ�������
#define _RESULT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"manager.h"

// �}�N����`


// ���U���g��ʃN���X
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif