#include "MainMenu.h"  
#include <windows.h>
#include "resource.h"  //Подключаем ресусрс

cont_question Box_Quest;

/*Макрос для нормальной кнопки, по умолчанию win98*/
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


/*Основные окна*/
HINSTANCE hNew_Q, hFile, hRead, hTest, hSave;/*Объявляем окна для поля ввода*/
/*ОКНО НОВОГО ВОПРОСА*/
HWND hwndQ, hwndTrue, hwndFalsem, hwndComment; //окна для создания вопроса
/*ОКНО ОТКРЫТИЯ ФАЙЛА*/
HWND hwndNameFile; //окно для ввода имяни файла

/*ОКНО просмотра*/
HWND hList;
/*ОКНО СОХРАНЕНИЯ ФАЙЛА*/
HWND hwndNameSave, hwndHead; //окно для ввода имяни сохраняемого файла 



BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DlgProc_new(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_file(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Read(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Test(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Save(HWND, UINT, WPARAM, LPARAM);

// Функция WinAPI для точки входа в программу
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDM_DIALOG), 0, (DlgProc), 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		HICON hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 1, (LPARAM)hIcon1);

		hNew_Q = GetModuleHandle(NULL); 
		hFile = GetModuleHandle(NULL);
		hRead = GetModuleHandle(NULL);
		hTest = GetModuleHandle(NULL);
		hSave = GetModuleHandle(NULL);
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		switch (LOWORD(wParam))
		{
		case IDM_NEW:
			DialogBoxParam(hNew_Q, MAKEINTRESOURCE(IDN_DIALOG), hwnd, DlgProc_new, 0);
			//MessageBox(hwnd, "Была нажата кнопка добавить впосрос", "это перовое", MB_OK | MB_ICONINFORMATION);
			break;
		case IDM_ADDFILE:
			DialogBoxParam(hFile, MAKEINTRESOURCE(IDF_DIALOG), hwnd, DlgProc_file, 0);
			//MessageBox(hwnd, "Была нажата кнопка добавить впосрос", "это перовое", MB_OK | MB_ICONINFORMATION);
			break;
		case IDM_READ:
			DialogBoxParam(hRead, MAKEINTRESOURCE(IDR_DIALOG), hwnd, DlgProc_Read, 0);
			break;
		case IDM_TECT:
			MessageBox(hwnd, "Была нажата кнопка TECT (Но я пока не разобрался с чекбоксами)", "ИНФО", MB_OK | MB_ICONINFORMATION);
			break;
		case IDM_SAVE:		
			DialogBoxParam(hSave, MAKEINTRESOURCE(IDS_DIALOG), hwnd, DlgProc_Save, 0);
			//MessageBox(hwnd, "Была нажата кнопка SAVE", "info", MB_OK | MB_ICONINFORMATION);
			break;
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return FALSE;
}


BOOL CALLBACK DlgProc_new(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		/*к текстовым окнам привязываем их ид, и связь с главным окном */
		hwndQ = GetDlgItem(hwnd, IDN_ENEW);
		hwndTrue = GetDlgItem(hwnd, IDN_ETRUE);
		hwndFalsem = GetDlgItem(hwnd, IDN_EFALSE);
		hwndComment = GetDlgItem(hwnd, IDN_ECOMMENT);
		/*Посылаем текст в текстовое поле hEdit1*/
		SendMessage(hwndQ, WM_SETTEXT, 0, (LPARAM)"Введите вопрос");
		SendMessage(hwndTrue, WM_SETTEXT, 0, (LPARAM)"Введите правильные ответы, каждый ответ с новой строки");
		SendMessage(hwndFalsem, WM_SETTEXT, 0, (LPARAM)"Введите не правильные ответы, каждый ответ с новой строки");
		SendMessage(hwndComment, WM_SETTEXT, 0, (LPARAM)"Введите коментарий");
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		switch (LOWORD(wParam))
		{			
		case IDN_NEXT:
			char* text;
			text = new char[255];			
			GetDlgItemText(hwnd, IDN_ENEW, (LPSTR)text, 255);
			//GetWindowText(hwndQ, (LPSTR)text,255);/*Вариант 2*/
			//SendMessage(hwndQ, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameC() = text;
			delete[] text;
			
			
			
			MessageBox(hwnd, "Вопрос был сохранен", "ИНФО", MB_OK | MB_ICONINFORMATION);
			EndDialog(hwnd, 0);
			return TRUE;
			//DialogBoxParam(hNew_Q, MAKEINTRESOURCE(IDN_DIALOG), hwnd, DlgProc_new, 0);
			
			break;	
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_file(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		/*к текстовым окнам привязываем их ид, и связь с главным окном */
		hwndNameFile = GetDlgItem(hwnd, IDF_NAMEFILE);
		/*Посылаем текст в текстовое поле hEdit1*/
		SendMessage(hwndNameFile, WM_SETTEXT, 0, (LPARAM)"Name.html");
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		switch (LOWORD(wParam))
		{
		case IDF_OPEN:
			char* text = new char[255];
		
			SendMessage(hwndNameFile, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameF() = text;
			delete[] text;

			std::string messege = Box_Quest.find_file();
			MessageBox(hwnd, messege.c_str(), "ИНФО", NULL);
			EndDialog(hwnd, 0);
			return TRUE;	
			break;
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_Read(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		
		
		hList = GetDlgItem(hwnd, IDR_LIST);
		for (int i = 0; i < Box_Quest.SIZE_BOX(); i++) {
			//std::string temp = std::to_string(i)+". ";
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Box_Quest.print_quest(i).c_str());
		}		
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		switch (LOWORD(wParam))
		{
		case IDR_LIST:		
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
								
				CHAR str_2[255];
				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str_2);
			
				MessageBox(hwnd, str_2, "info", NULL);
			}		
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}



BOOL CALLBACK DlgProc_Save(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		/*к текстовым окнам привязываем их ид, и связь с главным окном */
		hwndHead = GetDlgItem(hwnd, IDS_ENAMHEAD);
		hwndNameFile = GetDlgItem(hwnd, IDS_ENAMESAVE2);
		/*Посылаем текст в текстовое поле hEdit1*/
		SendMessage(hwndHead, WM_SETTEXT, 0, (LPARAM)"Заголовок для вопросов");
		SendMessage(hwndNameFile, WM_SETTEXT, 0, (LPARAM)"Имя_файла_не_должно_содержать_пробелы");
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		char* text;
		switch (LOWORD(wParam))
		{
		case IDS_TXT:
			text = new char[255];
			SendMessage(hwndHead, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameC() = text;
			delete[] text;

			text = new char[255];
			SendMessage(hwndNameFile, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameF() = text;
			delete[] text;

			Box_Quest.save_fileTXT();
			MessageBox(hwnd, "Сохраняем как тхт", "ИНФО", MB_OK | MB_ICONINFORMATION);
			EndDialog(hwnd, 0);
			return TRUE;
			break;

		case IDS_HTML:		
			text = new char[255];
			SendMessage(hwndHead, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameC() = text;
			delete[] text;
			
			text = new char[255];
			SendMessage(hwndNameFile, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameF() = text;
			delete[] text;

			Box_Quest.save_fileHTML();
			MessageBox(hwnd, "Сохраняем как хтмл", "ИНФО", MB_OK | MB_ICONINFORMATION);
			EndDialog(hwnd, 0);
			return TRUE;			
			break;			
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}