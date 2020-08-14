#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random> //генератор случайный чисел
#include <fstream> // файловые потоки
#include <sstream> //строковы потоки
//using namespace std;

class answer {
	bool if_TRUE; //1- Да верно.
	std::string Answer;
	int random_nomer;
public:
	answer(bool i, std::string A) : if_TRUE(i), Answer(A)   {
		std::random_device rd;
		random_nomer = rd() % 100;
	}
	std::string getAnswer() { return Answer; }
	int getVal() { return random_nomer; }
	bool if_true() { return if_TRUE; }
};

class question {
	std::string quest;	//?? нужен ли отдельный класс вопрос или обойтись просто стрингом
	std::vector <answer> Answer;
	std::string comment = "";
public:
	std::string getQuest() { return quest; }
	void print();	//вывод на консоль

	
	void setQuest(std::string Q);
	void addAnswer(std::string A, bool t);
	void clearAnswer();
	void setComment(std::string Q);

	void writeTXT(std::ostream& os, int val);	//запись в файл
	void writeHTML(std::ostream& os, int val);	//запись в файл

	bool operator<(question& obj) {
		if(quest < obj.quest )
			return true;
		return false;		
	}
	bool operator==(question& obj) { 
		if (quest == obj.quest)
			return true;
		return false;
	}

};



/* - - - - - - - */
/*   РЕАЛИЗАЦИЯ  */
/* - - - - - - - */


void question::print() {
//вывод на консоль
	std::cout << "ВОПРОC: " << quest << std::endl;
	for (answer x : Answer) {
		if (x.if_true()) std::cout << "ВЕРНО: ";
		else  std::cout << "НЕ ВЕРНО: ";
		std::cout << x.getAnswer() << std::endl;
	}
	if (comment.size()>2) std::cout << "КОМЕНТАРИЙ: " << comment << std::endl;
	std::cout << std::endl;
}	

void question::setQuest(std::string Q){
	quest = Q;
}
void question::clearAnswer(){
	Answer.clear();
}
void question::addAnswer(std::string A, bool t){
	Answer.emplace_back(t, A);
}
void question::setComment(std::string C){
	comment = C;
}


void question::writeTXT(std::ostream& os, int val) {
	/*Запись вопроса в блокнот*/
	os << val+1 <<" ВОПРОС: " << quest << std::endl;
	for (answer x : Answer) {
		if (x.if_true()) os << "ВЕРНО: ";
		else  os << "НЕ ВЕРНО: ";
		os << x.getAnswer() << std::endl;
	}
	if (comment.size() > 2) os << "КОМЕНТАРИЙ: " << comment << std::endl;
	os << std::endl;
}

void question::writeHTML(std::ostream& os, int val) {
	/*Запись вопроса в блокнот*/
	"<div style=\" line-height:1;\">TML и СSS.</div></li>";
	os << "<div style=\"margin-left:20px;\"><div style=\" line-height:1;\"><strong>" << val + 1 << ") ВОПРОС: " << quest << "</strong></div></div></li>\n"<< std::endl;
	for (answer x : Answer) {
		if (x.if_true()) {
			os << "<div style=\"margin-left:40px;\"><div style=\" line-height:0.8;\"><p><font color=\"green\"> &#10004; ВЕРНО: " << x.getAnswer() << "</font></p></div></div></li>\n";
		}
		else {
			os << "<div style=\"margin-left:40px;\"><div style=\" line-height:0.8;\"><p><font color=\"red\"><del> &#10008; НЕ ВЕРНО: " << x.getAnswer() << "</del></font></p></div></div></li>\n";
		}		
	}
	if (comment.size() > 2) {
		os <<
			"<div style=\"margin-left:20px;\"><div class=\"spoiler\">\n"
			"   <details open>" //Если убрать open комент будит закрыт
			"      <summary>";
		os << "КОМЕНТАРИЙ:</summary><div><div style=\"margin-left:40px;\"><div style=\"margin-right:40px;\"><p align=\"justify\"><i>" << comment  <<"</i></p></div></div></div>\n"
			"   </details>\n"		
			"</div></div>\n";
	}
	os << "<br/>\n";
}