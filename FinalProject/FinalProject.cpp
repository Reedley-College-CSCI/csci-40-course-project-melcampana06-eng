
// Melina Campana

#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
//#include < cstddef >



using namespace std;

const int MAX_SIZE = 50;
string bookArray[MAX_SIZE]; //array containg book titles, 50 max size

//Function Prototypes
char userPrompt();

void bubbleSort(string arr[], int n);
bool binarySearch(string array[], int size, string value);

void newBookEntry();
string searchForOldEntry();

string getPart(string line, int index);
void editPastEntry();

//Struct for all data related to the books
struct bookData {

	string bookTitle;
	string authorName;
	string bookGenre;
	int bookRating = 0;
	string bookReview;
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
		editPastEntry();
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
	if (found) { cout << "we good !! :P" << endl; }

	return found;
}


void newBookEntry() {

	bookData book; //Current book

	char letter = 'y';


	cout << "enter book name: " << endl;
	getline(cin, book.bookTitle);

	cout << "enter author first and last name: " << endl;
	getline(cin, book.authorName);

	cout << "what is the books genre ?" << endl;
	getline(cin, book.bookGenre);

	cout << "what rating would you give the book ?" << endl;
	cin >> book.bookRating;

	cout << "would you like to add a review ? " << endl 
		 << "('Y' or 'y' for yes, any other key for no)" << endl;
	cin >> letter;

	if (letter == 'y' || letter == 'Y') { 
		cin.ignore();
		cout << "Type Review: " << endl;
		getline(cin, book.bookReview); 
	}


	// OUTPUT FILE CODE 

	ofstream outputFile("bookTitles.txt", ios::app); //opens book output information file 
													 //and enables appended text 

	if (outputFile.is_open()) {    //checks if book output information file is open
		cout << "Output file opened" << endl;
	}
	else {
		cout << "Output File not opened" << endl;
	}

	if (outputFile.is_open()) {   //puts info in file
		outputFile << book.bookTitle << "   " << book.authorName << "   " << book.bookGenre 
			       << "   " << book.bookRating << "   " << book.bookReview << endl;
	}

	outputFile.close();  //closes book information file



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
	while (count < MAX_SIZE && getline(inputFile, bookArray[count])) {  //populates array
		cout << bookArray[count] << endl;	//DELETE THIS			    // turns everything lowercase
		bookArray[count] = toLower(bookArray[count]);
		count++;
	}
	inputFile.close();  //closes book information file
	


	bubbleSort(bookArray, count);



	cout << endl << "Sorted Check: " << endl; //DELETE THIS
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
		sortOutputFile << bookArray[i] << endl; //puts sorted array into new file
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
		bookArray[count] = toLower(extractTitle(line));   //Extracts book titles into array
		count++;										  //turns it lower case
	}

	inputFile.close();

	cout << "What title are you searching for? " << endl;
	getline(cin, title);    // gets title
	title = toLower(title); //turns it lower case

	// Perform binary search
	bool result = binarySearch(bookArray, count, title); 

	if (result)
		cout << "Book found!\n";
	else
		cout << "Book NOT found.\n";


	inputFile.open("bookTitlesSorted.txt"); 
	
	
	while (getline(inputFile, line)) {
		
		string bookName = toLower(getPart(line, 0));

		if (title == bookName) {

			bookName = getPart(line, 0);
			string authorName = getPart(line, 1);
			string genre = getPart(line, 2);
			string rating = getPart(line, 3);
			string review = getPart(line, 4);

			cout << "Title: " << bookName << endl;
			cout << "Author: " << authorName << endl;
			cout << "Genre: " << genre << endl;
			cout << "Rating: " << rating << "/5" << endl;
			cout << "review: " << review << endl;
			cout << endl;
		}
	}

	inputFile.close();
	return title;
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


void editPastEntry() {

	string titleToEdit;
	cout << "Enter the title you want to edit: " << endl;
	getline(cin, titleToEdit);

	string title = toLower(titleToEdit);

	ifstream inputFile("bookTitlesSorted.txt");
	ofstream tempFile("temp_edit.tmp");

	if (!inputFile || !tempFile) {
		cout << "Error opening file." << endl;
	}

	string line;
	bool found = false;

	while (getline(inputFile, line)) {

		string currentTitle = toLower(getPart(line, 0));

		if (currentTitle == title) {

			found = true;

			cout << "\nEntry found. Please enter new details.\n";

			bookData book;

			cout << "New Title: ";
			getline(cin, book.bookTitle);

			cout << "New Author: ";
			getline(cin, book.authorName);

			cout << "New Genre: ";
			getline(cin, book.bookGenre);

			cout << "New Rating: ";
			cin >> book.bookRating;
			cin.ignore();

			cout << "New Review: ";
			getline(cin, book.bookReview);

			// Write updated entry to temp file
			tempFile << book.bookTitle << "   "
				<< book.authorName << "   "
				<< book.bookGenre << "   "
				<< book.bookRating << "   "
				<< book.bookReview << endl;

		}
		else {
			tempFile << line << endl;   // keep original line
		}
	}

	inputFile.close();
	tempFile.close();

	if (found) {
		remove("bookTitlesSorted.txt");
		rename("temp_edit.tmp", "bookTitlesSorted.txt");
		cout << "Entry updated successfully.\n";
	}
	else {
		cout << "Entry NOT found. No changes made.\n";
		remove("temp_edit.tmp");
	}
}