// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.


// Melina Campana

#include <iostream>
#include <fstream>

using namespace std;

struct bookData {



};

int main()
{
	string bookName; //holds book name
	
	ofstream outputFile("bookInfo.txt", ios::app); //opens book information file 
												  //and enables appended text 

	if (outputFile.is_open()) {    //checks if book information file is open
	   cout << "Book Information file open" << endl;
	}
	else {
	   cout << "File not opened" << endl;
	}
	
	cout << "enter book name: " << endl;
	cin >> bookName;
	
	if (outputFile.is_open()) { 
	   outputFile << bookName << endl;
	   outputFile.close();  //closes book information file
	}
	else {
	   cout << "File not opened" << endl;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
