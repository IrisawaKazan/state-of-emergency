//==============================================================
//
// [pause.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"pause.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CPause::m_pTexture = nullptr;

//----------------------------------------
// ポーズのコンストラクタ
//----------------------------------------
CPause::CPause(int nPriority) : CObject2D(nPriority)
{
	m_bUse = false;
}

//----------------------------------------
// ポーズのデストラクタ
//----------------------------------------
CPause::~CPause()
{
}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CPause::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause001.png",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CPause::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//----------------------------------------
// 生成処理
//----------------------------------------
CPause* CPause::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CPause* pPause;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pPause = new CPause;

		// テクスチャの設定
		pPause->SetUV(1.0f, 1.0f);

		// 初期化処理
		pPause->Init();

		pPause->SetPosition(pos);

		// サイズの設定
		pPause->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pPause->BindTexture(m_pTexture);

		return pPause;
	}

	return NULL;
}

//----------------------------------------
// ポーズの初期化処理
//----------------------------------------
HRESULT CPause::Init(void)
{
	CObject2D::Init();

	// 種類の設定処理
	CObject::SetType(TYPE_PAUSE);

	return S_OK;
}

//----------------------------------------
// ポーズの終了処理
//----------------------------------------
void CPause::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// ポーズの更新処理
//----------------------------------------
void CPause::Update(void)
{
	if (m_bUse == true)
	{
		CObject2D::Update();
	}
}

//----------------------------------------
// ポーズの描画処理
//----------------------------------------
void CPause::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}

//----------------------------------------
// ポーズテクスチャの使用有無の設定処理
//----------------------------------------
void CPause::SetUse(bool use)
{
	m_bUse = use;
}

//----------------------------------------
// ポーズテクスチャの使用有無の取得処理
//----------------------------------------
bool CPause::GetUse(void)
{
	return m_bUse;
}