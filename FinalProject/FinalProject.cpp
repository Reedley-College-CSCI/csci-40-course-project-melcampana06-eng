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

const int MAX_SIZE = 50;
string bookArray[MAX_SIZE]; //array containg book titles, 50 max size

//Function Prototypes
void bubbleSort(string arr[], int n);

void newBookEntry();
char userPrompt();

//Struct for all data related to the books
struct bookData {

	string bookTitle;
	string authorName;
	string bookGenre;
	int bookRating;

	//int readingStartDate;
//	int readingEndDate;
	//string bookReview;
};


bookData orderByTitle(bookData currBook, bookData firstName, bookData lastName);

int main()
{
	char userChoice = userPrompt();

	if ( userChoice == 'a') {

		newBookEntry();
	}
	else if (userChoice == 'b') {
	
	}
	else if (userChoice == 'c') {

		return 0;
	}
	else {

		cout << "invalid input" << endl;
	}
	

	return 0;
}

void bubbleSort(string arr[], int n) {
	bool swapped;
	for (int i = 0; i < n - 1; ++i) {
		swapped = false;
		for (int j = 0; j < n - 1 - i; ++j) {
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


int binarySearch(int array[], int size, int value)
{
	int first = 0, // First array element
		last = size - 1, // Last array element
		middle, // Mid point of search
		position = -1; // Position of search value
	bool found = false; // Flag
	while (!found && first <= last)
	{
		middle = (first + last) / 2; // Calculate mid point
		if (array[middle] == value) // If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (array[middle] > value) // If value is in lower half
			last = middle - 1;
		else
			first = middle + 1; // If value is in upper half
	}
	return position;
}


void newBookEntry() {

	bookData book; //Current book
	bookData authorFirstName;
	bookData authorLastName;

	cout << "enter book name: " << endl;
	getline(cin, book.bookTitle);

	cout << "enter author first and last name: " << endl;
	cin >> authorFirstName.authorName;
	cin >> authorLastName.authorName;

	orderByTitle(book, authorFirstName, authorLastName);

}

void searchForOldEntry() {

	bool found = false;

	// INPUT FILE CODE
	ifstream inputFile("bookTitlesSorted.txt");//opens book information input file 
	//and enables appended text 


	if (inputFile.is_open()) {    //checks if book information input file is open
		cout << "Input file opened" << endl;
	}
	else {
		cout << "Input file not opened" << endl;
	}


	bool found = false;
	int spaceCount = 0;
	char space = ' ';
	char letter;
	string line;
	bookData book;

	while (found = false) {

		while (getline(inputFile,line )) {

			for (int i = 0; i < line.length(); ++i) {
				letter = line[i]; // Access character at index i

				for (int i = 0; i < 3; ++i) {
					if (!(letter = space)) {
						cin >> book.bookTitle;

					}
				}
			
			}
		}
	}



	inputFile.close();  //closes book information file
	// ^^^ ALSO WORKS
}

bookData orderByTitle(bookData currBook, bookData firstName, bookData lastName) {

	bookData genre;
	bookData rating;

	cout << "what is the books genre ?" << endl;
	cin >> genre.bookGenre;

	cout << "what rating would you give the book ?" << endl;
	cin >> rating.bookRating;

	// OUTPUT FILE CODE 
	ofstream outputFile("bookTitles.txt", ios::app); //opens book output information file 
	//and enables appended text 

	if (outputFile.is_open()) {    //checks if book output information file is open
		cout << "Output file opened" << endl;
	}
	else {
		cout << "Output File not opened" << endl;
	}

	if (outputFile.is_open()) {
		outputFile << currBook.bookTitle << "   "  << lastName.authorName << "   " << firstName.authorName 
			
			<< "   "  << genre.bookGenre << "   " << rating.bookRating << endl;//puts title in file
	}

	outputFile.close();  //closes book information file
	// ^^^ WORKS DONT CHANGE 



	// INPUT FILE CODE
	ifstream inputFile("bookTitles.txt");//opens book information input file 
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

	ofstream sortOutputFile("bookTitlesSorted.txt"); //opens book output information file 
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

	return currBook;
}


char userPrompt() {

	char letter;

	cout << "welcome to your book log! :D\n" << endl;
	cout << "if you want to add a new entry, enter 'a'\n";
	cout << "if you want to search for an old entry, enter 'b'\n";
	cout << "if you want to exit, enter 'c'\n";

	cin >> letter;
	cin.ignore(); // clear leftover newline
	return letter;
}

