#include<Windows.h>
#include <winapifamily.h>
#include"resource.h"

CHAR sz_login_invitation[] = "�������� �����";
CHAR sz_password_invitation[] = "�������� ������";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMgs, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(NULL, "HelloWorld", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP
		| MB_DEFBUTTON4 | MB_SYSTEMMODAL
		//| MB_RTLREADING
		|MB_SETFOREGROUND);*/
		//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

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

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);	//�������� ID ���� ���������� ���� �� ����� �������
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//��� ���������� ��������� �������� ��� �����-���� ��������� ���������� (�����),
			//���� ������� ���������� (����) �������� �����������. �����������, ��� ����� ������� ���������.
			//��������, ����� �� ���������� � ��������� ����, �� ��� ��������� ���� �������� ����������� EN_SETFOCUS,
			//����� �� "������" �� ���������� ����, �� ��� �������� ����������� EN_KILLFOCUS.
			//EN - Edit Notification
			//����� - ��� ����� ����, ������� ��������� ������� � ����������.
			
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if(strcmp(sz_buffer, sz_login_invitation) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)""); 
				break;
			case EN_KILLFOCUS:
				if(strlen(sz_buffer) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
				break;
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//�������� ����� �� ���������� ���� Password � sz_buffer
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_BUTTON_SET_TITLE:
		{
			
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//SendMessage(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "���� ������ ������ OK", "Info", MB_OK | MB_ICONWARNING); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}