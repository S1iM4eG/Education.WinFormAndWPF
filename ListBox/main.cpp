#include<Windows.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };

CHAR g_AddText[64] = {};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DlgProc, 0);

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
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		//case IDC_LIST:
		//	if (LOWORD(wParam) == IDC_LIST && HIWORD(wParam) == LBN_DBLCLK)					//Двойное нажатие по элементу
		//	{
		//		HWND hList = GetDlgItem(hwnd, IDC_LIST);
		//		INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);

		//		if (index != LB_ERR)
		//		{
		//			SendMessage(hList, LB_GETTEXT, index, (LPARAM)g_AddText);
		//			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc1, 0); //Вызов окна для редактирования элемента

		//			if (g_AddText[0] != '\0')
		//			{
		//				SendMessage(hList, LB_DELETESTRING, index, 0);					//Удаляем старую строку
		//				SendMessage(hList, LB_INSERTSTRING, index, (LPARAM)g_AddText);  //Вставляем новую строку на место старой
		//			}
		//		}
		//		return TRUE;
		//	}
		//	break;
		case IDC_LIST:
			if (HIWORD(wParam) == LBN_DBLCLK)
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc1, 0);
				break;
		case IDOK:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);

			if (index != CB_ERR)
			{
				CHAR itemText[64], result[64];

				SendMessage(hList, LB_GETTEXT, index, (LPARAM)itemText);
				wsprintf(result, "Выбран элемент №%d со значением: %s", index + 1, itemText);
				MessageBox(hwnd, result, "Информационное окно", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Ни один из элементов не был выбран.", "Информационное окно", MB_OK | MB_ICONERROR);
			}
		}
		break;
		case IDC_ADD:																	//Добавление нового элемента
		{
			ZeroMemory(g_AddText, sizeof(g_AddText));

			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc1, 0); //Вызов окна для ввода нового элемента

			if (g_AddText[0] != '\0')
			{
				HWND hList = GetDlgItem(hwnd, IDC_LIST);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_AddText);
				MessageBox(hwnd, "Элемент добавлен", "Информационное окно", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hwnd, "Элемент не добавлен", "Информационное окно", MB_OK | MB_ICONWARNING);
			}
		}
		break;
		case IDC_DELETE:																//Удаление выбранного элемента
		{
			CHAR itemText[64], result[64];

			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{
				SendMessage(hList, LB_GETTEXT, index, (LPARAM)itemText);
				wsprintf(result, "Удалент элемент №%d со значением: %s", index + 1, itemText);
				SendMessage(hList, LB_DELETESTRING, index, 0);							//Удаление элемента из списка
				MessageBox(hwnd, result, "Информационное окно", MB_OK | MB_ICONWARNING);
			}
			else
			{
				MessageBox(hwnd, "Элемент не выбран", "Ошибка", MB_OK | MB_ICONERROR);
			}
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
BOOL CALLBACK DlgProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
	{
		HICON hIсon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIсon);
	}
	{
		SetDlgItemText(hwnd, IDC_EDIT_ADD, g_AddText);
		return TRUE;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			GetDlgItemText(hwnd, IDC_EDIT_ADD, g_AddText, sizeof(g_AddText));
			if (g_AddText[0] != '\0')
				EndDialog(hwnd, IDOK);
		}
		return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
		HWND hParent = GetParent(hwnd);
		HWND hList = GetDlgItem(hParent, IDC_LIST);
		HWND hEDit = GetDlgItem(hwnd, IDC_EDIT_ADD);
		INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
		CHAR sz_buffer[MAX_PATH] = {};
		SendMessage(hwnd, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}