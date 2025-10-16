//==============================================================
//
// [main.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"main.h"
#include"renderer.h"
#include"object.h"
#include"object2D.h"
#include"manager.h"
#include"input.h"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void FullScreen(HWND hWnd);

// �O���[�o���ϐ��錾
int g_nCntFPS = NULL;
bool g_bFullscreen = false;
RECT g_windowRect = {};

//----------------------------------------
// ���C���֐�
//----------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	hinstancePrev = nullptr;
	lpCmdLine = nullptr;

	CManager* pManager = nullptr;

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),             // WINDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                     // �E�B���h�E�̃X�^�C��
		WindowProc,                     // �E�B���h�E�v���V�[�W��
		0,                              // 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,                              // 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,                      // �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), // �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),     // �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;                                      // �E�B���h�E�n���h��
	MSG msg;                                        // ���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; // ��ʃT�C�Y�̍\����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left), // �E�B���h�E�̕�
		(rect.bottom - rect.top), // �E�B���h�E�̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	// �}�l�[�W���̐���
	pManager = new CManager;

	// �}�l�[�W���̏���������
	pManager->Init(hInstance, hWnd);

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow); // �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);         // �N���C�A���g�̈���X�V

	DWORD dwFrameCount;  // �t���[���J�E���g
	DWORD dwFPSLastTime; // �Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); // ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  // �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();

			if (dwCurrentTime - dwFPSLastTime >= 500)
			{// 0.5�b�o��
				// FPS���v��
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime; // FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;              // �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �}�l�[�W���̍X�V����
				pManager->Update();

				// �}�l�[�W���̕`�揈��
				pManager->Draw();

				dwFrameCount++; // �t���[���J�E���g�����Z
			}
		}
	}

	// �����_���[�̔j��
	if (pManager != nullptr)
	{
		// �I������
		pManager->Uninit();

		delete pManager;

		pManager = nullptr;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//----------------------------------------
// �E�B���h�E�v���V�[�W��
//----------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int nID = NULL;

	switch (uMsg)
	{
	case WM_ACTIVATE:
		return 0L;

	case WM_DESTROY:
		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂��� ?", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd); // �E�B���h�E�j�����b�Z�[�W
			}
			else
			{
				return 0;
			}
			break;

		case VK_F11:
			FullScreen(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------------------------
// �t���X�N���[������
//----------------------------------------
void FullScreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_bFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top, g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top, SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_bFullscreen = !g_bFullscreen;
}

//----------------------------------------
// FPS�̎擾����
//----------------------------------------
int GetFPS(void)
{
	return g_nCntFPS;
}