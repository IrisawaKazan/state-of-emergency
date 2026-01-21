//==============================================================
//
// [blood.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"blood.h"
#include"manager.h"
#include"renderer.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBlood::m_pTexture = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CBlood::CBlood(int nPriority) : CObject2D(nPriority)
{

}

//----------------------------------------
// デストラクタ
//----------------------------------------
CBlood::~CBlood()
{

}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CBlood::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\blood_green.png",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CBlood::Unload(void)
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
CBlood* CBlood::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CBlood* pBlood;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pBlood = new CBlood;

		// テクスチャの設定
		pBlood->SetUV(1.0f, 1.0f);

		// 初期化処理
		pBlood->Init();

		pBlood->SetPosition(pos);

		// サイズの設定
		pBlood->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pBlood->BindTexture(m_pTexture);

		return pBlood;
	}

	return NULL;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CBlood::Init(void)
{
	CObject2D::Init();

	// 種類の設定処理
	CObject::SetType(TYPE_BLOOD);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CBlood::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CBlood::Update(void)
{
	CObject2D::Update();
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CBlood::Draw(void)
{
	CObject2D::Draw();
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CBlood::SetPosition(D3DXVECTOR3 pos)
{
	CObject2D::SetPosition(pos);
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CBlood::SetSize(float xsize, float ysize)
{
	CObject2D::SetSize(xsize, ysize);
}