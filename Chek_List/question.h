#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random> //��������� ��������� �����
#include <fstream> // �������� ������
#include <sstream> //�������� ������
//using namespace std;

class answer {
	bool if_TRUE; //1- �� �����.
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
	std::string quest;	//?? ����� �� ��������� ����� ������ ��� �������� ������ ��������
	std::vector <answer> Answer;
	std::string comment = "";
public:
	std::string getQuest() { return quest; }
	void print();	//����� �� �������

	
	void setQuest(std::string Q);
	void addAnswer(std::string A, bool t);
	void clearAnswer();
	void setComment(std::string Q);

	void writeTXT(std::ostream& os, int val);	//������ � ����
	void writeHTML(std::ostream& os, int val);	//������ � ����

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
/*   ����������  */
/* - - - - - - - */


void question::print() {
//����� �� �������
	std::cout << "�����C: " << quest << std::endl;
	for (answer x : Answer) {
		if (x.if_true()) std::cout << "�����: ";
		else  std::cout << "�� �����: ";
		std::cout << x.getAnswer() << std::endl;
	}
	if (comment.size()>2) std::cout << "����������: " << comment << std::endl;
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
	/*������ ������� � �������*/
	os << val+1 <<" ������: " << quest << std::endl;
	for (answer x : Answer) {
		if (x.if_true()) os << "�����: ";
		else  os << "�� �����: ";
		os << x.getAnswer() << std::endl;
	}
	if (comment.size() > 2) os << "����������: " << comment << std::endl;
	os << std::endl;
}

void question::writeHTML(std::ostream& os, int val) {
	/*������ ������� � �������*/
	"<div style=\" line-height:1;\">TML � �SS.</div></li>";
	os << "<div style=\"margin-left:20px;\"><div style=\" line-height:1;\"><strong>" << val + 1 << ") ������: " << quest << "</strong></div></div></li>\n"<< std::endl;
	for (answer x : Answer) {
		if (x.if_true()) {
			os << "<div style=\"margin-left:40px;\"><div style=\" line-height:0.8;\"><p><font color=\"green\"> &#10004; �����: " << x.getAnswer() << "</font></p></div></div></li>\n";
		}
		else {
			os << "<div style=\"margin-left:40px;\"><div style=\" line-height:0.8;\"><p><font color=\"red\"><del> &#10008; �� �����: " << x.getAnswer() << "</del></font></p></div></div></li>\n";
		}		
	}
	if (comment.size() > 2) {
		os <<
			"<div style=\"margin-left:20px;\"><div class=\"spoiler\">\n"
			"   <details open>" //���� ������ open ������ ����� ������
			"      <summary>";
		os << "����������:</summary><div><div style=\"margin-left:40px;\"><div style=\"margin-right:40px;\"><p align=\"justify\"><i>" << comment  <<"</i></p></div></div></div>\n"
			"   </details>\n"		
			"</div></div>\n";
	}
	os << "<br/>\n";
}