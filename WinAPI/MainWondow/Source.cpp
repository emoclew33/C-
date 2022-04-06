#include <Windows.h>

CONST CHAR g_szClassName[] = "My Window Class"; // global string zero
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	//�������������
	WNDCLASSEX wc;														// window class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));								// �������� ��������� wc
	wc.cbSize = sizeof(WNDCLASSEX);										// �������������� ���� ��������� ������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;											// ������ ��������� ���� ��� ������� ������
	
	wc.style = 0;														// ����� ����, ���������� ��� �������������� ��������.
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	// ������, �� ������ �����
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); // ������, � ������ ��������� (IconSm - icon small)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;												// ID ���� ����, ���� ���� ������� ��� ID �������, ���� ���� ��������. NULL - ���� �����������
	wc.lpszClassName = g_szClassName;

	//�����������
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//�������� ����
	HWND hwnd = CreateWindowEx
		(
			NULL,						  // Ex - style
			g_szClassName,				  // ��� ������ ����
			"Main Window",				  // ��������� ����
			WS_OVERLAPPEDWINDOW,		  // ����� ����. � �������� ���� ���������� ����� ������ WS_OVERLAPPEDWINDOW
			20, 40, // ��������� ����
			640, 480, // ������ ����
			NULL,						  // ������������ ����
			NULL,						  // ����
			hInstance,
			NULL						  // 
		);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);		// ������ ����� �����������
	UpdateWindow(hwnd);				// ���������� ����

	//������ ����� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		if (MessageBox(hwnd, "�� ������������� ������ ������� ����?", "��, �������?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}