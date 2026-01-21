//==============================================================
//
// [fade.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"fade.h"
#include"renderer.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CFade::CFade()
{
	m_pVtxBuff = nullptr;
	m_fade = FADE_NONE;
	m_modeNext = CScene::MODE_TITLE;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CFade::~CFade()
{

}

//----------------------------------------
// 初期化処理
//----------------------------------------
HRESULT CFade::Init(CScene::MODE modeNext)
{
	m_fade = FADE_IN;                            // フェードイン状態に
	m_modeNext = modeNext;                       // 次の画面(モード)にしておく
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // 黒いポリゴン(不透明)にしておく

	// 種類の設定処理
	CObject::SetType(TYPE_FADE);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// モードの設定
	CManager::SetMode(m_modeNext);

	return S_OK;
}

//----------------------------------------
// 終了処理
//----------------------------------------
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//----------------------------------------
// 更新処理
//----------------------------------------
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{// フェードイン状態
			m_color.a -= 0.05f; // ポリゴンを透明にしていく

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE; // 何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_color.a += 0.05f; // ポリゴンを不透明にしていく

			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_fade = FADE_IN; // フェードイン状態に

				// モード設定(次の画面に移行)
				CManager::SetMode(m_modeNext);
			}
		}

		VERTEX_2D* pVtx;

		// 頂点バッファをロックし,頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラーの設定
		pVtx[0].col = m_color;
		pVtx[1].col = m_color;
		pVtx[2].col = m_color;
		pVtx[3].col = m_color;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//----------------------------------------
// 描画処理
//----------------------------------------
void CFade::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//----------------------------------------
// 設定処理
//----------------------------------------
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;                           // フェードアウト状態に
	m_modeNext = modeNext;                       // 次の画面(モード)を設定
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); // 黒いポリゴン(透明)にしておく
}

//----------------------------------------
// 取得処理
//----------------------------------------
CFade::FADE CFade::Get(void)
{
	return m_fade;
}