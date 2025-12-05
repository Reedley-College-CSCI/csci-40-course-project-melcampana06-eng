
// Melina Campana

/*
This program takes in information about the users current read and logs it. 
The user is able to revist this log and edit it.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;
string bookArray[MAX_SIZE]; //array containg book titles, 50 max size

//Function Prototypes
string toLower(string s);
string extractTitle(const string& line);
char userPrompt();
void bubbleSort(string arr[], int n);
bool binarySearch(string array[], int size, string value);
void newBookEntry();
void searchForOldEntry();
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
	//makes each char in string s lower case
	for (char& c : s)
		c = tolower(c);
	return s;
}

string capitalizeWords(string s) {

	bool capNext = true; //when to capitalize

	//checks if c in string s is empty space
	//if true, next letter needs to be capitalized
	//else capNext is false
	for (char& c : s) {
		if (isspace(c)) {  
			capNext = true;
		}
		else if (capNext) {
			c = toupper(c);
			capNext = false;
		}
	}

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
	return found;
}

void newBookEntry() {

	bookData book; //Current book
	char letter = 'y'; //char for if user wants to add a review


	cout << "enter book name: " << endl;    //prompts user for book name
	getline(cin, book.bookTitle);

	cout << "enter author first and last name: " << endl; //prompts user for authors full name
	getline(cin, book.authorName);

	cout << "what is the books genre ?" << endl;   //prompts user for book genre
	getline(cin, book.bookGenre);

	cout << "what rating would you give the book (1 to 5) ?" << endl;  //prompts user for rating they give the book
	cin >> book.bookRating;

	do { 
		cout << "would you like to add a review ? " << endl				// asks user if they was to write a review
			<< "('Y' or 'y' for yes, 'n' or 'N' no)" << endl;
		cin >> letter;

		if (letter == 'y' || letter == 'Y') {   //uses 'y' or 'Y' to represent 'yes'
			cin.ignore();
			cout << "Write Review: " << endl;
			getline(cin, book.bookReview);     //takes in users review
		}
		else if (letter == 'n' || letter == 'N') { //uses 'n' or 'N' to represent 'no'
			book.bookReview = " ";                 // makes user review blank
		}
		else {
			cout << "------------------------" << endl;
			cout << " (invalid input, try again)" << endl;
			cout << "------------------------" << endl;
		}
	} while (!(letter == 'y' || letter == 'Y' || letter == 'n' || letter == 'N')); //iterates until letter is a valid answer



	// OUTPUT FILE CODE 
	ofstream outputFile("bookTitles.txt", ios::app); //opens book output information file 
													 //and enables appended text 

	cout << "------------------------" << endl;
	if (outputFile.is_open()) {    //checks if output file is open
		cout << "(output file opened)" << endl;
	}
	else {
		cout << "(output file not opened)" << endl;
	}

	if (outputFile.is_open()) {   //puts info in output file
		outputFile << book.bookTitle << "   " << book.authorName << "   " << book.bookGenre 
			       << "   " << book.bookRating << "   " << book.bookReview << endl;
	}

	outputFile.close();  //closes output file
	cout << "(output file closed)" << endl;


	// INPUT FILE CODE
	ifstream inputFile("bookTitles.txt");//opens input file 

	if (inputFile.is_open()) {    //checks if input file is open
		cout << "(input file opened)" << endl;
	}
	else {
		cout << "(input file not opened)" << endl;
	}

	int count = 0;
	while (count < MAX_SIZE && getline(inputFile, bookArray[count])) {  //populates array with input file info
		bookArray[count] = toLower(bookArray[count]);                   // turns everything lowercase
		count++;
	}
	inputFile.close();  //closes input file
	cout << "(input file closed)" << endl;
	
	bubbleSort(bookArray, count); //calls bubbleSort() to sort info alphabetically


	//SORTED FILE CODE
	ofstream sortOutputFile("bookTitlesSorted.txt"); //opens new output information file 

	if (sortOutputFile.is_open()) {    //checks if new output file is open
		cout << "(sorted output file opened)" << endl;
	}
	else {
		cout << "(sorted output file not opened)" << endl;
	}

	for (int i = 0; i < count; ++i) {
		sortOutputFile << bookArray[i] << endl; //puts sorted array into new output file
	}

	sortOutputFile.close();  //closes new sorted file
	cout << "(sorted output file closed)" << endl;
	cout << "------------------------" << endl;

	cout << endl;
	main();

}

void searchForOldEntry() {

	bool found = false;
	string title;
	bookData book;

	// INPUT FILE CODE
	ifstream inputFile("bookTitlesSorted.txt");//opens input file 

	cout << "------------------------" << endl;
	if (inputFile.is_open()) {    //checks if input file is open
		cout << "(input file opened)" << endl;
	}
	else {
		cout << "(input file not opened)" << endl;
	}

	int count = 0;
	string line;

	while (count < MAX_SIZE && getline(inputFile, line)) {
		bookArray[count] = toLower(extractTitle(line));   //Extracts book titles from file into the array
		count++;										  //turns title lower case
	}

	inputFile.close();
	cout << "(input file closed)" << endl;
	cout << "------------------------" << endl;

	cout << "What title are you searching for? " << endl;  //prompts user for title 
	getline(cin, title);									// gets title
	title = toLower(title);									//turns it lower case

	bool result = binarySearch(bookArray, count, title);    // Perform binary search


	cout << "------------------------" << endl;
	if (result) {
		cout << "(Book found!)" << endl;         //checks if title was found
	}
	else {
		cout << "(Book NOT found.)" << endl;
	}

	inputFile.open("bookTitlesSorted.txt"); 

	if (inputFile.is_open()) {    //checks if book information input file is open
		cout << "(input file opened)" << endl;
	}
	else {
		cout << "(input file not opened)" << endl;
	}
	cout << "------------------------" << endl;

	while (getline(inputFile, line)) {    //puts first line in the file into var line
		
		string bookName = toLower(getPart(line, 0)); //Makes bookName lowercase

		if (title == bookName) {  //checks if the users title is the same as the books

			//if true, goes through each part of the line
			//and assigns it to its correct variable
			bookName = getPart(line, 0);
			string authorName = getPart(line, 1);
			string genre = getPart(line, 2);
			string rating = getPart(line, 3);
			string review = getPart(line, 4);

			//couts variables
			cout << "Title: " << capitalizeWords(bookName) << endl;
			cout << "Author: " << capitalizeWords(authorName) << endl;
			cout << "Genre: " << capitalizeWords(genre) << endl;
			cout << "Rating: " << rating << "/5" << endl;
			cout << "review: " << capitalizeWords(review) << endl;
			cout << endl;
		}
	}

	//closes file
	cout << "------------------------" << endl;
	inputFile.close();
	cout << "(input file closed)" << endl;
	cout << "------------------------" << endl;

	cout << endl;
	main();
}

string getPart(string line, int index) {
	string spaces = "   ";     // The delimiter between fields (3 spaces)
	size_t position;

	// Loop to skip past the first index
	for (int i = 0; i < index; i++) {
		position = line.find(spaces);        // Find the next spaces
		if (position == string::npos)       // If no spaces are found,
			return "";                 // return empty string to avoid errors
		line = line.substr(position + spaces.length());
		// Remove everything up to and including the spaces
	}

	// Now get the next index after skipping previous ones
	position = line.find(spaces);

	if (position == string::npos)
		return line;    // last space

	return line.substr(0, position); // Return text from start up to the next space
}

void editPastEntry() {

	string titleToEdit;   //book user wants to edit
	cout << "Enter the title you want to edit: " << endl;  //Prompts user
	getline(cin, titleToEdit);								//gets title

	string title = toLower(titleToEdit);  //Makes title lowercase

	ifstream inputFile("bookTitlesSorted.txt");  //opens input file
	ofstream tempFile("temp_edit.tmp");		    //opens temporary output file

	if (!inputFile || !tempFile) {
		cout << "Error opening file." << endl;   //checks is files are open
	}

	string line;        //line in file
	bool found = false;  

	while (getline(inputFile, line)) {  //gets line from file

		string currentTitle = toLower(getPart(line, 0));  // assigns lowercase title to current title

		if (currentTitle == title) {  //checks if current title is the users title
			// if true, propmts the user to replace old entry with new one
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

	//closes files
	inputFile.close();
	tempFile.close();

	if (found) {   //puts changes back into original file
		remove("bookTitlesSorted.txt");
		rename("temp_edit.tmp", "bookTitlesSorted.txt");
		cout << "Entry updated successfully.\n";
	}
	else {
		cout << "Entry NOT found. No changes made.\n";
		remove("temp_edit.tmp");
	}

	cout << endl;
	main();
}