#include<Windows.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIсon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIсon);
	}
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

			if (index != CB_ERR)
			{
				char itemText[64], result[64];

				SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)itemText);
				wsprintf(result, "Выбран элемент №%d со значением: %s",	index + 1, itemText);
				MessageBox(hwnd, result, "Информационное окно", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Ни один из элементов не был выбран.", "Информационное окно", MB_OK | MB_ICONERROR);
			}
			EndDialog(hwnd, 0);
		}
		break;

		case IDCANCEL: 
			MessageBox(hwnd, "Была нажата кнопка \"CANCEL\"", "Информационное окно", MB_OK | MB_ICONSTOP);
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}