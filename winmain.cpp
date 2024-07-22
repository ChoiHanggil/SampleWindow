#include<Windows.h>
// ������ API �ڵ� ��Ÿ��
// �Լ� : �Ľ�Į(�ܾ��� ������ �빮�ڷ�)
// ���� : �밡���� ǥ���( ������ Ÿ�� ���ڸ� ���ξ� )

//int WinMain(p1, p2, p3, p4)
//WINAPI : Windouw Application Progaramming Interface
//_IN_, _IN_opt_, _Out_ : SAL(Sourcecode Annotation Language)
//HINSTANCE : Handle Of Instance (Pointer to Instance) ����Ǵ� �ν��Ͻ��� ����Ű�� ������
//LPSTR : Long Pointer Null-Terminated STR (Suspend to RAM)
//


// 1. ������ Ŭ���� ���
// 2. ������ ����
// 3. ������ �޽��� ó��
// 4. ������ ���ν��� �ۼ�
//

const wchar_t MY_CLASS_NAME[]{ L"MyWindowClass" };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,			//*OS�� ������ ���� �ν��Ͻ� �ڵ�
	_In_opt_ HINSTANCE hPrevInstance,	//������ ������ ���� �ν��Ͻ� �ڵ�
	_In_ LPSTR lpCmdLine,				//����� CommandLine
	_In_ int nShowCmd)					//int Show Command 
{
	// HWND : Handle of WiNDow
	// LPCTSTR : Long Pointer Constant Tchar STRing
	// L ���ξ� ������ : Wide Character Literal
	//auto ret = MessageBox(nullptr, L"Hello, World!", L"SimpleWindow", MB_ICONEXCLAMATION|MB_YESNO);

	//if (ret == IDYES)
	//{
	//	MessageBox(nullptr, L"Yes", L"Result", MB_OK);
	//}
	//else if (ret == IDNO)
	//{
	//	MessageBox(nullptr, L"No", L"Result", MB_OK);
	//}

	// 1. ������ Ŭ���� ���
	WNDCLASSEX wc{};
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //C���

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = MY_CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to RegisterClassEx()", nullptr, MB_OK);
		return 0;
	}

	//2. ������ ����
	HWND hWnd;
	hWnd = CreateWindowEx(
		0,
		MY_CLASS_NAME,
		L"Hello World",
		WS_OVERLAPPEDWINDOW,
		0,0,
		600,400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindowEx()", nullptr, MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	
	//3. �޽��� ó��
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//4.������ ���ν��� ����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMessage, wParam, lParam);
	}

	return 0;
}
