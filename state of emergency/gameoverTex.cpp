//==============================================================
//
// [gameoverTex.h]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"gameoverTex.h"
#include"manager.h"
#include"renderer.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CGameoverTex::m_pTexture = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CGameoverTex::CGameoverTex(int nPriority) : CObject2D(nPriority)
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CGameoverTex::~CGameoverTex()
{

}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CGameoverTex::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameover.png",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CGameoverTex::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//----------------------------------------
// 生成処理
//----------------------------------------
CGameoverTex* CGameoverTex::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CGameoverTex* pGameoverTex;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pGameoverTex = new CGameoverTex;

		// テクスチャの設定
		pGameoverTex->SetUV(1.0f, 1.0f);

		// 初期化処理
		pGameoverTex->Init();

		pGameoverTex->SetPosition(pos);

		// サイズの設定
		pGameoverTex->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pGameoverTex->BindTexture(m_pTexture);

		return pGameoverTex;
	}

	return NULL;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CGameoverTex::Init(void)
{
	CObject2D::Init();

	// 種類の設定処理
	CObject::SetType(TYPE_GAMEOVERTEX);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CGameoverTex::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CGameoverTex::Update(void)
{
	CObject2D::Update();
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CGameoverTex::Draw(void)
{
	CObject2D::Draw();
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CGameoverTex::SetPosition(D3DXVECTOR3 pos)
{
	CObject2D::SetPosition(pos);
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CGameoverTex::SetSize(float xsize, float ysize)
{
	CObject2D::SetSize(xsize, ysize);
}