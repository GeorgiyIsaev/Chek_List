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
	int size_answers() { return Answer.size(); }
	std::string getQuest() const { return quest; }
	std::string getComment() const { return comment; }
	std::vector <answer> getAnswers() { return Answer; }
	std::string getAnswer(int val) { return Answer.at(val).getAnswer(); }
	void print();	//����� �� �������



	void sortAnswer() {
		sort(Answer.begin(), Answer.end(), [](answer& tmp1, answer& tmp2) {
			if (tmp1.getVal() > tmp2.getVal())
				return true;
			return false;		
		});		
	}

	bool if_this_true(std::string temp) {
		for (int i = 0; i < Answer.size(); i++) {
			if (Answer.at(i).getAnswer() == temp) return true;
		}
		return false;
	}
	bool if_this_true_int(int i) {
		if (Answer.at(i).if_true() ) return true;		
		return false;
	}
	bool if_not_true_answers() {
		int i = Answer.size();
		int countRight = 0;
		while (i--) {
			if (Answer.at(i).if_true()) countRight++;
		}
		if(countRight>=1) return false;
		else return true;		
	}
	bool if_only_one_answer() {
		if (Answer.size() >= 1) return false;
		return true;
	}

	
	void setQuest(std::string Q);
	void addAnswer(std::string A, bool t);
	void clearAnswer();
	void setComment(std::string Q);

	void writeTXT(std::ostream& os, int val);	//������ � ����
	void writeHTML(std::ostream& os, int val);	//������ � ����


	bool operator<(const question& obj) const{
		if(quest > obj.quest )
			return true;
		return false;		
	}
	bool operator==(const question& obj) const {
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
	answer tempAnswer(t,A);
	Answer.push_back(tempAnswer);
	//Answer.emplace_back(t, A);
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



namespace numers{
#pragma once
#include <iostream> 
#include <random> 

	//using namespace std;

	/*����� � ���������� ��� �����*/
	class info_test_create {
		std::vector<int> qenerator_next_quest;
		//int SIZE_box;
		int next_Q = 0;
		int countAnswer = 0;
	public:
		void reset() {
			qenerator_next_quest.clear();
			next_Q = 0;
			countAnswer = 0;
		}
		void right_answer() { countAnswer++; }
		bool if_stop() {
			if (next_Q >= 20) return true;
			return false;
		}
		int next_int_question() {	
			return qenerator_next_quest.at(next_Q++);
		}
		void generator(int size) {
			//SIZE_box = size;
			std::random_device rd;
			//std::mt19937 mt(rd());
			int val = 20;
			while (val--) {
				qenerator_next_quest.push_back(rd() % size);
			}
		}
		std::string finalSTR() {
			std::string info;
			double proc = (countAnswer * 100.0)/ next_Q; 
			std::string procSTR = std::to_string(proc);
			procSTR.erase(4);
			info = "���� �����ب�!\r\n \r\n";
			info += "���������: ";
			if (proc > 90.0) info += "�������";
			else if (proc > 60.0) info += "������������������";
			else info += "�� ������������������";
			info += "\r\n";

			info += "���������� �������� ��������: " + std::to_string(next_Q);
			info += "\r\n";
			info += "���������� ������ �������: " + std::to_string(countAnswer);
			info += " (" + procSTR + " %)";
			info += "\r\n";
			return info;
		}
	};
};