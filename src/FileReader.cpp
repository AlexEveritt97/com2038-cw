#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>

using namespace std;

// method for printing the table in the correct format with consistent spacing
template<typename T> void FileReader::printElement(T t, const int& width)
{
	const char separator = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

// outputting the headers in the correct format as required 
void FileReader::printHeaders(int total) 
{
	cout << "There are " << total << " dog(s) in the inventory, which are:" << '\n' << '\n';
	cout << "Name     Breed    Colour   Dad      Mom" << '\n';
	cout << "-----------------------------------------" << '\n';
}

// method for the user to input a dogs name and output the paternal tree onto the cmd line
void FileReader::paternalTree()
{
	string inputName;
	cout << "Enter the dog's name to find its paternal tree: ";

	// get the user input from the command line for the dogs name
	getline(cin, inputName);

	cout << '\n';

	bool inInventory = false;

	for(unsigned int i = 0; i < inventory.size(); i++) {
		if(inputName == inventory[i].getName()) {
			Dog *dog = &inventory[i];
			inInventory = true;
			cout << inputName + " <-- " << traverseTree(dog, "") + "\n" << endl;
		}	
	}

	// input string to exit the program and clear the memory using "EXIT"
	if(inputName ==  "EXIT") {
		vector<Breed>().swap(inventory);
		exit(1);
	}

	if(!inInventory) {
		cout << inputName + " was not found in the inventory!" << endl;
		cout << '\n';
	}

	paternalTree();
}

string FileReader::traverseTree(Dog *dog, string output) 
{
	Dog *ptr = dog;
	// base case
	if(ptr -> getDad() -> getName() == "N/A") {
		output += "[END]";
		return output;
	}
	else {
		output += (ptr -> getDad() -> getName() + " <-- ");
		return traverseTree(ptr -> getDad(), output);
	}
}

// count the total number of dogs in the inventory
int FileReader::totalDogs(string filename)
{
	// input stream
	ifstream file;
	file.open(filename.c_str());

	if(file.fail()) {
		// if file fails to open output an error and exit
		cerr << "Error opening file: " << strerror(errno);
		exit(0);
	}

	string line;
	int total = 0;
	string line2;

	while(!file.eof()) {
		file >> line2;
		// total the no of dogs in the file
		total++;
	}

	return total;
}

// reading the csv file for the inventory input
void FileReader::fileReader(string filename) 
{
	// open input stream for the file
	ifstream file;
	
	// open the file stream for the required file
	file.open(filename.c_str());

	// ensure the file can be opened
	if(file.fail()) {
		// if fail output and error and exit
		cerr << "Error opening file: " << strerror(errno);
		exit(1);
	}

	// string for the line input
	string line;

	int total = totalDogs(filename);

	printHeaders(total);

	const int nameWidth = 9;

	// while the file is not at the end of the lines in the file
	while(!file.eof()) {

		// add the current line from the file to the string
		file >> line;

		// string tokenizer for each element seperated by commas
		istringstream ss(line);
		string token;
		int counter = 0;

		// fields to build a breed object
		string breed;
		string name;
		string colour;
		string dadName;
		string momName;

		// split the line up by commas
		while(getline(ss, token, ',')) {

			// depending on which token the word is in the line apply different
			// rules accordingly using a switch statement
			counter++;

			// if there is no token then have N/A in the table instead
			if(token == "") {
				token = "N/A";
			}
			switch(counter) {
				case 1:
					// breed
					if(token.compare("Husky") ==0 || token.compare("Corgi") == 0 || token.compare("Boxer") == 0){
						breed = token;
					}
					else{
						throw invalid_argument(token+ " is not a valid breed name - must be Husky, Corgi or Boxer");
					}
					break;
				case 2:
					// name
					name  = token;
					printElement(name, nameWidth);
					printElement(breed, nameWidth);
					break;

				case 3: 	
					// colour
					colour = token;
					printElement(token, nameWidth);
					break;

				case 4:
					// dads name
					dadName = token;
					printElement(token, nameWidth);
					break;

				case 5:
					// moms name
					momName = token;
					printElement(token, nameWidth);
					break;

				default:
					cout << "error" << endl;
					break;
			}

			
 		}

		// at the end of the line add N/A if last token is null
		if(counter == 4) {
			printElement("N/A", nameWidth);
		}
		cout << '\n';

		// create a breed object based on the tokens in the line
		Breed dog(name, colour, breed);

		bool hasDad, hasMom;

		// set the dad/mom pointers to the correct object
		for(unsigned int i = 0; i < inventory.size(); i++) {
			if(!inventory.empty()) {

				if(inventory[i].getName() == dadName) {
					Breed *ptr1 = &inventory[i];
					dog.setDad(ptr1);
					hasDad = true;
				}

				if(inventory[i].getName() == momName) {
					Breed *ptr2 = &inventory[i];
					dog.setMom(ptr2);
					hasMom = true;
				}
			}	
		}

		if(!hasDad || !hasMom) {
			Breed dog2("N/A", "black", "Husky");

			Breed *ptr3 = &dog2;
			dog.setDad(ptr3);
			dog.setMom(ptr3);

		}

		// add the dog to the inventory vector
		inventory.push_back(dog);

	}
	cout << '\n';

	paternalTree();
}
