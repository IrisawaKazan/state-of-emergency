//==============================================================
//
// [game.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _GAME_H_ // ���̃}�N����`������ĂȂ�������
#define _GAME_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"manager.h"

// �O���錾
class CObjectX;
class CPause;

// �}�N����`
#define MAX_SPAWN (20)                     // �G�̗N����(�������������Əo�����ɂ����Ȃ�)
#define NUM_FRAME_CNT (60 * 2)             // ������ނ̓G���ǂꂾ���A�����ĕ�����
#define MAX_FRAMECOUNTER (32)              // �t���[���J�E���^�[�̐�
#define SPAWN_POS_X (325.0f)               // �I�u�W�F�N�g���N���ꏊ

#define UNINIT_POS (SPAWN_POS_X + 50.0f)   // �I�u�W�F�N�g��������ꏊ

#define MAX_STARDUST_SPAWN (10)            // �A�C�e���̗N����(�������������Əo�����ɂ����Ȃ�)
#define NUM_STARDUST_FRAME_CNT (60 * 15)   // �A�C�e�����ǂꂾ���A�����ĕ�����
#define MAX_COIN10_SPAWN (10)              // 10�R�C���̗N����(�������������Əo�����ɂ����Ȃ�)
#define NUM_COIN10_FRAME_CNT (60 * 10)     // 10�R�C���ǂꂾ���A�����ĕ�����

#define MAX_SmallThings_SPAWN (30)         // ���������̗̂N����(�������������Əo�����ɂ����Ȃ�) �� ��������

#define NUM_SPACESHIP_X (250.0f)           // �F���D�̈ʒuX
#define NUM_SPACESHIP_Y (-100.0f)          // �F���D�̈ʒuY

// �Q�[����ʃN���X
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX* GetObjectX(void);
	static CPause* GetPause(void);

	static void DestoryPlayer(void);

private:
	bool m_bPause;                         // �|�[�Y���Ă��邩�ۂ�
	int m_nSpawn;                          // �X�|�[�����̒���
	int m_nFrameCounter[MAX_FRAMECOUNTER]; // �t���C���J�E���^�[
	int m_nScrapCounter;                   // �S�����p�̃J�E���^�[(�o�ꎞ�Ԃ̒����p)
	int m_nSmallThingsCounter;             // ���������̗p�̃J�E���^�[(�o�ꎞ�Ԃ̒����p)
	int m_nBlackThingsCounter;             // �u���b�N�G�l�~�[�p�̃J�E���^�[(�o�ꎞ�Ԃ̒����p)

	int m_nSmallThingsSpawn;               // ���������̂̃X�|�[�����̒���

	static CObjectX* m_pObjectX;
	static CPause* m_pPause;

	int m_nTransition;
};

#endif