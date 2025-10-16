//==============================================================
//
// [object.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECT_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �}�N����`
#define MAX_OBJ (512)
#define MAX_PRI (8)

// �I�u�W�F�N�g�N���X
class CObject
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_TIMER,
		TYPE_SCORE,
		TYPE_EFFECT,
		TYPE_PAUSE,
		TYPE_PLAYER,

		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);
	virtual	~CObject();

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	virtual void SetPosition(D3DXVECTOR3 pos) = 0;

	virtual D3DXVECTOR3 GetPos(void) = 0;

	void SetType(TYPE type);
	TYPE GetType(void);
	static CObject* GetObj(int nPriority, int nIdx);
	static int GetNumAll(void);

protected:
	void Release(void);

private:
	static CObject* m_apObject[MAX_PRI][MAX_OBJ];
	static int m_nNumAll; // �I�u�W�F�N�g�̑���
	int m_nID;            // �������g��ID
	TYPE m_type;
	int m_nPriority; // �D�揇�ʂ̈ʒu
};

#endif