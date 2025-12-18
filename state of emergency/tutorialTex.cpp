//==============================================================
//
// [tutorialTex.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"tutorialTex.h"
#include"manager.h"
#include"renderer.h"
#include"object.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CTutorialTex::m_pTexture = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CTutorialTex::CTutorialTex(int nPriority) : CObject2D(nPriority)
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CTutorialTex::~CTutorialTex()
{

}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CTutorialTex::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpg",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CTutorialTex::Unload(void)
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
CTutorialTex* CTutorialTex::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CTutorialTex* pBackground;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pBackground = new CTutorialTex;

		// テクスチャの設定
		pBackground->SetUV(1.0f, 1.0f);

		// 初期化処理
		pBackground->Init();

		pBackground->SetPosition(pos);

		// サイズの設定
		pBackground->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pBackground->BindTexture(m_pTexture);

		return pBackground;
	}

	return NULL;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CTutorialTex::Init(void)
{
	CObject2D::Init();

	// 種類の設定処理
	CObject::SetType(TYPE_TUTORIALTEX);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CTutorialTex::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CTutorialTex::Update(void)
{
	CObject2D::Update();
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CTutorialTex::Draw(void)
{
	CObject2D::Draw();
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CTutorialTex::SetPosition(D3DXVECTOR3 pos)
{
	CObject2D::SetPosition(pos);
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CTutorialTex::SetSize(float xsize, float ysize)
{
	CObject2D::SetSize(xsize, ysize);
}