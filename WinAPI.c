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
	WndClass.lpszClassName = "win"; // CreateWindowA�� ù ��° ���ڿ��� ������ �̸��� ���ƾ���.
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = WndProc; // ���� ���α׷� �޽��� ť���� ������ ó���ϴ� ������ ���α׷��Ӱ� ���� �������� �ϴµ� �ٷ� �̷��� ����� �ϴ� �Լ��̴�.
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszMenuName = NULL;




	RegisterClassA(&WndClass);


	// �����츦 ����
	CreateWindowA("win", "�ĳĳ�", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 400, 100, NULL, NULL, hinstance, NULL);

		while(GetMessageA(&msg, 0, 0, 0)) // �޽����� �ݺ������� ������. �� �Լ��� ��� �޽���ť���� �޽����� ���� ���� �ִ�.
		{
		TranslateMessage(&msg);
		DispatchMessageA(&msg); // �޽����� �� ������ ������ �Ʒ� �޽��� ó�� �Լ��� ȣ��� �� �ֵ��� Dispatch ���ش�.
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // �޽����� �� ������ �Լ�ó���� �� �ִ� �Լ�
{
	if (uMsg == WM_HOTKEY)
	{
		if (wParam == 1)
		{
			system("start www.twitch.tv/nyangbomnyang");
			PostQuitMessage(0); //�޼��� �ݱ�
		}
		else if (wParam == 0)
		{
			PostQuitMessage(0); //�޼��� �ݱ�
		}
	}
	// �޽����� �߻��� ������ �� �Լ��� ȣ��
	switch (uMsg)
	{
	case WM_CREATE:
		RegisterHotKey(hwnd, 1, 0, VK_F5);
		RegisterHotKey(hwnd, 0, 0, VK_F6);
		CreateWindowA("button", "�ɺ��� ��� ����Ʈ ����(F5)", WS_VISIBLE | WS_CHILD, 40, 15, 200, 40, hwnd, (HMENU)channel_link, g_inst, NULL);
		CreateWindowA("button", "����(F6)", WS_VISIBLE | WS_CHILD, 250, 15, 100, 40, hwnd, (HMENU)shutdown, g_inst, NULL);
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
		PostQuitMessage(0); //�޼��� �ݱ�
	default:
		break;
	}
	return DefWindowProcA(hwnd, uMsg, wParam, lParam); //�⺻���� �޽���(�ִ�, �ּ�ȭ ��)�� �����찡 ��� ���ִ� �Լ�
}