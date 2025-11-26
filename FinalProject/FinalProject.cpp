// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


// Melina Campana

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void bubbleSort(string arr[], int num);
char userPrompt();
void addBookEntry();

struct bookData {

	string bookTitle;

	/*string authorName;
	string bookGenre;
	float bookRating;

	int readingStartDate;
	int readingEndDate;
	string bookReview;*/
};

int main()
{

	bookData book; //Current book

	char userChoice;
	
	userChoice = userPrompt();

	if (  userChoice == 'a') {

		addBookEntry();
		
	}
	else {

		cout << "bye bye" << endl;
	}

	return 0;

}

void bubbleSort(string arr[], int num) {
	bool swapped;
	for (int i = 0; i < num - 1; ++i) {
		swapped = false;
		for (int j = 0; j < num - 1 - i; ++j) {
			// Compare adjacent strings lexicographically
			if (arr[j] > arr[j + 1]) {
				// If they are in the wrong order, swap them
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		// If no two elements were swapped by inner loop, then array is sorted
		if (!swapped) {
			break;
		}
	}
}

char userPrompt() {
	char letter;

	cout << "Welcome to your book log! \n" << endl;
	cout << "If you wish to add a new entry enter 'a'\n";
	cout << "If you want to view a past entry enter 'b'\n";
	cout << "If you want to exit enter 'c'\n";
	cin >> letter;

	return letter;
}

void addBookEntry() {

	const int MAX_SIZE = 50;
	string bookArray[MAX_SIZE]; //array containg book titles, 50 max size
	bookData book;



	// OUTPUT FILE CODE 
	ofstream outputFile("bookInfo.txt", ios::app); //opens book output information file 
	//and enables appended text 

	if (outputFile.is_open()) {    //checks if book output information file is open
		cout << "Output file opened" << endl;
	}
	else {
		cout << "Output File not opened" << endl;
	}

	cout << "enter book name: " << endl;

	getline(cin, book.bookTitle);

	if (outputFile.is_open()) {
		outputFile << book.bookTitle << endl;//puts title in file
	}

	outputFile.close();  //closes book information file
	// ^^^ WORKS DONT CHANGE 



	// INPUT FILE CODE
	ifstream inputFile("bookInfo.txt");//opens book information input file 
	//and enables appended text 


	if (inputFile.is_open()) {    //checks if book information input file is open
		cout << "Input file opened" << endl;
	}
	else {
		cout << "Input file not opened" << endl;
	}

	int count = 0;
	while (count < MAX_SIZE && getline(inputFile, bookArray[count])) {
		cout << bookArray[count] << endl;
		count++;
	}
	inputFile.close();  //closes book information file
	// ^^^ ALSO WORKS




	bubbleSort(bookArray, count);

	cout << endl << "Sorted Check: " << endl;
	for (int i = 0; i < count; ++i) {
		cout << bookArray[i] << endl;
	}


	//SORTED FILE CODE

	ofstream sortOutputFile("sortedBookInfo.txt"); //opens book output information file 
	//and enables appended text 

	if (sortOutputFile.is_open()) {    //checks if book output information file is open
		cout << "Sorted Output file opened" << endl;
	}
	else {
		cout << "Sorted Output File not opened" << endl;
	}

	for (int i = 0; i < count; ++i) {
		sortOutputFile << bookArray[i] << endl;
	}

	sortOutputFile.close();  //closes book information file

}

