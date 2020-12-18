#include <Windows.h>
#include <stdbool.h>
#include <stdlib.h>

HINSTANCE g_inst;
#define channel_link 100
#define shutdown	 200
#define showWin		 300
MSG msg;
WNDCLASSA WndClass;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int CALLBACK WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WndClass.lpszClassName = "win"; // CreateWindowA의 첫 번째 인자에서 정해준 이름과 같아야함.
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = WndProc; // 응용 프로그램 메시지 큐에서 꺼내서 처리하는 과정을 프로그래머가 직접 만들어줘야 하는데 바로 이러한 기능을 하는 함수이다.
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszMenuName = NULL;




	RegisterClassA(&WndClass);


	// 윈도우를 생성
	CreateWindowA("win", "냐냐냥", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 400, 100, NULL, NULL, hinstance, NULL);

		while(GetMessageA(&msg, 0, 0, 0)) // 메시지를 반복적으로 꺼낸다. 이 함수를 써야 메시지큐에서 메시지를 꺼낼 수가 있다.
		{
		TranslateMessage(&msg);
		DispatchMessageA(&msg); // 메시지가 올 때마다 꺼내서 아래 메시지 처리 함수가 호출될 수 있도록 Dispatch 해준다.
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // 메시지가 올 때마다 함수처리할 수 있는 함수
{
	if (uMsg == WM_HOTKEY)
	{
		if (wParam == 1)
		{
			system("start www.twitch.tv/nyangbomnyang");
			PostQuitMessage(0); //메세지 닫기
		}
		else if (wParam == 0)
		{
			PostQuitMessage(0); //메세지 닫기
		}
	}
	// 메시지가 발생할 때마다 이 함수가 호출
	switch (uMsg)
	{
	case WM_CREATE:
		RegisterHotKey(hwnd, 1, 0, VK_F5);
		RegisterHotKey(hwnd, 0, 0, VK_F6);
		CreateWindowA("button", "냥봄냥 방송 사이트 접속(F5)", WS_VISIBLE | WS_CHILD, 40, 15, 200, 40, hwnd, (HMENU)channel_link, g_inst, NULL);
		CreateWindowA("button", "종료(F6)", WS_VISIBLE | WS_CHILD, 250, 15, 100, 40, hwnd, (HMENU)shutdown, g_inst, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case channel_link:
			system("start www.twitch.tv/teemo_loto");
			break;
		default:
			break;
		}
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0); //메세지 닫기
	default:
		break;
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam); //기본적인 메시지(최대, 최소화 등)를 윈도우가 모두 해주는 함수
}