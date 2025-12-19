//==============================================================
//
// [playerTex.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"playerTex.h"
#include"manager.h"
#include"renderer.h"
#include"object.h"
#include"tutorial.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CPlayerTex::m_pTexture = nullptr;

//----------------------------------------
// コンストラクタ
//----------------------------------------
CPlayerTex::CPlayerTex(int nPriority) : CObject2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CPlayerTex::~CPlayerTex()
{

}

//----------------------------------------
// テクスチャの生成(読み込み)
//----------------------------------------
HRESULT CPlayerTex::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの初期化処理
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerTex.png",
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
// テクスチャの破棄
//----------------------------------------
void CPlayerTex::Unload(void)
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
CPlayerTex* CPlayerTex::Create(D3DXVECTOR3 pos, float xsize, float ysize)
{
	CPlayerTex* pPlayerTex;

	int nNumAll = CObject::GetNumAll();

	if (nNumAll <= MAX_OBJ)
	{
		// オブジェクト2Dの生成
		pPlayerTex = new CPlayerTex;

		// テクスチャの設定
		pPlayerTex->SetUV(1.0f, 1.0f);

		// 初期化処理
		pPlayerTex->Init();

		pPlayerTex->SetPosition(pos);

		// サイズの設定
		pPlayerTex->SetSize(xsize, ysize);

		// テクスチャの割り当て
		pPlayerTex->BindTexture(m_pTexture);

		return pPlayerTex;
	}

	return NULL;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CPlayerTex::Init(void)
{
	CObject2D::Init();

	// 種類の設定処理
	CObject::SetType(TYPE_PLAYERTEX);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CPlayerTex::Uninit(void)
{
	CObject2D::Uninit();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CPlayerTex::Update(void)
{
	CObject2D::Update();

	// 位置の取得
	D3DXVECTOR3 pos = CPlayerTex::GetPos();

	// 位置を更新
	pos.x += m_move.x;

	m_move.x = NUM_PLAYERYEX_MOVE;

	CPlayerTex::SetPosition(pos);
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CPlayerTex::Draw(void)
{
	CObject2D::Draw();
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CPlayerTex::SetPosition(D3DXVECTOR3 pos)
{
	CObject2D::SetPosition(pos);
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CPlayerTex::SetSize(float xsize, float ysize)
{
	CObject2D::SetSize(xsize, ysize);
}