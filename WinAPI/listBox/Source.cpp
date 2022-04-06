#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <winapifamily.h>
#include "resource.h"

CONST CHAR* string[] =
{
	"this", "is", "my", "first", "list", "box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Это сообщение отправляется в окно при его создании
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
	}
	break;
	case WM_COMMAND:	//Это сообщение обрабатывает нажатие на кнопки, и другие элементы интерфейса окна
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 246;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};
			
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент № %d со значением \"%s\"", index+1, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}



//type name(parameters);
//type calling_convertion name(parameters);
//type - тип возвращаемого значения: bool, char, int
//calling_convention - конвенция вызовов (соглашение о вызове функции):
//_syscall
//_stdcall - WinAPI
// _fastcall - x64
// _cdecl - С/C++
// конфенция вызовов определяет порядок вызова функции:
//	 - кто очищает стек, вызывающая функция(caller) или вызываемая функция (callee)
//	 - как читается список передоваемых параметров - слева направо или справа налево. Или же параметры передаются через регистры(_fastcall).
//  
// HWND - handler to window. ОБРАБОТЧИК ОКНА, дескриптор окна. Индефикатор окна, через который можно к нему обратиться. 
// UINT uMsg - message  , UINT - unsigned int
// LPARAM - 
// WPARAM -  параметры сообщения, зависят от того какое имено uMsg передаем окну
//

