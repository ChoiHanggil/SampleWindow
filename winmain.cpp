#include<Windows.h>
// 원도우 API 코딩 스타일
// 함수 : 파스칼(단어의 시작을 대문자로)
// 변수 : 헝가리언 표기법( 변수의 타입 약자를 접두어 )

//int WinMain(p1, p2, p3, p4)
//WINAPI : Windouw Application Progaramming Interface
//_IN_, _IN_opt_, _Out_ : SAL(Sourcecode Annotation Language)
//HINSTANCE : Handle Of Instance (Pointer to Instance) 실행되는 인스턴스를 가르키는 포인터
//LPSTR : Long Pointer Null-Terminated STR (Suspend to RAM)
//


// 1. 윈도우 클래스 등록
// 2. 윈도우 생성
// 3. 원도우 메시지 처리
// 4. 윈도우 프로시져 작성
//

const wchar_t MY_CLASS_NAME[]{ L"MyWindowClass" };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,			//*OS가 실행한 앱의 인스턴스 핸들
	_In_opt_ HINSTANCE hPrevInstance,	//이전에 실행한 앱의 인스턴스 핸들
	_In_ LPSTR lpCmdLine,				//명령줄 CommandLine
	_In_ int nShowCmd)					//int Show Command 
{
	// HWND : Handle of WiNDow
	// LPCTSTR : Long Pointer Constant Tchar STRing
	// L 접두어 문자일 : Wide Character Literal
	//auto ret = MessageBox(nullptr, L"Hello, World!", L"SimpleWindow", MB_ICONEXCLAMATION|MB_YESNO);

	//if (ret == IDYES)
	//{
	//	MessageBox(nullptr, L"Yes", L"Result", MB_OK);
	//}
	//else if (ret == IDNO)
	//{
	//	MessageBox(nullptr, L"No", L"Result", MB_OK);
	//}

	// 1. 윈도우 클래스 등록
	WNDCLASSEX wc{};
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //C언어

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

	//2. 윈도우 생성
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
	
	//3. 메시지 처리
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//4.윈도우 프로시저 저의
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
