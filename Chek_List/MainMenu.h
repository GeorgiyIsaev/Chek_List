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
	int count_RIGHT_answer() {
		int count = 0;
		for (answer x : (*It).getAnswers()) if (x.if_true()) count++;
		return count;
	}		 
	std::string getQuest() {return (*It).getQuest();}
	std::string getComment() { return (*It).getComment(); }
	std::string getAnswer() { 
		std::string Ans = "";	
		for (answer x : (*It).getAnswers()) {
			if (x.if_true()) {
				Ans += x.getAnswer();
				Ans += "\r\n";
			}
		}
		Ans.erase(Ans.size()-1);
		return Ans;
	}
	std::string getAnAnswer() {
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
	
	std::string getAnswer_val(int val) {
		return (*It).getAnswer(val);
		/*std::string temp = std::to_string(val)+". "+(*It).getAnswer(val);
		return temp;*/
	}
	int size_answers() {
		return (*It).size_answers();
	}
	void sort_answer_IT() {
		(*It).sortAnswer();
	}	
	//question& setQuestion() { return (*It); }
	void It_this(int i) {
		It = conteiner.begin();
		advance(It, i);
	}
	void add_question();
	

	std::string strInfoQuest(std::string info) {
		info += "\r\nЗАДАННЫЙ ВОПРОС: \r\n";
		info+=(*It).getQuest(); info += "\r\n\r\n";
		info += "ВЕРНЫЕ ОТВЕТЫ: \r\n"; 
		info += getAnswer(); info += "\r\n";
		if ((*It).getComment() != "") {
			info += "\r\nКОМЕНТАРИЙ:\r\n";
			info += (*It).getComment(); info += "\r\n";
		}
		return info;
	}



	bool new_question(std::string Quest, std::string Answer, std::string AnAnswer, std::string Comment) {
		question Quest_Obj;
		//if (!if_have_Q(Quest)) {
			Quest_Obj.setQuest(Quest);
			
			int p = 0;
			while (Answer.find("\n", 0) != std::string::npos) {
				if (Answer.find("\n", 0) != std::string::npos) {
					p = Answer.find("\n", p)-1;
					std::string temp = Answer.substr(0, p);
					Answer.erase(0, p+2);
					Quest_Obj.addAnswer(temp, true);
				}
			}
			if(Answer.size()>0) Quest_Obj.addAnswer(Answer, true);

			p = 0;
			while (AnAnswer.find("\n", 0) != std::string::npos) {
				if (AnAnswer.find("\n", 0) != std::string::npos) {
					p = AnAnswer.find("\n", p)-1;
					std::string temp = AnAnswer.substr(0, p);
					AnAnswer.erase(0, p+2);
					Quest_Obj.addAnswer(temp, false);
				}
			}
			if (AnAnswer.size() > 0) Quest_Obj.addAnswer(AnAnswer, false);
		
			if (Comment == "Введите коментарий")Comment = "";
			if (Comment == "Введите коментарий\r\n\r\n (*Не обязательное поле), можно оставить пустым!")Comment = "";
			Quest_Obj.setComment(Comment);
			if(!Quest_Obj.if_true_answers()) Quest_Obj.addAnswer("Нет верного ответа", true);
			if (Quest_Obj.if_no_one_answer()) Quest_Obj.addAnswer("Нет верного ответа", false);
			conteiner.push_back(Quest_Obj);
			SORT();
			return true;
		/*}
		return false;*/
	}
	bool add_quest(std::string temp){
		question Q_temp;
		if (if_have_Q(temp)) {
			/*std::cout << "Этот вопрос уже есть!";*/
			return false;
		}
		Q_temp.setQuest(temp);
		return true;
	}	
	
	bool if_this_true_int(int i) {
		return (*It).if_this_true_int(i);
	}

	void SORT() {std::sort(conteiner.rbegin(), conteiner.rend());}
	int SIZE_BOX() { return conteiner.size(); }
	std::string print_quest(int i) {
		It = conteiner.begin();
		advance(It, i);
		std::string _i ="";
		if (conteiner.size() > 99 && i < 99) _i = "0";
		if (conteiner.size() > 9 && i < 9)	_i += "0";
		_i += std::to_string(i+1) + ". "+ (*It).getQuest();
		return _i;		
	}
	bool if_have_Q(std::string tmp);
	bool dell_question();
	bool dell_question(int);

	void print_full();
	void print_one();

	void save_fileTXT();
	bool read_fileTXT();

	void save_fileHTML();
	bool read_fileHTML();
	void open_file_Name(std::string& mes);
	std::string find_file();


	std::string if_type_file();
	std::string& set_NameC() {return name_conteiner;}
	std::string& set_NameF() {return name_file;}

};


class command {
protected:
	std::string opisanie;
public:
	virtual void execute(cont_question&) = 0;
	virtual std::string getInfo() { return opisanie; };
};


/*Релизация списка с вопросами*/



bool cont_question::if_have_Q(std::string tmp) {
	question temp;
	It = find_if(conteiner.begin(), conteiner.end(), [&tmp](question q) {
		if (q.getQuest() == tmp) return true;
		else return false;
	});
	if (It != conteiner.end()) return true;
	else return false;
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
	conteiner.erase(conteiner.begin()+val);
	return true;
}
//class Q_dell :public command {
//public:
//	Q_dell() { opisanie = "Удалить вопрос. "; }
//	virtual void execute(cont_question& temp) {
//		temp.add_question();
//	}
//};




//void cont_question::print_one() {
//	std::cout << "Введите номер вопроса --> ";
//	int val; (std::cin >> val).get();
//	if (val>=0 && val < conteiner.size()) {	
//		It = conteiner.begin();
//		advance(It, val);
//		std::cout << val << ". ";
//		(*It).print();
//	}
//	else {
//		std::cout << "Вопроса с таким номером нет!\n";
//	}
//}
//class Q_print_one :public command {
//public:
//	Q_print_one() { opisanie = "Показать один вопрос. "; }
//	virtual void execute(cont_question& temp) {
//		temp.print_one();
//	}
//};


//void cont_question::print_full() {
//	for (question tmp : conteiner) {
//		tmp.print();
//	}
//}
//class Q_print_full :public command {
//public:
//	Q_print_full() { opisanie = "Показать все вопросы. "; }
//	virtual void execute(cont_question& temp) {
//		temp.print_full();
//	}
//};


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
class Q_savefile :public command {
public:
	Q_savefile() { opisanie = "Сохранить в файл. "; }
	virtual void execute(cont_question& temp) {
		temp.save_fileTXT();
	}
};


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
			std::getline(to_file, temp);  std::cout <<" --- "<< temp << std::endl;
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
class Q_readfile :public command {
public:
	Q_readfile() { opisanie = "Прочесть из файла. "; }
	virtual void execute(cont_question& temp) {
		temp.read_fileTXT();
	}
};




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
	//cout << "Файл успешно записан" << endl;
}
class Q_savefile_HTML :public command {
public:
	Q_savefile_HTML() { opisanie = "Сохранить в файл HTML "; }
	virtual void execute(cont_question& temp) {
		std::cout << "Введите имя файла -> ";
		std::string str;
		(std::cin >> str).get();
		std::cout << "Введите Тему впоросов (заголовок)-> ";
		(std::cin >> str).get();
		str += ".html";
		
		temp.save_fileHTML();
	}
};


bool cont_question::read_fileHTML() {
	std::ifstream to_file(name_file);
	question Q_temp;
	if (to_file.is_open()) {
		//std::getline(to_file, name_conteiner);
		int countr = 0;
		/*Отдельно создаем вопрос*/
		std::string temp = "";
		//std::getline(to_file, temp);  /*Пустая строчка*/
		while (!to_file.eof()) {
			temp = "";
			std::getline(to_file, temp);  //cout << countr++ << "   "<< temp << endl;
			if (temp.find("ВОПРОС:") != std::string::npos) {
				if (Q_temp.getQuest().size() > 2) {
					conteiner.push_back(Q_temp);
					Q_temp = question(); //пересоздать объект
				}
				temp = temp.erase(temp.find("</strong></div></div></li>"));
				Q_temp.setQuest(temp.substr(temp.find("ВОПРОС:") + 8));
				//cout << temp.substr(temp.find("ВОПРОС:") + 8) << endl;
				//cout << "+вопрос \n ";
			}
			else if (temp.find("НЕ ВЕРНО:") != std::string::npos) {
				temp = temp.erase(temp.find("</del></font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("НЕ ВЕРНО: ") + 10), 0);
				//cout << "+нет \n ";
			}
			else if (temp.find("ВЕРНО:") != std::string::npos) {
				temp = temp.erase(temp.find("</font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("ВЕРНО: ") + 7), 1);
				//cout << "+да \n ";
			}
			else if (temp.find("КОМЕНТАРИЙ:") != std::string::npos) {
				//std::cout << " --     " << temp << std::endl;
				temp = temp.erase(temp.find("</i></p></div></div></div>"));
				//std::cout << " ---    " << temp << std::endl;
				//std::cout << " 111-   " << temp.substr(temp.find("КОМЕНТАРИЙ:") + 111) << endl;
				Q_temp.setComment(temp.substr(temp.find("КОМЕНТАРИЙ:") + 111));
				//cout << "+ком \n ";
			}
		}
		//system("pause");
		conteiner.push_back(Q_temp);
		to_file.close();
		return true;
		//cout << "Добавлено студентов: " << countr << endl;
	}
	else return false;
}

class Q_readfile_HTML :public command {
public:
	Q_readfile_HTML() { opisanie = "Прочесть из файла HTML. "; }
	virtual void execute(cont_question& temp) {
		temp.read_fileHTML();
	}
};

void cont_question::open_file_Name(std::string& messege) {	
	if (if_type_file() == ".txt") {
		bool mes = read_fileTXT();
		if (!mes) messege += " Файл " + set_NameF() + " не найден!";
		else{ messege = "Файл " + set_NameF() + " успешно прочитан!";	throw 1;}
	}
	if (if_type_file() == ".html") {
		bool mes = read_fileHTML();
		if (!mes) messege += "Файл " + set_NameF() + " не найден! ";
		else { messege = "Файл " + set_NameF() + " успешно прочитан!";	throw 1;}
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