// insertionsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
void InsertionSort(unsigned int array[], unsigned int size);
void BubbleSort(unsigned int array[], unsigned int size);

int main()
{
	const unsigned int size = 10;
	unsigned int table[size] = { 3,4,9,8,22,1,57,90,13,0 };
	unsigned int table2[size] = { 3,4,9,8,22,1,57,90,13,0 };
	InsertionSort(table, size);
	std::cout << std::endl;
	BubbleSort(table2, size);
    return 0;
}

void InsertionSort(unsigned int array[], unsigned int size) {
	unsigned int pointer = 1;
	while (true) {
		if (pointer == size) {
			break;
		}
		for (int i = 0; i <= pointer; i++) {
			if (array[i] > array[pointer]) {
				int temp = array[i];
				array[i] = array[pointer];
				array[pointer] = temp;
			}
		}

		pointer++;
	}

	for (int i = 0; i < size; i++) {
		std::cout << "[ " << array[i] << " ]";
	}
}

void BubbleSort(unsigned int array[], unsigned int size) { //sorting function 

	int length = size - 2;

	while (true) {
		int changes = 0;
		for (int j = 0; j <= length; j++) { //sorting for 
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				changes++;
			}
		}
		if (changes == 0) {
			break; // breakin instructions when everything is done 
		}
	}

	for (int i = 0; i < size; i++) {
		std::cout << "[ " << array[i] << " ]";
	}


}

