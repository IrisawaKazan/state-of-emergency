//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TUTORIAL_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"manager.h"

// �}�N����`


// �`���[�g���A����ʃN���X
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif