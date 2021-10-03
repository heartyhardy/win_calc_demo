#include <Windows.h>
#include <wchar.h>

HWND textHandler = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	WNDCLASS wc = {};
	wc.lpszClassName = TEXT("ButtonsDemo");
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		TEXT("Calculator"),
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT, 310, 350,

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}

void CreateButton(HWND hWndParent, LPCWSTR lpCaption, int x, int y, int nHeight, int nWidth, int nMenu) {
	CreateWindow(
		TEXT("button"),
		lpCaption,
		WS_VISIBLE | WS_CHILD,

		x, y, nWidth, nHeight,

		hWndParent,
		(HMENU)nMenu,
		NULL,
		NULL
	);
}

HWND CreateText(HWND hWndParent, LPCWSTR lpCaption, int x, int y, int nHeight, int nWidth, int nMenu) {
	HWND handler = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		TEXT("edit"),
		lpCaption,
		WS_VISIBLE | WS_CHILD | ES_READONLY,

		x, y, nWidth, nHeight,

		hWndParent,
		(HMENU)nMenu,
		NULL,
		NULL
	);
	return handler;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_CREATE:
	{
		CreateButton(hWnd, TEXT("7"), 10, 70, 50, 60, 7);
		CreateButton(hWnd, TEXT("8"), 80, 70, 50, 60, 8);
		CreateButton(hWnd, TEXT("9"), 150, 70, 50, 60, 9);

		CreateButton(hWnd, TEXT("4"), 10, 130, 50, 60, 4);
		CreateButton(hWnd, TEXT("5"), 80, 130, 50, 60, 5);
		CreateButton(hWnd, TEXT("6"), 150, 130, 50, 60, 6);

		CreateButton(hWnd, TEXT("3"), 10, 190, 50, 60, 3);
		CreateButton(hWnd, TEXT("2"), 80, 190, 50, 60, 2);
		CreateButton(hWnd, TEXT("1"), 150, 190, 50, 60, 1);

		CreateButton(hWnd, TEXT("0"), 10, 250, 50, 60, 0);
		CreateButton(hWnd, TEXT("."), 80, 250, 50, 60, 10);
		CreateButton(hWnd, TEXT("="), 150, 250, 50, 60, 11);

		CreateButton(hWnd, TEXT("÷"), 220, 70, 50, 60, 12);
		CreateButton(hWnd, TEXT("×"), 220, 130, 50, 60, 13);
		CreateButton(hWnd, TEXT("-"), 220, 190, 50, 60, 14);
		CreateButton(hWnd, TEXT("+"), 220, 250, 50, 60, 15);

		textHandler = CreateText(hWnd, TEXT("0"), 10, 10, 50, 270, 16);

		break;
	}

	case WM_COMMAND:
	{

		WORD hMenuID = LOWORD(wParam);
		//WCHAR wcMenuID[50];
		//swprintf_s(wcMenuID, 50, L"Button With ID: %d Clicked!", hMenuID);

		//if (hMenuID <= 15) {
		//	MessageBox(hWnd, wcMenuID, TEXT("Buttons Demo"), MB_ICONINFORMATION);
		//}

		//int txt_len = GetWindowTextLengthA(textHandler);
		//WCHAR wcHWND[50];
		//swprintf_s(wcHWND, 50, L"Text len is: %d", txt_len);
		//MessageBox(hWnd, wcHWND, TEXT("Buttons Demo"), MB_ICONINFORMATION);

		switch (hMenuID) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		{
			WCHAR num0[2];
			swprintf_s(num0, 2, L"%d", hMenuID);
			SetWindowTextW(textHandler, num0);
		}
		break;
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}