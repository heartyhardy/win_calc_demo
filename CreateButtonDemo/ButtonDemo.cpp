//#include <windows.h>
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG  msg;
//	WNDCLASS wc = { 0 };
//	wc.lpszClassName = TEXT("Buttons");
//	wc.hInstance = hInstance;
//	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
//	wc.lpfnWndProc = WndProc;
//	wc.hCursor = LoadCursor(0, IDC_ARROW);
//
//
//	RegisterClass(&wc);
//	CreateWindow(wc.lpszClassName, TEXT("Buttons"),
//		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
//		150, 150, 230, 150, 0, 0, hInstance, 0);
//
//	while (GetMessage(&msg, NULL, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return (int)msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//
//
//	switch (msg)
//	{
//	case WM_CREATE:
//	{
//		CreateWindow(TEXT("button"), TEXT("Beep"),
//			WS_VISIBLE | WS_CHILD,
//			20, 50, 80, 25,
//			hwnd, (HMENU)1, NULL, NULL);
//
//		CreateWindow(TEXT("button"), TEXT("Quit"),
//			WS_VISIBLE | WS_CHILD,
//			120, 50, 80, 25,
//			hwnd, (HMENU)2, NULL, NULL);
//		break;
//	}
//
//	case WM_COMMAND:
//	{
//		if (LOWORD(wParam) == 1) {
//			Beep(40, 50);
//		}
//
//		if (LOWORD(wParam) == 2) {
//			PostQuitMessage(0);
//		}
//
//		break;
//	}
//
//	case WM_DESTROY:
//	{
//		PostQuitMessage(0);
//		break;
//	}
//	}
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}