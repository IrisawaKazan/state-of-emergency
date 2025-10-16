//==============================================================
//
// [objectX.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECTX_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECTX_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"
#include"object.h"

// �}�N����`
#define MAX_PMOVE (2.0f) // �v���[���[�̑���

// �I�u�W�F�N�gX�N���X
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);
	~CObjectX();

	static CObjectX* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetPositionOld(D3DXVECTOR3 posOld);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetDeadCounter(int DeadCounter);
	void SetBonus(int bonus);

	void SetEnable(bool enable);
	void SetSigns(bool signs);
	void SetPowerUp(bool powerup);
	void SetScoreBonus(bool scorebonus);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);
	int GetDeadCounter(void);
	int GetBonus(void);

	bool GetEnable(void);
	bool GetSigns(void);
	bool GetPowerUp(void);
	bool GetScoreBonus(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;       // ���b�V��(���_���W)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;  // �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;         // �}�e���A���̐�
	D3DXVECTOR3 m_pos;        // �ʒu
	D3DXVECTOR3 m_posOld;     // �O��̈ʒu
	D3DXVECTOR3 m_rot;        // ����
	D3DXMATRIX m_mtxWorld;    // ���[���h�}�g���b�N�X

	float m_fRotation;		  // ���[�e�[�V����
	D3DXVECTOR3 m_size;		  // �傫��
	D3DXVECTOR3 m_vtxMin;	  // ���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMax;	  // ���f���̍ő�l

	bool m_bUse;			  // �g�p���Ă��邩
	bool m_bRetention;		  // �A�C�e����ێ����Ă��邩
	bool m_bPowerUp;		  // �p���[�A�b�v���Ă��邩
	bool m_bScoreBonus;		  // �X�R�A�{�[�i�X�^�C����

	int m_nScoreBonus;		  // �X�R�A�{�[�i�X�̔{��

	int m_nCounter;           // �X�R�A�Ŏg���J�E���^�[
	int m_nDeadCounter;       // ���܂ł̃J�E���^�[
	int m_nPowerUpCounter;    // �p���[�A�b�v���Ɏg���J�E���^�[
	int m_nScoreBonusCounter; // �X�R�A�{�[�i�X���Ɏg���J�E���^�[

	float m_fSpeedUp;         // �p���[�A�b�v���Ƀv���C���[�̈ړ����x�������Ȃ�
};

#endif