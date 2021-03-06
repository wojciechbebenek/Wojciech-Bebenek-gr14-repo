#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

void DisplayHelp();
void DisplayLog(std::string filename_1);
int CheckFileName(std::string filename_1, std::string filename_2);
void Diff(std::string filename_1, std::string filename_2);
void Commit(std::string filename_1, std::string filename_2);
void Update(std::string filename_1, std::string filename_2);

struct Differences {
	int NumberOfLine;
	std::string Content;
	std::string ContentM;
	Differences *_pointer;
};

int main(int argc, char * argv[])
{
	using namespace std;
	int idofoperation;

	for (int i = 0; i < argc; i++) {
		if (argc > 4) {
			system("cls");
			cout << "Too much parameters" << endl;
			exit(0);
		}
		else {
			string argcontainer_1 = argv[1];
			if (argcontainer_1 == "-h") {//display help, id:5
				idofoperation = 5;
			}
			else if (argcontainer_1 == "-l") {//display log file of any file
				idofoperation = 4;
			}
			else {
				if (argc < 4) {
					system("cls");
					cout << "Not enough parameters" << endl;
					exit(0);
				}
				else {
					if (argcontainer_1 == "-d") {//diff, comparing two files, id:1
						idofoperation = 1;
					}
					else if (argcontainer_1 == "-c") {//commit, saving changes to main file, id:2
						idofoperation = 2;
					}
					else if (argcontainer_1 == "-u") {//update, copying main file to branch file
						idofoperation = 3;
					}
				}
			}
		}
	}//end of the beginning;


	 //	int operation;

	if (idofoperation == 5) { //help
		DisplayHelp();
	}


	string filename_1;//temp one
	string filename_2;//main one
	filename_1 = argv[2];
	if (idofoperation == 4) {//log
		DisplayLog(filename_1);
	}
	filename_2 = argv[3];

	if (idofoperation == 4) {//log
		DisplayLog(filename_1);
	}

	if (CheckFileName(filename_1, filename_2) == 0) {
		system("cls");
		cout << "File does not exist!";
		exit(0);
	}


	if (idofoperation == 3) {//update
		Update(filename_1, filename_2);
		exit(0);
	}
	else if (idofoperation == 2) {//commit
		Commit(filename_1, filename_2);
		exit(0);
	}
	else if (idofoperation == 1) {//diff
		Diff(filename_1, filename_2);
		exit(0);
	}
	return 0;
}

void DisplayHelp() {
	using namespace std;
	system("cls");
	cout << "Correct grammar:" << endl;
	cout << "program.exe <switch> <name of file1> <name of file2>" << endl;
	cout << "file1 -- the file you are working on" << endl;
	cout << "file2 -- the main file" << endl;
	cout << "List of possible switches:" << endl;
	cout << "-d -- displays the difference between two files" << endl;
	cout << "-c -- commits changes to main file" << endl;
	cout << "-u -- copying file2 data into file1" << endl;
	cout << "-l -- shows change logs of file" << endl;
	cout << "It has special grammar:" << endl;
	cout << "program.exe -l <name of file>" << endl;
	cout << "-h -- displays help" << endl;
	exit(0);
}

int CheckFileName(std::string filename_1, std::string filename_2) {
	using namespace std;
	fstream file1;
	fstream file2;
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);

	if (file1.good() == false) {
		return 0;
	}
	else {
		if (file2.good() == false) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

/////////////////////////DIFF
void add_end(int NumberOfLine, std::string Content, std::string ContentM, Differences*&head) {
	Differences* Tail = new Differences{ NumberOfLine,Content, ContentM, nullptr };

	if (head == nullptr) {
		head = Tail;
	}
	else {
		Differences* guardian = head;
		while (guardian->_pointer != nullptr) {
			guardian = guardian->_pointer;
		}
		guardian->_pointer = Tail;
	}
}

void remove_list(Differences *&head) {
	Differences* Helper;
	while (head != nullptr) {
		Helper = head;
		head = Helper->_pointer;
		delete Helper;
	}
}

void Diff(std::string filename_1, std::string filename_2) {
	using namespace std;
	fstream file1;
	fstream file2;
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);
	string Templine1;
	string Templine2;
	string DiffLine[10];
	int counter1 = 1;
	int counter2 = 1;
	int line = 1;
	int anotherone = 0;
	while (getline(file1, Templine1)) {
		counter1++;
	}
	while (getline(file2, Templine2)) {
		counter2++;
	}
	file1.close();
	file2.close();
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);

	Differences *start;
	start = nullptr;

	if (counter1 >= counter2) {
		while (getline(file1, Templine1)) {
			if (counter2 > line) {
				getline(file2, Templine2);
			}
			else {
				Templine2 = "";
			}

			if (Templine1 != Templine2) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	else {
		while (getline(file2, Templine2)) {
			if (counter1 > line) {
				getline(file1, Templine1);
			}
			else {
				Templine1 = "";
			}

			if (Templine2 != Templine1) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	file1.close();
	file2.close();
	//holder;
	cout << "# | File1 | File2" << endl;
	cout << "---------------------------" << endl;
	while (start) {
		cout << start->NumberOfLine << " | " << start->Content << " || " << start->ContentM << endl;
		start = start->_pointer;
	}
	remove_list(start);
}

void Commit(std::string filename_1, std::string filename_2) {
	using namespace std;
	fstream file1;
	fstream file2;
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);
	string Templine1;
	string Templine2;
	int counter1 = 1;
	int counter2 = 1;
	int line = 1;
	int anotherone = 0;
	while (getline(file1, Templine1)) {
		counter1++;
	}
	while (getline(file2, Templine2)) {
		counter2++;
	}
	file1.close();
	file2.close();
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);

	Differences *start;
	start = nullptr;

	if (counter1 >= counter2) {
		while (getline(file1, Templine1)) {
			if (counter2 > line) {
				getline(file2, Templine2);
			}
			else {
				Templine2 = "";
			}

			if (Templine1 != Templine2) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	else {
		while (getline(file2, Templine2)) {
			if (counter1 > line) {
				getline(file1, Templine1);
			}
			else {
				Templine1 = "";
			}

			if (Templine2 != Templine1) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	file1.close();
	file2.close();

	// FUNCTION THAT SAVES LOG INTO FILE

	fstream log_file;
	log_file.open(filename_2 + "_log.txt", ios::out | ios::app);
	while (start) {
		log_file << "Changed line #" << start->NumberOfLine << endl << "From: " << start->ContentM << endl << "To: " << start->Content << endl;
		start = start->_pointer;
	}
	log_file.close();
	//
	remove_list(start);

	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in | ios::out | ios::trunc);

	while (getline(file1, Templine1)) {
		file2 << Templine1 << endl;
	}

	file1.close();
	file2.close();
}

void DisplayLog(std::string filename_1) {
	using namespace std;
	fstream file1;
	file1.open(filename_1 + "_log.txt", ios::in);
	string Templine1;
	if (file1.good() == false) {
		system("cls");
		cout << "File does not exist!" << endl;
		exit(0);
	}
	else {
		system("cls");
		while (getline(file1, Templine1)) {
			cout << Templine1 << endl;
		}
		file1.close();
		exit(0);
		//file1.open(filename_1."_log.txt", ios::out | ios::app);
	}
}

void Update(std::string filename_1, std::string filename_2) {
	using namespace std;
	fstream file1;
	fstream file2;
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);
	string Templine1;
	string Templine2;
	int counter1 = 1;
	int counter2 = 1;
	int line = 1;
	int anotherone = 0;
	while (getline(file1, Templine1)) {
		counter1++;
	}
	while (getline(file2, Templine2)) {
		counter2++;
	}
	file1.close();
	file2.close();
	file1.open(filename_1 + ".txt", ios::in);
	file2.open(filename_2 + ".txt", ios::in);

	Differences *start;
	start = nullptr;

	if (counter1 >= counter2) {
		while (getline(file1, Templine1)) {
			if (counter2 > line) {
				getline(file2, Templine2);
			}
			else {
				Templine2 = "";
			}

			if (Templine1 != Templine2) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	else {
		while (getline(file2, Templine2)) {
			if (counter1 > line) {
				getline(file1, Templine1);
			}
			else {
				Templine1 = "";
			}

			if (Templine2 != Templine1) {
				add_end((line), Templine1, Templine2, start);
				anotherone++;
			}
			line++;
		}
	}
	file1.close();
	file2.close();

	// FUNCTION THAT SAVES LOG INTO FILE

	fstream log_file;
	log_file.open(filename_1 + "_log.txt", ios::out | ios::app);
	while (start) {
		log_file << "Changed line #" << start->NumberOfLine << endl << "From: " << start->Content << endl << "To: " << start->ContentM << endl;
		start = start->_pointer;
	}
	log_file.close();
	//
	remove_list(start);

	file1.open(filename_1 + ".txt", ios::in | ios::out | ios::trunc);
	file2.open(filename_2 + ".txt", ios::in);

	while (getline(file2, Templine2)) {
		file1 << Templine2 << endl;
	}

	file1.close();
	file2.close();
}
