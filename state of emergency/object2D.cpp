//==============================================================
//
// [object2D.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"object2D.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

// 静的メンバ変数宣言


//----------------------------------------
// コンストラクタ
//----------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_faUV = 0.0f;
	m_fzUV = 0.0f;
	m_fxSize = 0.0f;
	m_fySize = 0.0f;
	m_nCounterAnim = NULL;
	m_nPatternAnim = NULL;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CObject2D::~CObject2D()
{

}

//----------------------------------------
// 生成処理
//----------------------------------------
CObject2D* CObject2D::Create(void)
{
	CObject2D* pObject2D;

	// オブジェクト2Dの生成
	pObject2D = new CObject2D;

	// 初期化処理
	pObject2D->Init();

	return pObject2D;
}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CObject2D::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx; // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_faUV, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_fzUV);
	pVtx[3].tex = D3DXVECTOR2(m_faUV, m_fzUV);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CObject2D::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// オブジェクト(自分自身)の破棄
	this->Release();
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CObject2D::Update(void)
{
	VERTEX_2D* pVtx; // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	m_fLength = sqrtf(m_fxSize * m_fxSize + m_fySize * m_fySize) / 2.0f;

	// 対角線の角度を算出する
	m_fAngle = atan2f(m_fxSize, m_fySize);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CObject2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
// 位置の設定処理
//----------------------------------------
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//----------------------------------------
// テクスチャの設定処理
//----------------------------------------
void CObject2D::SetUV(float aUV, float zUV)
{
	m_faUV = aUV;
	m_fzUV = zUV;
}

//----------------------------------------
// サイズの設定処理
//----------------------------------------
void CObject2D::SetSize(float xsize, float ysize)
{
	m_fxSize = xsize;
	m_fySize = ysize;
}

//----------------------------------------
// エフェクトの設定処理
//----------------------------------------
void CObject2D::SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fRedius, pos.y - fRedius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fRedius, pos.y - fRedius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fRedius, pos.y + fRedius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fRedius, pos.y + fRedius, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//----------------------------------------
// テクスチャアニメーションの処理
//----------------------------------------
void CObject2D::TextureAnimation(int texposx, int animspeed)
{
	float OffSetX = 1.0f / texposx;

	m_nCounterAnim++; // カウンターを計算

	VERTEX_2D* pVtx; // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// アニメーション
	if ((m_nCounterAnim % animspeed) == 0)
	{
		m_nCounterAnim = 0;                              // カウンターを初期値に戻す

		m_nPatternAnim = (m_nPatternAnim + 1) % texposx; // パターンNo.を更新する

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX + OffSetX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * OffSetX + OffSetX, 1.0f);
	}
}

//----------------------------------------
// 位置の取得処理
//----------------------------------------
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//----------------------------------------
// アニメーションパターンの取得処理
//----------------------------------------
int CObject2D::GetPtAnim(void)
{
	return m_nPatternAnim;
}

//----------------------------------------
// アニメーションカウンターの取得処理
//----------------------------------------
int CObject2D::GetCntAnim(void)
{
	return m_nCounterAnim;
}

//----------------------------------------
// テクスチャの割り当て
//----------------------------------------
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}