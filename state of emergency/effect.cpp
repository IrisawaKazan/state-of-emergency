//==============================================================
//
// [effect.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"effect.h"
#include"manager.h"
#include"renderer.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = nullptr;

//----------------------------------------
// エフェクトのコンストラクタ
//----------------------------------------
CEffect::CEffect(int nPriority) : CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fRedius = 0.0f;
	m_nLife = NULL;
}

//----------------------------------------
// エフェクトのデストラクタ
//----------------------------------------
CEffect::~CEffect()
{

}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CEffect::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CEffect::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//----------------------------------------
// エフェクトの生成処理
//----------------------------------------
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife, float xsize, float ysize)
{
	CEffect* pEffect;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pEffect = new CEffect;

		// 初期化処理
		pEffect->Init(pos, col, fRedius, nLife);

		// サイズの設定
		pEffect->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pEffect->BindTexture(m_pTexture);

		return pEffect;
	}

	return NULL;
}

//----------------------------------------
// エフェクトの初期化処理
//----------------------------------------
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife)
{
	// テクスチャの設定
	CObject2D::SetUV(1.0f, 1.0f);

	SetPosition(pos);

	CObject2D::Init();

	m_pos = pos;

	m_col = col;

	m_fRedius = fRedius;

	m_nLife = nLife;

	// 種類の設定処理
	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//----------------------------------------
// エフェクトの終了処理
//----------------------------------------
void CEffect::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// エフェクトの更新処理
//----------------------------------------
void CEffect::Update(void)
{
	CObject2D::Update();

	CObject2D::SetEffect(m_pos, m_col, m_fRedius);

	m_nLife--;

	m_fRedius -= 1.5f;

	if (m_nLife == 0)
	{
		Uninit();
	}
}

//----------------------------------------
// エフェクトの描画処理
//----------------------------------------
void CEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//----------------------------------------
// エフェクトの位置の設定処理
//----------------------------------------
void CEffect::SetPosition(D3DXVECTOR3 pos)
{
	CObject2D::SetPosition(pos);
}

//----------------------------------------
// エフェクトのサイズの設定処理
//----------------------------------------
void CEffect::SetSize(float xsize, float ysize)
{
	CObject2D::SetSize(xsize, ysize);
}