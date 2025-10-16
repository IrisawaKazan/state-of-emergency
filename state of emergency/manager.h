//==============================================================
//
// [manager.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _MANAGER_H_ // このマクロ定義がされてなかったら
#define _MANAGER_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"

// 前方宣言
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoypad;
class CSound;
class CCamera;
class CLight;
class CDebugProc;
class CScore;
class CTimer;
class CBoost;
class CEffect;
class CPause;
//class CFade;

// シーンクラス
class CScene : public CObject
{
public:
	// 画面(モード)の種類
	typedef enum
	{
		MODE_TITLE = 0, // タイトル(最高スコア)画面
		MODE_GAME,      // ゲーム画面
		MODE_TUTORIAL,  // チュートリアル画面
		MODE_RESULT,    // リザルト(ゲームオーバー, スコア)画面

		MODE_MAX
	}MODE;

	CScene(MODE mode);
	~CScene();

	static CScene* Create(MODE mode);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPos(void);

	MODE GetMode(void);

private:
	MODE m_mode;
};

// マネージャクラス
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE nInstance, HWND hWnds);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetInputKeyboard(void);
	static CInputMouse* GetInputMouse(void);
	static CInputJoypad* GetInputJoypad(void);
	static CSound* GetSound(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CDebugProc* GetDebugProc(void);

	static CScore* GetScore(void);
	static CTimer* GetTimer(void);
	static CBoost* GetBoost(void);
	static CEffect* GetEffect(void);
	static CPause* GetPause(void);

	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);

	static CScene* GetScene(void);

	//static CFade* GetFade(void);

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
	static CInputMouse* m_pInputMouse;
	static CInputJoypad* m_pInputJoypad;
	static CSound* m_pSound;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CDebugProc* m_pDebugProc;

	static CScore* m_pScore;
	static CTimer* m_pTimer;
	static CBoost* m_pBoost;
	static CEffect* m_pEffect;
	static CPause* m_pPause;

	static CScene* m_pScene;

	//static CFade* m_pFade;
};

#endif