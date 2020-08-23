#pragma once
#include "question.h"
#include <algorithm>
#include <set>


class cont_question {
	std::vector<question> conteiner;
	std::string name_conteiner;
	std::string name_file;
	std::vector<question>::iterator It;
public:
	/*Методы для работы теста*/
	int test_count_RIGHT_answer();
	int test_count_FULL_answers();
	bool if_this_int_answer_true(int i);
	void test_unsort_answer_IT();
	std::string testGet_strInfoQuest(std::string info);

	/*Методы возврата полей для просмотра*/
	void It_this(int i); //выбрать конкретный вопрос

	std::string getQuest();
	std::string getComment();
	std::string getFullAnswer();
	std::string getFullAnAnswer();
	std::string getAnswer_val(int val);

	std::string print_quest_listbox(int i);
	int SIZE_BOX() { return conteiner.size(); }

	bool dell_question();
	bool dell_question(int);

	/*Запись нового вопроса*/
	bool if_have_Q(std::string tmp);
	std::string dell_str_RN(std::string temp);
	bool new_question(std::string Quest, std::string Answer, std::string AnAnswer, std::string Comment);	

	
	/*Методы для работы праграммы с файлами*/
	void SORT() {std::sort(conteiner.rbegin(), conteiner.rend());}
	std::string& set_NameC();
	std::string& set_NameF();
	
	void open_file_Name(std::string& mes);
	std::string find_file();
	std::string if_type_file();

	void save_fileTXT();
	void save_fileHTML();
	bool read_fileTXT();	
	bool read_fileHTML();
};


/**************************************************/
/*************Методы для работы теста**************/
/**************************************************/
int cont_question::test_count_RIGHT_answer() { //количество правильных ответов, для проверки теста
	int count = 0;
	for (answer x : (*It).getAnswers()) if (x.if_true()) count++;
	return count;
}
int cont_question::test_count_FULL_answers() {
	return (*It).size_answers();
}
void cont_question::test_unsort_answer_IT() {
	(*It).sortAnswer();
}
std::string cont_question::testGet_strInfoQuest(std::string info) {
	info += "\r\nЗАДАННЫЙ ВОПРОС: \r\n";
	info += (*It).getQuest(); info += "\r\n\r\n";
	info += "ВЕРНЫЕ ОТВЕТЫ: \r\n";
	info += getFullAnswer(); info += "\r\n";
	if ((*It).getComment() != "") {
		info += "\r\nКОМЕНТАРИЙ:\r\n";
		info += (*It).getComment(); info += "\r\n";
	}
	return info;
}
bool cont_question::if_this_int_answer_true(int i)
{
	return (*It).if_this_true_int(i);
}


/**************************************************/
/******Методы возврата полей для просмотра*********/
/**************************************************/
void cont_question::It_this(int i) {
	It = conteiner.begin();
	advance(It, i);
}

std::string cont_question::getQuest() { return (*It).getQuest(); }
std::string cont_question::getComment() { return (*It).getComment(); }
std::string cont_question::getFullAnswer() {
	std::string Ans = "";
	for (answer x : (*It).getAnswers()) {
		if (x.if_true()) {
			Ans += x.getAnswer();
			Ans += "\r\n";
		}
	}
	Ans.erase(Ans.size() - 1);
	return Ans;
}
std::string cont_question::getFullAnAnswer() {
	std::string Ans = "";
	(*It).getAnswers();
	for (answer x : (*It).getAnswers()) {
		if (!(x.if_true())) {
			Ans += x.getAnswer();
			Ans += "\r\n";
		}
	}
	Ans.erase(Ans.size() - 1);
	return Ans;
}
std::string cont_question::getAnswer_val(int val) {
	return (*It).getAnswer(val);
}

std::string  cont_question::print_quest_listbox(int i) {
	It = conteiner.begin();
	advance(It, i);
	std::string _i = "";
	if (conteiner.size() > 99 && i < 99) _i = "0";
	if (conteiner.size() > 9 && i < 9)	_i += "0";
	_i += std::to_string(i + 1) + ". " + (*It).getQuest();
	return _i;
}


bool cont_question::dell_question() {
	if (It != conteiner.end()) {
		conteiner.erase(It);
		return true;
	}
	return false;
}
bool cont_question::dell_question(int val) {
	if (val<0 || val >conteiner.size()) {
		return false;
	}
	conteiner.erase(conteiner.begin() + val);
	return true;
}


/**************************************************/
/***************Запись нового вопроса**************/
/**************************************************/
std::string cont_question::dell_str_RN(std::string temp) {
	int p = 0; std::string tempQ = "";
	while (temp.find("\r\n", 0) != std::string::npos) {
		if (temp.find("\r\n", 0) != std::string::npos) {
			p = temp.find("\r\n", 0);
			tempQ += temp.substr(0, p);
			temp.erase(0, p + 2);
			tempQ += " ";
		}
	}
	tempQ += temp;
	return tempQ;
}
bool cont_question::if_have_Q(std::string tmp) {
	tmp = dell_str_RN(tmp);
	question temp;
	It = find_if(conteiner.begin(), conteiner.end(), [&tmp](question q) {
		if (q.getQuest() == tmp) return true;
		else return false;
	});
	if (It != conteiner.end()) return true;
	else return false;
}
bool cont_question::new_question(std::string Quest, std::string Answer, std::string AnAnswer, std::string Comment) {
	question Quest_Obj;
	Quest_Obj.setQuest(dell_str_RN(Quest));

	int p = 0;
	while (Answer.find("\r\n", 0) != std::string::npos) {
		if (Answer.find("\r\n", 0) != std::string::npos) {
			p = Answer.find("\r\n", 0);
			std::string temp = Answer.substr(0, p - 1);
			temp;
			Answer.erase(0, p + 1);
			Quest_Obj.addAnswer(temp, true);
		}
	}
	if (Answer.size() > 0) Quest_Obj.addAnswer(Answer, true);

	p = 0;
	while (AnAnswer.find("\n", 0) != std::string::npos) {
		if (AnAnswer.find("\n", 0) != std::string::npos) {
			p = AnAnswer.find("\n", 0);
			std::string temp = AnAnswer.substr(0, p - 1);
			AnAnswer.erase(0, p + 1);
			Quest_Obj.addAnswer(temp, false);
		}
	}
	if (AnAnswer.size() > 0) Quest_Obj.addAnswer(AnAnswer, false);

	if (Comment == "Введите коментарий")Comment = "";
	if (Comment == "Введите коментарий\r\n\r\n (*Не обязательное поле), можно оставить пустым!")Comment = "";
	Quest_Obj.setComment(dell_str_RN(Comment));
	if (Quest_Obj.if_not_true_answers()) Quest_Obj.addAnswer("Нет верного ответа", true);
	if (Quest_Obj.if_only_one_answer()) Quest_Obj.addAnswer("Нет верного ответа", false);
	conteiner.push_back(Quest_Obj);
	SORT();
	set_NameF() = "TEMPTXT";
	save_fileTXT();
	return true;

}


/*************************************/
/********   РАБОТА С ФАЙЛАМИ   *******/
/*************************************/
std::string & cont_question::set_NameC() { return name_conteiner; }
std::string & cont_question::set_NameF() { return name_file; }

void cont_question::open_file_Name(std::string& messege) {
	if (if_type_file() == ".txt") {
		bool mes = read_fileTXT();
		if (!mes) messege += " Файл " + set_NameF() + " не найден!";
		else { messege = "Файл " + set_NameF() + " успешно прочитан!";	throw 1; }
	}
	if (if_type_file() == ".html") {
		bool mes = read_fileHTML();
		if (!mes) messege += "Файл " + set_NameF() + " не найден! ";
		else { messege = "Файл " + set_NameF() + " успешно прочитан!";	throw 1; }
	}
	//return messege;
};
std::string cont_question::find_file()
{
	std::string messege = "ОШИБКА! ";
	try {
		open_file_Name(messege);
		if (if_type_file() == "") {
			std::string temp_name = set_NameF();
			set_NameF() = temp_name + ".html";
			open_file_Name(messege);
			set_NameF() = temp_name + ".txt";
			open_file_Name(messege);
		}
	}
	catch (...) {
		int i;
	}
	SORT();
	return messege;
}
std::string cont_question::if_type_file() {	
	if (name_file.size() >= 5 && name_file.find(".txt", name_file.size() - 4) != std::string::npos) {
		return ".txt";
	}
	else if (name_file.size() >= 6 && name_file.find(".html", name_file.size() - 5) != std::string::npos) {
		return ".html";
	}
	else return "";
}



void cont_question::save_fileHTML() {
	name_file += ".html";
	std::ofstream to_file(name_file);
	int val = 0;
	to_file << "<html>\n	<head>\n";
	to_file << "<body bgcolor=\"springgreen\">\n";//Закрасить всю страницу зеленым
	"<h1><center>Сборник тестов 1</center><br/></h1>,";
	to_file << "<h1><center>" << name_conteiner << "</center><br/></h1>\n\n"; //заголовок

	to_file << "</head>\n	</body>\n"; //закрываем заголовок открываем тело

	for (question tmp : conteiner) {
		tmp.writeHTML(to_file, val);
		val++;
	}

	to_file << "	</body>\n</html>"; //закрываем страницу
	to_file.close();
}
void cont_question::save_fileTXT() {
	name_file += ".txt";
	std::ofstream to_file(name_file);
	int val = 0;
	to_file << name_conteiner << "\n\n";
	for (question tmp : conteiner) {
		tmp.writeTXT(to_file, val);
		val++;
	}
	to_file.close();
	//cout << "Файл успешно записан" << endl;
}


bool cont_question::read_fileHTML() {
	std::ifstream to_file(name_file);
	question Q_temp;
	if (to_file.is_open()) {		
		int countr = 0;
		/*Отдельно создаем вопрос*/
		std::string temp = "";		
		while (!to_file.eof()) {
			temp = "";
			std::getline(to_file, temp); 
			if (temp.find("ВОПРОС:") != std::string::npos) {
				if (Q_temp.getQuest().size() > 2) {
					conteiner.push_back(Q_temp);
					Q_temp = question(); //пересоздать объект
				}
				temp = temp.erase(temp.find("</strong></div></div></li>"));
				Q_temp.setQuest(temp.substr(temp.find("ВОПРОС:") + 8));
			}
			else if (temp.find("НЕ ВЕРНО:") != std::string::npos) {
				temp = temp.erase(temp.find("</del></font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("НЕ ВЕРНО: ") + 10), 0);
			}
			else if (temp.find("ВЕРНО:") != std::string::npos) {
				temp = temp.erase(temp.find("</font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("ВЕРНО: ") + 7), 1);
			}
			else if (temp.find("КОМЕНТАРИЙ:") != std::string::npos) {
				temp = temp.erase(temp.find("</i></p></div></div></div>"));
				Q_temp.setComment(temp.substr(temp.find("КОМЕНТАРИЙ:") + 111));
			}
		}		
		conteiner.push_back(Q_temp);
		to_file.close();
		return true;		
	}
	else return false;
}
bool cont_question::read_fileTXT() {

	std::ifstream to_file(name_file);
	question Q_temp;
	if (to_file.is_open()) {
		std::getline(to_file, name_conteiner);
		int countr = 0;
		/*Отдельно создаем вопрос*/
		std::string temp = "";
		std::getline(to_file, temp);  /*Пустая строчка*/
		while (!to_file.eof()) {
			temp = "";
			std::getline(to_file, temp);  std::cout << " --- " << temp << std::endl;
			if (temp.find("ВОПРОС:") != std::string::npos) {
				if (Q_temp.getQuest().size() > 2) {
					conteiner.push_back(Q_temp);
					Q_temp = question(); //пересоздать объект
				}
				Q_temp.setQuest(temp.substr(temp.find("ВОПРОС:") + 8));
				std::cout << temp.substr(temp.find("ВОПРОС:") + 8) << std::endl;
				std::cout << "+вопрос \n ";
			}
			else if (temp.find("НЕ ВЕРНО:") != std::string::npos) {
				Q_temp.addAnswer(temp.substr(temp.find("НЕ ВЕРНО: ") + 10), 0);
				std::cout << "+нет \n ";
			}
			else if (temp.find("ВЕРНО:") != std::string::npos) {
				Q_temp.addAnswer(temp.substr(temp.find("ВЕРНО: ") + 7), 1);
				std::cout << "+да \n ";
			}
			else if (temp.find("КОМЕНТАРИЙ: ") != std::string::npos) {
				Q_temp.setComment(temp.substr(temp.find("КОМЕНТАРИЙ: ") + 12));
				std::cout << "+ком \n ";
			}
		}
		conteiner.push_back(Q_temp);
		to_file.close();
		return true;
		//cout << "Добавлено студентов: " << countr << endl;
	}
	else return false;
}

