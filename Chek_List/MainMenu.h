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
	void add_question();
	bool add_quest(std::string temp){
		question Q_temp;
		if (if_have_Q(temp)) {
			/*std::cout << "���� ������ ��� ����!";*/
			return false;
		}
		Q_temp.setQuest(temp);
		return true;
	}
	void add_answer(std::string temp, bool b) {
		//int p = 0;
		//if (temp.find(";", p) != std::string::npos) {
		//	if (Q_temp.getQuest().size() > 2) {
		//		conteiner.push_back(Q_temp);
		//		Q_temp = question(); //����������� ������
		//	}
		//	Q_temp.setQuest(temp.substr(temp.find("������:") + 8));
		//	std::cout << temp.substr(temp.find("������:") + 8) << std::endl;
		//	std::cout << "+������ \n ";
		//}
		//
		//
		//
		//int val = 1;
		//while (val) {


		//	std::string temp = "";
		//	std::cout << "������� �����: ";
		//	//cin.get();
		//	std::getline(std::cin, temp_str);
		//	bool set = 0;
		//	std::cout << "[ �����? (1-��, 0-���) ][ ��� �����? (1-��, 0-���) ]\n";
		//	(std::cin >> set >> val).get();
		//	Q_temp.addAnswer(temp_str, set);
		//}
	}
	void add_comment(std::string temp="") {
		conteiner.at(conteiner.size() - 1).setComment(temp);
		SORT();
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
	void dell_question();

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


/*��������� ������ � ���������*/



bool cont_question::if_have_Q(std::string tmp) {
	question temp;
	It = find_if(conteiner.begin(), conteiner.end(), [&tmp](question q) {
		if (q.getQuest() == tmp) return true;
		else return false;
	});
	if (It != conteiner.end()) return true;
	else return false;
}
//void cont_question::add_question() {
//	/*��� ���������� ���������, � � ������ �� �����, ������ ����� Q_add ��������� � ���� ���������, � ��������� question ������ ������ ���������*/
//	question Q_temp;
//	std::string temp_str;
//	std::cout << "������� ������: ";
//	std::getline(std::cin, temp_str);
//	if (if_have_Q(temp_str)) {
//		std::cout << "���� ������ ��� ����!";
//		return;
//	}
//	Q_temp.setQuest(temp_str);
//	int val = 1;
//	while (val) {
//		std::string temp = "";
//		std::cout << "������� �����: ";
//		//cin.get();
//		std::getline(std::cin, temp_str);
//		bool set = 0;
//		std::cout << "[ �����? (1-��, 0-���) ][ ��� �����? (1-��, 0-���) ]\n";
//		(std::cin >> set >> val).get();
//		Q_temp.addAnswer(temp_str, set);
//	}
//	std::cout << "��������� �� ��������� (1-��, 0-���) --> ";
//	bool set = 0;	(std::cin >> set).get();
//	if (set) {
//		std::cout << "���������� -> ";
//		std::getline(std::cin, temp_str);
//		Q_temp.setComment(temp_str);
//	}
//	conteiner.emplace(Q_temp);
//	/*� ����������� ������ ����� ����� ������� ����� ���������� ������ ����������*/
//}
class Q_add :public command {	
public:
	Q_add() {opisanie = "�������� ����� ������. ";}
	virtual void execute(cont_question& temp) {
		temp.add_question();
	}
};




//void cont_question::dell_question() {
//	std::cout << "������� ����� ���������� ������� --> ";
//	int val; (std::cin >> val).get();
//	if (val<0 || val >conteiner.size()) {
//		std::cout << "������� � ����� ������� ���!\n";
//		return;
//	}
//	conteiner.erase(conteiner.begin()+val);
//}
//class Q_dell :public command {
//public:
//	Q_dell() { opisanie = "������� ������. "; }
//	virtual void execute(cont_question& temp) {
//		temp.add_question();
//	}
//};




//void cont_question::print_one() {
//	std::cout << "������� ����� ������� --> ";
//	int val; (std::cin >> val).get();
//	if (val>=0 && val < conteiner.size()) {	
//		It = conteiner.begin();
//		advance(It, val);
//		std::cout << val << ". ";
//		(*It).print();
//	}
//	else {
//		std::cout << "������� � ����� ������� ���!\n";
//	}
//}
//class Q_print_one :public command {
//public:
//	Q_print_one() { opisanie = "�������� ���� ������. "; }
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
//	Q_print_full() { opisanie = "�������� ��� �������. "; }
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
	//cout << "���� ������� �������" << endl;
}
class Q_savefile :public command {
public:
	Q_savefile() { opisanie = "��������� � ����. "; }
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
		/*�������� ������� ������*/
		std::string temp = "";
		std::getline(to_file, temp);  /*������ �������*/
		while (!to_file.eof()) {
			temp = "";
			std::getline(to_file, temp);  std::cout <<" --- "<< temp << std::endl;
			if (temp.find("������:") != std::string::npos) {
				if (Q_temp.getQuest().size() > 2) {
					conteiner.push_back(Q_temp);
					Q_temp = question(); //����������� ������
				}
				Q_temp.setQuest(temp.substr(temp.find("������:") + 8));
				std::cout << temp.substr(temp.find("������:") + 8) << std::endl;
				std::cout << "+������ \n ";
			}
			else if (temp.find("�� �����:") != std::string::npos) {
				Q_temp.addAnswer(temp.substr(temp.find("�� �����: ") + 10), 0);
				std::cout << "+��� \n ";
			}
			else if (temp.find("�����:") != std::string::npos) {
				Q_temp.addAnswer(temp.substr(temp.find("�����: ") + 7), 1);
				std::cout << "+�� \n ";
			}			
			else if (temp.find("����������: ") != std::string::npos) {
				Q_temp.setComment(temp.substr(temp.find("����������: ") + 12));
				std::cout << "+��� \n ";
			}			
		}
		system("pause");
		conteiner.push_back(Q_temp);
		to_file.close();
		 return true;
		//cout << "��������� ���������: " << countr << endl;
	}
	else return false;
}
class Q_readfile :public command {
public:
	Q_readfile() { opisanie = "�������� �� �����. "; }
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
	to_file << "<body bgcolor=\"springgreen\">\n";//��������� ��� �������� �������
	"<h1><center>������� ������ 1</center><br/></h1>,";
	to_file << "<h1><center>" << name_conteiner << "</center><br/></h1>\n\n"; //���������

	to_file << "</head>\n	</body>\n"; //��������� ��������� ��������� ����

	for (question tmp : conteiner) {
		tmp.writeHTML(to_file, val);
		val++;
	}

	to_file << "	</body>\n</html>"; //��������� ��������
	to_file.close();
	//cout << "���� ������� �������" << endl;
}
class Q_savefile_HTML :public command {
public:
	Q_savefile_HTML() { opisanie = "��������� � ���� HTML "; }
	virtual void execute(cont_question& temp) {
		std::cout << "������� ��� ����� -> ";
		std::string str;
		(std::cin >> str).get();
		std::cout << "������� ���� �������� (���������)-> ";
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
		/*�������� ������� ������*/
		std::string temp = "";
		//std::getline(to_file, temp);  /*������ �������*/
		while (!to_file.eof()) {
			temp = "";
			std::getline(to_file, temp);  //cout << countr++ << "   "<< temp << endl;
			if (temp.find("������:") != std::string::npos) {
				if (Q_temp.getQuest().size() > 2) {
					conteiner.push_back(Q_temp);
					Q_temp = question(); //����������� ������
				}
				temp = temp.erase(temp.find("</strong></div></div></li>"));
				Q_temp.setQuest(temp.substr(temp.find("������:") + 8));
				//cout << temp.substr(temp.find("������:") + 8) << endl;
				//cout << "+������ \n ";
			}
			else if (temp.find("�� �����:") != std::string::npos) {
				temp = temp.erase(temp.find("</del></font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("�� �����: ") + 10), 0);
				//cout << "+��� \n ";
			}
			else if (temp.find("�����:") != std::string::npos) {
				temp = temp.erase(temp.find("</font></p></div></div></li>"));
				Q_temp.addAnswer(temp.substr(temp.find("�����: ") + 7), 1);
				//cout << "+�� \n ";
			}
			else if (temp.find("����������:") != std::string::npos) {
				//std::cout << " --     " << temp << std::endl;
				temp = temp.erase(temp.find("</i></p></div></div></div>"));
				//std::cout << " ---    " << temp << std::endl;
				//std::cout << " 111-   " << temp.substr(temp.find("����������:") + 111) << endl;
				Q_temp.setComment(temp.substr(temp.find("����������:") + 111));
				//cout << "+��� \n ";
			}
		}
		//system("pause");
		conteiner.push_back(Q_temp);
		to_file.close();
		return true;
		//cout << "��������� ���������: " << countr << endl;
	}
	else return false;
}

class Q_readfile_HTML :public command {
public:
	Q_readfile_HTML() { opisanie = "�������� �� ����� HTML. "; }
	virtual void execute(cont_question& temp) {
		temp.read_fileHTML();
	}
};

void cont_question::open_file_Name(std::string& messege) {	
	if (if_type_file() == ".txt") {
		bool mes = read_fileTXT();
		if (!mes) messege += " ���� " + set_NameF() + " �� ������!";
		else{ messege = "���� " + set_NameF() + " ������� ��������!";	throw 1;}
	}
	if (if_type_file() == ".html") {
		bool mes = read_fileHTML();
		if (!mes) messege += "���� " + set_NameF() + " �� ������! ";
		else { messege = "���� " + set_NameF() + " ������� ��������!";	throw 1;}
	}
	//return messege;
};


std::string cont_question::find_file()
{
	std::string messege = "������! ";
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