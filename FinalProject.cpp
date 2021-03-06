// projectforexam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>




void CheckFilename(std::string filename);
void Encoding(std::string filename, int displacement);
void Decoding(std::string filename, int displacement);
int CheckIfExist(std::string filename);

int main(int argc, char * argv[])
{
	using namespace std;
	int idofoperation;
	int displacement;
	for (int i = 0; i < argc; i++) {
		if (argc < 4) {
			system("cls");
			cout << "Not enough parameters" << endl;
			exit(0);
		}else if(argc > 4) {
			system("cls");
			cout << "Too much parameters" << endl;
			exit(0);
		}else{
			
			displacement = atoi(argv[argc - 1]);

			string argcontainer_1 = argv[1];
			if (argcontainer_1 == "-e") {
				idofoperation = 1;
			}
			else if (argcontainer_1
				== "-d") {
				idofoperation = 2;
			}
			else if (argcontainer_1 == "-h") {
				system("cls");
				cout << "Correct grammar:" << endl;
				cout << "program.exe <switch> <name of file> <number of deplacement>" << endl;
				cout << "List of possible switches:" << endl;
				cout << "-e -- used to encode a file" << endl;
				cout << "-d -- used to decod a file" << endl;
				cout << "-h -- displays help" << endl;
				exit(0);
			}
			else {
				system("cls");
				cout << "Invalid parameter" << endl;
				exit(0);
			}

			
		}
	}

	string filename;
	int errorcode = 0; // no errors right now, just for testing
	string levelofd;
	
	int operation;

	filename = argv[2];
	CheckFilename(filename);
	if (CheckIfExist(filename) == 0) {
		system("cls");
		cout << "File does not exist";
		exit(0);
	}

	operation = idofoperation;

	if (operation == 1) {
		Encoding(filename, displacement);
	}
	if (operation == 2) {
		Decoding(filename, displacement);
	}
	
	
	return 0;
}
int CheckIfExist(std::string filename) {
	using namespace std;
	fstream FileToProcess;
	FileToProcess.open(filename + ".txt", ios::in);

	if (FileToProcess.good() == false) {
		return 0;
	}
	else {
		return 1;
	}
	
}


void Encoding(std::string filename, int displacement) {
	using namespace std;
	fstream FileToProcess;
	fstream EncodedFile;

	FileToProcess.open(filename + ".txt", ios::in);

	if (FileToProcess.good() == false) {
		cout << "File does not exist!" << endl;
		system("pause");
		exit(0);
	}

	EncodedFile.open("e" + filename + ".txt", ios::in);
	if (EncodedFile.good() == true) {
		EncodedFile.close();
		int counter = 2;
		while (true) {
			EncodedFile.open("e" + filename + "(" + to_string(counter) + ").txt", ios::in);
			if (EncodedFile.good() == false) {
				break;
			}
			EncodedFile.close();
			counter++;
		}


		EncodedFile.open("e" + filename + "(" + to_string(counter) + ").txt", ios::out | ios::app);
	}
	else {
		EncodedFile.open("e" + filename + ".txt", ios::out | ios::app);
	}
	string TempLine;


	while (getline(FileToProcess, TempLine)) {
		string EncodedLine = "";

		for (int i = 0; i < TempLine.length(); i++) {
			char actualchar = TempLine[i];
			char echar = actualchar + displacement;
			EncodedLine = EncodedLine + echar;
		}
		EncodedFile << EncodedLine << endl;
	}


	FileToProcess.close();
	EncodedFile.close();
}

void Decoding(std::string filename, int displacement) {
	using namespace std;
	fstream FileToProcess;
	fstream DecodedFile;

	FileToProcess.open(filename + ".txt", ios::in);

	if (FileToProcess.good() == false) {
		cout << "File does not exist!" << endl;
		system("pause");
		exit(0);
	}

	DecodedFile.open("e" + filename + ".txt", ios::in);
	if (DecodedFile.good() == true) {
		DecodedFile.close();
		int counter = 2;
		while (true) {
			DecodedFile.open("e" + filename + "(" + to_string(counter) + ").txt", ios::in);
			if (DecodedFile.good() == false) {
				break;
			}
			DecodedFile.close();
			counter++;
		}

		DecodedFile.open("e" + filename + "(" + to_string(counter) + ").txt", ios::out | ios::app);
	}
	else {
		DecodedFile.open("e" + filename + ".txt", ios::out | ios::app);
	}

	string TempLine;

	while (getline(FileToProcess, TempLine)) {
		string DecodedLine = "";

		for (int i = 0; i < TempLine.length(); i++) {
			char actualchar = TempLine[i];
			char echar = actualchar - displacement;
			DecodedLine = DecodedLine + echar;
		}
		DecodedFile << DecodedLine << endl;
	}
	FileToProcess.close();
	DecodedFile.close();
}

void CheckFilename(std::string filename) {

	int error = 0;
	for (int i = 0; i < filename.length(); i++) {
		char actualchar = filename[i]; // convertin' to char
		int v = actualchar; // getting ascii value of character
		if (isalnum(filename[i])) {
		}
		else if (v == 47 || v == 92 || v == 124 || v == 58 || v == 42 || v == 34 || v == 63 || v == 60 || v == 62) {// forbidden asciis: 47,92,124, 58, 42,34,63,60,62
			error = 1;
			break;
		}
	}

	if (error == 0) {
		std::cout << std::endl;
	}
	else {
		system("cls");
		std::cout << "Invalid characters in file name"<<std::endl;
		exit(0);
		}
}

