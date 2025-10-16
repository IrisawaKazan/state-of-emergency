//==============================================================
//
// [renderer.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"renderer.h"
#include"object.h"
#include"debugproc.h"
#include"manager.h"
#include"game.h"

// �ÓI�����o�ϐ��錾
int CRenderer::m_nCntFPS = NULL;

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apTextureMT[nCnt] = nullptr; // �����_�����O�^�[�Q�b�g�p�e�N�X�`��
		m_apRenderMT[nCnt] = nullptr;  // �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	}

	m_pZBuffMT = nullptr;          // �e�N�X�`�������_�����O�pZ�o�b�t�@
	m_viewportMT = D3DVIEWPORT9(); // �e�N�X�`�������_�����O�p�r���[�|�[�g

	m_pVtxBuffMT = nullptr; // �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CRenderer::~CRenderer()
{

}

//----------------------------------------
// ����������
//----------------------------------------
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        // �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; // �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                          // �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                       // �Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                     // �Q�[����ʂ̃T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;                      // �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                  // �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   // �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;                        // �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  // �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                   // �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   // �C���^�[�o��

	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs�Ȃ�)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_apTextureMT[nCnt],
			NULL);

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
		m_apTextureMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);
	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);

	// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// ���݂�Z�o�b�t�@���擾(�ۑ�)
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
		m_pD3DDevice->GetRenderTarget(0, &m_apRenderMT[nCnt]);
	}

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// Z�o�b�t�@�����ɖ߂�
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 0.0f;

	// �t�B�[�h�o�b�N�p�|���S���̐���
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMT,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT);
	pVtx[2].pos = D3DXVECTOR3(-SCREEN_WIDTH, 0.0f, -SCREEN_HEIGHT);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, -SCREEN_HEIGHT);

	// �e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffMT->Unlock();

	return S_OK;
}

//----------------------------------------
// �I������
//----------------------------------------
void CRenderer::Uninit(void)
{
	CObject::ReleaseAll();

	// Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̔j��
		if (m_apTextureMT[nCnt] != nullptr)
		{
			m_apTextureMT[nCnt]->Release();
			m_apTextureMT[nCnt] = nullptr;
		}

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̔j��
		if (m_apRenderMT[nCnt] != nullptr)
		{
			m_apRenderMT[nCnt]->Release();
			m_apRenderMT[nCnt] = nullptr;
		}
	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̔j��
	if (m_pZBuffMT != nullptr)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = nullptr;
	}

	// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@�̔j��
	if (m_pVtxBuffMT != nullptr)
	{
		m_pVtxBuffMT->Release();
		m_pVtxBuffMT = nullptr;
	}
}

//----------------------------------------
// �X�V����
//----------------------------------------
void CRenderer::Update(void)
{
	// �S�ẴI�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CRenderer::Draw(void)
{

	// ��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �S�ẴI�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

#ifdef _DEBUG

		// FPS���擾
		m_nCntFPS = GetFPS();

		// FPS���f�o�b�O�\��
		CDebugProc::Print("FPS: %d", m_nCntFPS);

		CDebugProc::Draw();

#endif

		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//----------------------------------------
// �擾����
//----------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}