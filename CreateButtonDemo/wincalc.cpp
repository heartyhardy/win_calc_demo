#include <Windows.h>
#include <wchar.h>
#include <string>

enum CURRENT_OPERAND
{
	CURRENT_OP_LEFT = 1,
	CURRENT_OP_RIGHT = 2,
};

enum Operation
{
	OP_NONE,
	OP_ADD,
	OP_SUBSTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
};

HWND textHandler = 0;
WCHAR wcOpLeft[20];
WCHAR wcOpRight[20];
int nCurrentOperand = CURRENT_OP_LEFT;
int nCurrentOperator = OP_NONE;
int nEndLeft = 1;
int nEndRight = 1;

void ResetToLeftOperand();
int GetArrLenW(WCHAR input[]);
int GetArrEndPos(WCHAR input[]);
long ToInt(WCHAR input[], const int size);

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

	wcOpLeft[0] = '0';
	wcOpLeft[1] = '\0';
	wcOpRight[0] = '0';
	wcOpRight[1] = '\0';

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
			if (nEndLeft >= 19 || nEndRight >= 19) {
				return 0;
			}

			SetWindowText(textHandler, 0);

			WCHAR num[2];
			swprintf_s(num, 2, L"%d", hMenuID);
			if (nCurrentOperand == CURRENT_OP_LEFT) {
				if (wcOpLeft[0] == '0') {
					wcOpLeft[0] = num[0];
					wcOpLeft[1] = '\0';
				}
				else {
					wcOpLeft[nEndLeft + 1] = '\0';
					wcOpLeft[nEndLeft] = num[0];
					nEndLeft++;
				}

				SetWindowTextW(textHandler, wcOpLeft);

			}
			else if (nCurrentOperand == CURRENT_OP_RIGHT) {
				if (wcOpRight[0] == '0') {
					wcOpRight[0] = num[0];
					wcOpRight[1] = '\0';
				}
				else {
					wcOpRight[nEndRight + 1] = '\0';
					wcOpRight[nEndRight] = num[0];
					nEndRight++;
				}

				SetWindowTextW(textHandler, wcOpRight);
			}

		}
		break;
		case 15:
			if (nCurrentOperand == CURRENT_OP_LEFT) {
				nCurrentOperand = CURRENT_OP_RIGHT;
				nCurrentOperator = OP_ADD;
			}
			else if (nCurrentOperand == CURRENT_OP_RIGHT) {
				switch (nCurrentOperator) {
				case OP_ADD:
					long nLeft = ToInt(wcOpLeft, GetArrLenW(wcOpLeft));
					long nRight = ToInt(wcOpRight, GetArrLenW(wcOpRight));

					long nResult = nLeft + nRight;

					//WCHAR buffLen[20];
					//wsprintf(buffLen, L"%ld", GetArrLenW(wcOpLeft));
					//MessageBox(hWnd, buffLen, TEXT("test"), 1);

					//WCHAR buff2_1[20];
					//wsprintf(buff2_1, L"%ld", nLeft);
					//MessageBox(hWnd, buff2_1, TEXT("test"), 1);

					//WCHAR buff2_2[20];
					//wsprintf(buff2_2, L"%ld", nRight);
					//MessageBox(hWnd, buff2_2, TEXT("test"), 1);

					wsprintf(wcOpLeft, L"%ld", nResult);

					ResetToLeftOperand();

					SetWindowText(textHandler, wcOpLeft);

					break;
				}
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


long ToInt(WCHAR input[], const int size) {
	WCHAR* wcToNum = new WCHAR(size);

	for (size_t i = 0; i < size; i++) {
		wcToNum[i] = input[i];
	}

	long numOperand = _wtol(wcToNum);
	return numOperand;
}

int GetArrLenW(WCHAR input[]) {
	int nSize = sizeof(input);
	return nSize;
}

int GetArrEndPos(WCHAR input[]) {
	for (size_t i = 0; i < GetArrLenW(input); i++) {
		if (input[i] == '\0') {
			return i;
		}
	}
	return GetArrLenW(input);
}

void ResetToLeftOperand() {
	wcOpRight[0] = '0';
	wcOpRight[1] = '\0';
	nEndLeft = GetArrEndPos(wcOpLeft) + 1;
	nEndRight = 1;
	nCurrentOperand = CURRENT_OP_LEFT;
	nCurrentOperator = OP_NONE;
}

/*
	TEST:

	WCHAR buff2_1[20];
	wsprintf(buff2_1, L"%ld", nLeft);
	MessageBox(hWnd, buff2_1, TEXT("test"), 1);

	WCHAR buff2_2[20];
	wsprintf(buff2_2, L"%ld", nRight);
	MessageBox(hWnd, buff2_2, TEXT("test"), 1);
*/