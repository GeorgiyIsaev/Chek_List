/*��������� �������
1.�������� ������������-> ����� -> ����� �������� -> ������������ ������������� ���������
2.�/�++ -> ����-> �������� ����� �++-> ��������� �������� ���������
3.�������� ������� -> ����������� -> ������� -> ���������� -> "Windows"
*/


#include "MainMenu.h"  
#include <windows.h>
#include "resource.h"  //���������� �������
#define BIGBUFF 8192 
cont_question Box_Quest;
numers::info_test_create Box_val;

/*������ ��� ���������� ������, �� ��������� win98*/
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


/*�������� ����*/
HINSTANCE hNew_Q, hFile, hRead, hTest, hSave;/*��������� ���� ��� ���� �����*/
/*���� ������ �������*/
HWND hwndQ, hwndTrue, hwndFalsem, hwndComment; //���� ��� �������� �������
/*���� �������� �����*/
HWND hwndNameFile; //���� ��� ����� ����� �����

/*���� ���������*/
HINSTANCE h_Re_read;
HWND hList; HWND hwnd_redact;

/*���� ������*/
HWND hListAnswer; HWND hwndQuestTest;


/*���� ���������� �����*/
HWND hwndNameSave, hwndHead; //���� ��� ����� ����� ������������ ����� 



BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DlgProc_new(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_file(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Read(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Redact(HWND, UINT, WPARAM, LPARAM); 
BOOL CALLBACK DlgProc_TECT(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Save(HWND, UINT, WPARAM, LPARAM);


// ������� WinAPI ��� ����� ����� � ���������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Box_Quest.set_NameF() = "TEMPTXT.txt";
	Box_Quest.read_fileTXT();
	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDM_DIALOG), 0, (DlgProc), 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
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
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
		switch (LOWORD(wParam))
		{
		case IDM_NEW:
			DialogBoxParam(hNew_Q, MAKEINTRESOURCE(IDN_DIALOG), hwnd, DlgProc_new, 0);
			break;
		case IDM_ADDFILE:
			DialogBoxParam(hFile, MAKEINTRESOURCE(IDF_DIALOG), hwnd, DlgProc_file, 0);			
			break;
		case IDM_READ:
			DialogBoxParam(hRead, MAKEINTRESOURCE(IDR_DIALOG), hwnd, DlgProc_Read, 0);
			break;
		case IDM_TECT:
			if (Box_Quest.SIZE_BOX() < 1) {
	    		MessageBox(hwnd, "� ���_����� ���� ��������!", "����", MB_OK | MB_ICONINFORMATION);				
			}
			else {
				Box_val.reset();
				Box_val.generator(Box_Quest.SIZE_BOX());
				DialogBoxParam(hTest, MAKEINTRESOURCE(IDT_DIALOG), hwnd, DlgProc_TECT, 0);
			}
			//MessageBox(hwnd, "���� ������ ������ TECT (�� � ���� �� ���������� � ����������)", "����", MB_OK | MB_ICONINFORMATION);
			break;
		case IDM_SAVE:		
			DialogBoxParam(hSave, MAKEINTRESOURCE(IDS_DIALOG), hwnd, DlgProc_Save, 0);
			//MessageBox(hwnd, "���� ������ ������ SAVE", "info", MB_OK | MB_ICONINFORMATION);
			break;
		}
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return FALSE;
}


void new_quest_edit(HWND hwnd) {
	/*� ��������� ����� ����������� �� ��, � ����� � ������� ����� */
	std::string questSTR = "������� ������ � " + std::to_string(Box_Quest.SIZE_BOX() + 1);
	char* quest = new char[BIGBUFF];
	strcpy_s(quest, BIGBUFF, questSTR.c_str());
	hwndQ = GetDlgItem(hwnd, IDN_ENEW);
	hwndTrue = GetDlgItem(hwnd, IDN_ETRUE);
	hwndFalsem = GetDlgItem(hwnd, IDN_EFALSE);
	hwndComment = GetDlgItem(hwnd, IDN_ECOMMENT);
	/*�������� ����� � ��������� ���� hEdit1*/
	SendMessage(hwndQ, WM_SETTEXT, 0, (LPARAM)quest);
	SendMessage(hwndTrue, WM_SETTEXT, 0, (LPARAM)"������� ���������� ������.\r\n������ ����� �������� � ����� ������\r\n����� ������->(CTRL+ENTER)");
	SendMessage(hwndFalsem, WM_SETTEXT, 0, (LPARAM)"������� �� ���������� ������\r\n������ ����� �������� � ����� ������\r\n����� ������->(CTRL+ENTER)");
	SendMessage(hwndComment, WM_SETTEXT, 0, (LPARAM)"������� ����������\r\n\r\n (*�� ������������ ����), ����� �������� ������!");

}
BOOL CALLBACK DlgProc_new(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{
		new_quest_edit(hwnd);
		break;
	}
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
		switch (LOWORD(wParam))
		{			
		case IDN_NEXT:
			
			//GetDlgItemText(hwndQ, IDN_ENEW, (LPSTR)text, 1024);
			//SendMessage(hwndQ, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			//int sizeCHAR = 2047;
			char* quest = new char[BIGBUFF];
			SendMessage(hwndQ, WM_GETTEXT, (WPARAM)BIGBUFF, (LPARAM)quest);
			char* Answer = new char[BIGBUFF];
			SendMessage(hwndTrue, WM_GETTEXT, (WPARAM)BIGBUFF, (LPARAM)Answer);
			char* AnAnswer = new char[BIGBUFF];
			SendMessage(hwndFalsem, WM_GETTEXT, (WPARAM)BIGBUFF, (LPARAM)AnAnswer);
			char* Comment = new char[BIGBUFF];
			SendMessage(hwndComment, WM_GETTEXT, (WPARAM)BIGBUFF, (LPARAM)Comment);
				
			if (Box_Quest.if_have_Q(quest)) {
				MessageBox(hwnd, "����� ������ ��� ����", "����", MB_OK | MB_ICONINFORMATION);
			}
			else {
				Box_Quest.new_question(quest, Answer, AnAnswer, Comment);
				delete[] quest; delete[] Answer; delete[] AnAnswer; delete[] Comment;
				new_quest_edit(hwnd);
				
			}
			break;	
		}
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_file(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{
		/*� ��������� ����� ����������� �� ��, � ����� � ������� ����� */
		hwndNameFile = GetDlgItem(hwnd, IDF_NAMEFILE);
		/*�������� ����� � ��������� ���� hEdit1*/
		SendMessage(hwndNameFile, WM_SETTEXT, 0, (LPARAM)"Name.html");
		break;
	}
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
		switch (LOWORD(wParam))
		{
		case IDF_OPEN:
			char* text = new char[255];
		
			SendMessage(hwndNameFile, WM_GETTEXT, (WPARAM)255, (LPARAM)text);
			Box_Quest.set_NameF() = text;
			delete[] text;

			std::string messege = Box_Quest.find_file();
			MessageBox(hwnd, messege.c_str(), "����", NULL);
			EndDialog(hwnd, 0);
			return TRUE;	
			break;
		}
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

void reset_list_question(HWND hwnd) {
	InvalidateRect(hList, NULL, TRUE); //�������� ����
	h_Re_read = GetModuleHandle(NULL);
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	hList = GetDlgItem(hwnd, IDR_LIST);
	for (int i = 0; i < Box_Quest.SIZE_BOX(); i++) {		
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Box_Quest.print_quest(i).c_str());
	}
}
BOOL CALLBACK DlgProc_Read(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{
		reset_list_question(hwnd);
		break;
	}
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
		switch (LOWORD(wParam))
		{
		case IDR_LIST:		
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);		
				Box_Quest.It_this(i);
				DialogBoxParam(h_Re_read, MAKEINTRESOURCE(IDR_DIALOG_RECORD), hwnd, DlgProc_Redact, 0);
							
				reset_list_question(hwnd);				
			}			
		}
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_Redact(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{
		int sizeCHAR = 2048;
		/*� ��������� ����� ����������� �� ��, � ����� � ������� ����� */
		hwndQ = GetDlgItem(hwnd, IDR_ENEW);
		hwndTrue = GetDlgItem(hwnd, IDR_ETRUE);
		hwndFalsem = GetDlgItem(hwnd, IDR_EFALSE);
		hwndComment = GetDlgItem(hwnd, IDR_ECOMMENT);
		/*�������� ����� � ��������� ���� hEdit1*/
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
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
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
			MessageBox(hwnd, "������ ��� ��������", "����", MB_OK | MB_ICONINFORMATION);
			SendMessage(hList, LB_RESETCONTENT, 0, 0);		
			EndDialog(hwnd, 0);
			return TRUE;
			break;
		}
		//InvalidateRect(NULL, NULL, TRUE);
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}


//int val_index_box = 0;
void reload_quest_test(HWND hwnd) {
	
	/*���������� ����� �������*/
	Box_Quest.It_this(Box_val.next_int_question());

	/*��������� ������*/
	//int sizeCHAR = BIGBUFF;
	char* quest = new char[BIGBUFF];
	strcpy_s(quest, BIGBUFF, Box_Quest.getQuest().c_str());
	SendMessage(hwndQuestTest, WM_SETTEXT, 0, (LPARAM)quest);
	/*��������� ������*/
	Box_Quest.sort_answer_IT();

	InvalidateRect(hList, NULL, TRUE); //�������� ����
	h_Re_read = GetModuleHandle(NULL);
	SendMessage(hListAnswer, LB_RESETCONTENT, 0, 0);
	hListAnswer = GetDlgItem(hwnd, IDT_ANSWER);
	for (int i = 0; i < Box_Quest.size_answers(); i++) {
		SendMessage(hListAnswer, LB_ADDSTRING, 0, (LPARAM)Box_Quest.getAnswer_val(i).c_str());
	}
	delete[] quest;
}

BOOL CALLBACK DlgProc_TECT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//std::string temp = "";
	int cSelItems;
	int cSelItemsInBuffer;
	int aSelItems[100];
	bool like;
	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{	
		hwndQuestTest = GetDlgItem(hwnd, IDT_QUEST);
		reload_quest_test(hwnd);
		break;		
	}
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
		char* info;
		switch (LOWORD(wParam))
		{
		case IDT_ANSWERS:
			cSelItems = SendMessage(hListAnswer, LB_GETSELCOUNT, 0, 0);
			cSelItemsInBuffer = SendMessage(hListAnswer, LB_GETSELITEMS, 512, (LPARAM)aSelItems);

			if (cSelItemsInBuffer == 0) {
				MessageBox(hwnd, "����� ������� ���� �� ���� �����", "������!", MB_OK | MB_ICONINFORMATION);
				return TRUE;
			}
			info = new char[BIGBUFF];	
			if (Box_Quest.count_RIGHT_answer() == cSelItemsInBuffer) {
				for (int i = cSelItemsInBuffer - 1; i >= 0; i--)
				{
					if (!Box_Quest.if_this_true_int(aSelItems[i])) {
						like = false;
						break;
					}
					like = true;
				}
			}
			else like = false;
			
			if (like) {				
				strcpy_s(info, BIGBUFF, Box_Quest.strInfoQuest("��� ����� ������!\r\n").c_str());
				MessageBox(hwnd, info, "���������� �����!", NULL);
				Box_val.right_answer();
			}
			else {
				strcpy_s(info, BIGBUFF, Box_Quest.strInfoQuest("��� ����� �� ������").c_str());
				MessageBox(hwnd, info, "��� ����� �� ������", MB_OK | MB_ICONHAND);
			}
			delete[] info;
			/*���������� ���������� ��� ������*/
		case IDT_NEXTANSWER:
			
			if(Box_val.if_stop()){				
				char* quest = new char[BIGBUFF];
				strcpy_s(quest, BIGBUFF, Box_val.finalSTR().c_str());
				
				MessageBox(hwnd, quest, "info", MB_OK | MB_ICONINFORMATION);
				EndDialog(hwnd, 0);
				return TRUE;
			}
			else {								
				reload_quest_test(hwnd);
			}
			break;
		}	
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}



BOOL CALLBACK DlgProc_Save(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) //���������� ���������
	{
	case WM_INITDIALOG:
	{
		/*� ��������� ����� ����������� �� ��, � ����� � ������� ����� */
		hwndHead = GetDlgItem(hwnd, IDS_ENAMHEAD);
		hwndNameFile = GetDlgItem(hwnd, IDS_ENAMESAVE2);
		/*�������� ����� � ��������� ���� hEdit1*/
		SendMessage(hwndHead, WM_SETTEXT, 0, (LPARAM)"��������� ���-�����");
		SendMessage(hwndNameFile, WM_SETTEXT, 0, (LPARAM)"Name.html");
		break;
	}
	case WM_COMMAND:	//���������� ������ ������, ���� ����� � �.�.
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
			MessageBox(hwnd, "��������� ��� ���", "����", MB_OK | MB_ICONINFORMATION);
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
			MessageBox(hwnd, "��������� ��� ����", "����", MB_OK | MB_ICONINFORMATION);
			EndDialog(hwnd, 0);
			return TRUE;			
			break;			
		}
		break;
	case WM_CLOSE:		//��������� �������� ���� ������������
		EndDialog(hwnd, 0);
		return TRUE;
	}
	return FALSE;
}