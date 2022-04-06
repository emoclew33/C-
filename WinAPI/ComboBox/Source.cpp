#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>
#include <winapifamily.h>
#include "resource.h"

CONST CHAR* string[] =
{
	"English", "Russian", "French"
};

CHAR sz_language[] = "Выбирите язык";

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
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)string[i]);
		}

		SendMessage(hComboBox, WM_SETTEXT, 0, (LPARAM)sz_language);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};

			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, " Язык приложения будет -  %s . Вы подтверждаете?", sz_buffer);
			MessageBox(hwnd, sz_message, "language", MB_YESNO | MB_ICONQUESTION);
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hwnd, 0);
		}
		break;
		}
	}
	break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}