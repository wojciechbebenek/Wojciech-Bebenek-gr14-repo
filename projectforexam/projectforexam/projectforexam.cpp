// projectforexam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
void CheckFilename(std::string filename);
int main()
{
	using namespace std;

	string filename;

	int errorcode = 0;

	

	cout << "Give me name of the file (without extension buddy) that is in program's folder" << endl;
	getline(cin, filename); //gettin' da line

	
	CheckFilename(filename);

    return 0;
}

void CheckFilename(std::string filename) {

	std::string errors[11];
	errors[1] = "Invalid characters in file name";
	int errorcode = 0;

	for (int i = 0; i < filename.length();i++) {
		char actualchar = filename[i]; // convertin' to char
		int v = actualchar; // gettin ascii value of character
		if (isalnum(filename[i])) {
			//cout << filename[i];
		}
		else if (v == 47 || v == 92 || v == 124 || v == 58 || v == 42 || v == 34 || v == 63 || v == 60 || v == 62) {// forbidden asciis: 47,92,124, 58, 42,34,63,60,62
			errorcode = 1;
			break;
		}


	}

	if (errorcode == 0) {
		std::cout << std::endl << "cool name";
	}
	else {
		for (int i = 1; i < 11; i++) {
			if (errorcode == i) {
				std::cout << std::endl << errors[i];
			}
		}

	}
}

/*
32-126 asciis with chars

Asciis a-z
65 97
90 122
*/