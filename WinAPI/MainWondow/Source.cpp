#include <Windows.h>

CONST CHAR g_szClassName[] = "My Window Class"; // global string zero
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	//ИНИЦИАЛИЗАЦИЯ
	WNDCLASSEX wc;														// window class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));								// зануляем экземпляр wc
	wc.cbSize = sizeof(WNDCLASSEX);										// инициализируем поля структуры данных
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;											// задаем процедуру окна для данного класса
	
	wc.style = 0;														// стиль окна, определяет его дополнительные свойства.
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	// иконка, на панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); // иконка, в строке заголовка (IconSm - icon small)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;												// ID меню окна, если окно главное или ID ресурса, если окно дочернее. NULL - меню отсутствует
	wc.lpszClassName = g_szClassName;

	//РЕГИСТРАЦИЯ
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//СОЗДАНИЕ ОКНА
	int width = GetSystemMetrics(SM_CXSCREEN) - 100;
	int height = GetSystemMetrics(SM_CYSCREEN) - 100;
	HWND hwnd = CreateWindowEx
		(
			NULL,						  // Ex - style
			g_szClassName,				  // имя класса окна
			"Main Window",				  // заголовок окна
			WS_OVERLAPPEDWINDOW,		  // стиль окна. У главного окна приложения стиль всегда WS_OVERLAPPEDWINDOW
			(GetSystemMetrics(SM_CXSCREEN) >> 1) - ((width >> 1)),
			(GetSystemMetrics(SM_CYSCREEN) >> 1) - ((height >> 1)), // размер окна
			width, height,
			NULL,						  // родительское окно
			NULL,						  // окна
			hInstance,
			NULL						  // 
		);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);		// задаем режим отображения
	UpdateWindow(hwnd);				// прорисовка окна

	//ЗАПУСК ЦИКЛА СООБЩЕНИЙ
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
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Шо, внатуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
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