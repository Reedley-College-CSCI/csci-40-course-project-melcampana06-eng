
// Melina Campana

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include < cstddef >


using namespace std;

const int MAX_SIZE = 50;
string bookArray[MAX_SIZE]; //array containg book titles, 50 max size

//Function Prototypes
char userPrompt();
void newBookEntry();
string searchForOldEntry();
void bubbleSort(string arr[], int n);
bool binarySearch(string array[], int size, string value);
string getPart(string line, int index);



//Struct for all data related to the books
struct bookData {

	string bookTitle;
	string authorName;
	string bookGenre;
	int bookRating = 0;

	//int readingStartDate;
//	int readingEndDate;
	//string bookReview;
};


int main()
{
	char userChoice = userPrompt();

	if ( userChoice == 'a') {

		newBookEntry();
	}
	else if (userChoice == 'b') {

		searchForOldEntry();

	}
	else if (userChoice == 'c') {

		
	}
	else if (userChoice == 'd') {

		return 0;
	}
	else {

		cout << "invalid input" << endl;
	}
	

	return 0;
}

string toLower(string s) {
	for (char& c : s)
		c = tolower(c);
	return s;
}


string extractTitle(const string& line) {
	return line.substr(0, line.find('   '));   // return everything before the first space
}


char userPrompt() {

	char letter;

	cout << "welcome to your book log!\n" << endl;
	cout << "if you want to add a new entry, enter 'a'\n";
	cout << "if you want to search for an old entry, enter 'b'\n";
	cout << "if you want edit a past entry, enter 'c'\n";
	cout << "if you want to exit, enter 'd'\n";

	cin >> letter;
	cin.ignore(); // clear leftover newline
	return letter;
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


bool binarySearch(string array[], int size, string value)
{
	int first = 0; // First array element
	int last = size - 1; // Last array element
	int middle; // Mid point of search
	bool found = false; // Flag

	while (!found && first <= last)
	{
		middle = (first + last) / 2; // Calculate mid point
		if (array[middle] == value) // If value is found at mid
		{
			found = true;
		}
		else if (array[middle] > value) // If value is in lower half
			last = middle - 1;
		else
			first = middle + 1; // If value is in upper half
	}
	if (found = true) { cout << "we good !! :P" << endl; }

	return found;
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

	//orderByTitle(book, authorFirstName, authorLastName);


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
		outputFile << book.bookTitle << "   " << authorFirstName.authorName << "   " << authorLastName.authorName

			<< "   " << genre.bookGenre << "   " << rating.bookRating << endl;//puts title in file
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
		bookArray[count] = toLower(bookArray[count]);
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

}


string searchForOldEntry() {

	bool found = false;
	string title;
	bookData book;

	// INPUT FILE CODE
	ifstream inputFile("bookTitlesSorted.txt");//opens book information input file 
	//and enables appended text 

	int count = 0;
	string line;

	while (count < MAX_SIZE && getline(inputFile, line)) {
		bookArray[count] = toLower(extractTitle(line));
		count++;
	}

	inputFile.close();

	cout << "What title are you searching for? " << endl;
	cin.ignore();
	getline(cin, title);
	title = toLower(title);

	// Perform binary search
	bool result = binarySearch(bookArray, count, title);

	if (result)
		cout << "Book found!\n";
	else
		cout << "Book NOT found.\n";



	inputFile.open("bookTitlesSorted.txt"); // <-- FIX: reopen 
	getline(inputFile, line);

	string bookName = getPart(line, 0);
	string authorName = getPart(line, 1);
	string genre = getPart(line, 2);
	string rating = getPart(line, 3);

	//ss >> book.bookTitle >> book.authorName >> book.bookGenre >> book.bookRating; 
	cout << "Title: " << bookName << endl
		<< "Author: " << authorName << endl
		<< "Genre: " << genre << endl
		<< "Rating: " << rating << endl;
	cout << endl;
	return title;
	inputFile.close();
}


string getPart(string line, int index) {
	string delim = "   ";
	size_t pos;

	for (int i = 0; i < index; i++) {
		pos = line.find(delim);
		if (pos == string::npos ) return "";   // <-- prevent crash
		line = line.substr(pos + delim.length());
	}

	pos = line.find(delim);
	if (pos == string::npos)
		return line;   // last field (safe)

	return line.substr(0, pos);
}