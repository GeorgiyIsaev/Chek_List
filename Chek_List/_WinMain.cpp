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
HINSTANCE h_Re_read;
HWND hList; HWND hwnd_redact;
/*ОКНО СОХРАНЕНИЯ ФАЙЛА*/
HWND hwndNameSave, hwndHead; //окно для ввода имяни сохраняемого файла 



BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DlgProc_new(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_file(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Read(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Redact(HWND, UINT, WPARAM, LPARAM);
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
		SendMessage(hwndTrue, WM_SETTEXT, 0, (LPARAM)"Введите ПРАВИЛЬНЫЕ ответы.\r\nКаждый ответ вводится с новой строки\r\nНовая строка->(CTRL+ENTER)");
		SendMessage(hwndFalsem, WM_SETTEXT, 0, (LPARAM)"Введите НЕ ПРАВИЛЬНЫЕ ответы\r\nКаждый ответ вводится с новой строки\r\nНовая строка->(CTRL+ENTER)");
		SendMessage(hwndComment, WM_SETTEXT, 0, (LPARAM)"Введите коментарий\r\n\r\n (*Не обязательное поле), можно оставить пустым!");
		break;
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		switch (LOWORD(wParam))
		{			
		case IDN_NEXT:
			
			//GetDlgItemText(hwndQ, IDN_ENEW, (LPSTR)text, 1024);
			//SendMessage(hwndQ, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			int sizeCHAR = 2047;
			char* quest = new char[sizeCHAR];
			SendMessage(hwndQ, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)quest);		
			char* Answer = new char[sizeCHAR];
			SendMessage(hwndTrue, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)Answer);		
			char* AnAnswer = new char[sizeCHAR];
			SendMessage(hwndFalsem, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)AnAnswer);
			char* Comment = new char[sizeCHAR];
			SendMessage(hwndComment, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)Comment);
					
			Box_Quest.new_question(quest, Answer, AnAnswer, Comment);
			delete[] quest; delete[] Answer; delete[] AnAnswer; delete[] Comment;
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
		
		h_Re_read = GetModuleHandle(NULL);
		
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
				Box_Quest.It_this(i);
				hwnd_redact = CreateDialog(h_Re_read, MAKEINTRESOURCE(IDR_DIALOG_RECORD), 0, DlgProc_Redact);
				ShowWindow(hwnd_redact, SW_SHOW);

				//SendMessage(hList, LB_GETTEXT, i, (LPARAM)str_2);
				//MessageBox(hwnd, str_2, "info", NULL);
			}		
		}
		break;
	case WM_CLOSE:		//Обработка закрытия окна пользователя
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_Redact(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //Обработчик сообщений
	{
	case WM_INITDIALOG:
	{
		int sizeCHAR = 2048;
		/*к текстовым окнам привязываем их ид, и связь с главным окном */
		hwndQ = GetDlgItem(hwnd, IDR_ENEW);
		hwndTrue = GetDlgItem(hwnd, IDR_ETRUE);
		hwndFalsem = GetDlgItem(hwnd, IDR_EFALSE);
		hwndComment = GetDlgItem(hwnd, IDR_ECOMMENT);
		/*Посылаем текст в текстовое поле hEdit1*/
		char* quest = new char[sizeCHAR];
		strcpy_s(quest, sizeCHAR, Box_Quest.getQuest().c_str());
		SendMessage(hwndQ, WM_SETTEXT, 0, (LPARAM)quest);
		char* Answer = new char[sizeCHAR];
		strcpy_s(Answer, sizeCHAR, Box_Quest.getAnswer().c_str());
		SendMessage(hwndTrue, WM_SETTEXT, 0, (LPARAM)Answer);
		char* AnAnswer = new char[sizeCHAR];
		strcpy_s(AnAnswer, sizeCHAR, Box_Quest.getAnAnswer().c_str());
		SendMessage(hwndFalsem, WM_SETTEXT, 0, (LPARAM)AnAnswer);
		char* Comment = new char[sizeCHAR];
		strcpy_s(Comment, sizeCHAR, Box_Quest.getComment().c_str());
		SendMessage(hwndComment, WM_SETTEXT, 0, (LPARAM)Comment);
		break;		
	}
	case WM_COMMAND:	//Обработчик команд кнопок, поле ввода и т.д.
		char* text;
		switch (LOWORD(wParam))
		{
		case IDR_DELETE:
			Box_Quest.dell_question();
			EndDialog(hwnd, 0);
			return TRUE;
			break;
		case IDR_SAVE_QUEST:	
			Box_Quest.dell_question();
			int sizeCHAR = 1023;
			char* quest = new char[sizeCHAR];
			SendMessage(hwndQ, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)quest);
			char* Answer = new char[sizeCHAR];
			SendMessage(hwndTrue, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)Answer);
			char* AnAnswer = new char[sizeCHAR];
			SendMessage(hwndFalsem, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)AnAnswer);
			char* Comment = new char[sizeCHAR];
			SendMessage(hwndComment, WM_GETTEXT, (WPARAM)sizeCHAR, (LPARAM)Comment);

			Box_Quest.new_question(quest, Answer, AnAnswer, Comment);
			delete[] quest; delete[] Answer; delete[] AnAnswer; delete[] Comment;
			MessageBox(hwnd, "Вопрос был сохранен", "ИНФО", MB_OK | MB_ICONINFORMATION);
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