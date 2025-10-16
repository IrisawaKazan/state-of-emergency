//==============================================================
//
// [title.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TITLE_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"manager.h"

// �O���錾
//class CObjectX;

// �}�N����`
#define MAX_PLAYER (4)                     // �Đ��v���C���[�̐�
#define NUM_SEPLAY_FRAME_CNT (60 * 20)     // ������ނ�SE���ǂꂾ���A�����čĐ�����邩
#define MAX_SPAWN_FLOAT (5)                // ���V���̗N����(�������������Əo�����ɂ����Ȃ�)
#define SPAWN_POS_Z (250.0f)               // ���V�����N���ꏊ
#define UNINIT_POS_Z (SPAWN_POS_Z + 50.0f) // ���V����������ꏊ
#define MAX_FRAMECOUNTER_F (8)             // �t���C���J�E���^�[

// �^�C�g����ʃN���X
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static CObjectX* GetObjectX(void);
	//static void DestoryPlayer(void);

private:
	int m_nPlay;                             // SE���Đ�����
	int m_nCounter[MAX_PLAYER];              // ���i�ōĐ����Ȃ����߂̃J�E���^�[
	int m_nFrameCounter[MAX_FRAMECOUNTER_F]; // �t���C���J�E���^�[

	int m_nSpawnFloating;                    // ���V���̃X�|�[�����̒���

	//static CObjectX* m_pObjectX;
};

#endif