//==============================================================
//
// [debugproc.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"debugproc.h"
#include"manager.h"
#include"renderer.h"

// �ÓI�����o�ϐ��錾
LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_aStr[MAX_CHARACTER] = {};

//----------------------------------------
// �R���X�g���N�^
//----------------------------------------
CDebugProc::CDebugProc()
{

}

//----------------------------------------
// �f�X�g���N�^
//----------------------------------------
CDebugProc::~CDebugProc()
{

}

//----------------------------------------
// ����������
//----------------------------------------
void CDebugProc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &m_pFont);
}

//----------------------------------------
// �I������
//----------------------------------------
void CDebugProc::Uninit(void)
{
	// �f�o�b�O�\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//----------------------------------------
// printf
//----------------------------------------
void CDebugProc::Print(const char* fint, ...)
{
	va_list args; // va_list�}�N�����g�p

	va_start(args, fint);

	vsprintf_s(m_aStr, fint, args); // vsprintf���g�p����ꍇ�� #define _CRT_SECURE_WARNINGS

	va_end(args);
}

//----------------------------------------
// �`�揈��
//----------------------------------------
void CDebugProc::Draw(void)
{
	RECT rect = { 5 /* X���W�̈ʒu */,5 /* Y���W�̈ʒu */,SCREEN_WIDTH,SCREEN_HEIGHT };

	m_pFont->DrawTextA(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 255, 255));
}