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
	// set the fill based on the width input and then the input string t
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
	const int nameWidth = 9;

	// print all the elements in the inventory vector to the table
	if(first) {
		for(unsigned int i = 0; i < inventory.size(); i++) {
			printElement(inventory[i].getName(), nameWidth);
			printElement(inventory[i].getBreedName(), nameWidth);
			printElement(inventory[i].getColor(), nameWidth);
			printElement(inventory[i].getDad() -> getName(), nameWidth);
			printElement(inventory[i].getMom() -> getName(), nameWidth);
			cout << '\n';
		}
		first = false;
	}

	cout << '\n';
	string inputName;
	cout << "Enter the dog's name to find its paternal tree: ";

	// get the user input from the command line for the dogs name
	getline(cin, inputName);

	cout << '\n';

	bool inInventory = false;

	// loop through the inventory
	for(unsigned int i = 0; i < inventory.size(); i++) {
		if(inputName == inventory[i].getName()) {
			// if the input name matches a dog in the inventory start traversing the parental tree
			Dog *dog = &inventory[i];
			inInventory = true;
			cout << inputName + " <-- " << traverseTree(dog, "") << endl;
		}	
	}

	// input string to exit the program and clear the memory using "EXIT"
	if(inputName ==  "EXIT") {
		// swaps inventory to empty array to clear memory
		vector<Breed>().swap(inventory);
		exit(1);
	}

	if(!inInventory) {
		// if the dog is not in the inventory print the input name and the string
		cout << inputName + " was not found in the inventory!" << endl;
	}

	// call the method recursively to allow the user to see more paternal trees
	paternalTree();
}

// recursive algorithm to return the paternal tree string
string FileReader::traverseTree(Dog *dog, string output) 
{
	Dog *ptr = dog;
	// base case
	// when the name of the parent object is N/A
	if(ptr -> getDad() -> getName() == "N/A") {
		output += "[END]";
		return output;
	}
	// recursive case 
	// to build the tree string by adding the dads name each time
	else {
		output += (ptr -> getDad() -> getName() + " <-- ");
		return traverseTree(ptr -> getDad(), output);
	}
}

// count the total number of dogs in the inventory by counting number of line files
int FileReader::totalDogs(string filename)
{
	// input stream
	ifstream file;
	file.open(filename.c_str());

	// error handling for if the file is correct or not
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
	first = true;

	// open input stream for the file
	ifstream file;
	
	// open the file stream for the required file
	file.open(filename.c_str());

	// ensure the file can be opened - error handling
	if(file.fail()) {
		// if fail output and error and exit
		cerr << "Error opening file: " << strerror(errno);
		exit(1);
	}

	// string for the line input
	string line;

	int total = totalDogs(filename);

	// print the headers for the inventory table
	printHeaders(total);

	// while the file is not at the end of the lines in the file
	while(!file.eof()) {

		// add the current line from the file to the string
		file >> line;

		// string tokenizer for each element seperated by commas
		istringstream ss(line);
		string token;
		int counter = 0;

		// fields to build a breed object
		string breed, name, colour, dadName, momName;

		// split the line up by commas
		while(getline(ss, token, ',')) {

			// depending on which token the word is in the line apply different
			// rules accordingly using a switch statement
			counter++;

			// if there is no token then have N/A in the table instead
			if(token == "") {
				token = "N/A";
			}
			// set all the fields for the breed object to be put into the inventory
			switch(counter) {
				case 1:
					breed = token;
					break;

				case 2:
					name = token;
					break;

				case 3: 	
					colour = token;
					break;

				case 4:
					dadName = token;
					break;

				case 5:
					momName = token;
					break;

				default:
					// error handling for the CSV file formatting
					throw invalid_argument("\nCSV file is not formatted correctly\n");
					break;
			}
 		}

		// create a breed object based on the tokens in the line
		Breed dog(name, colour, breed);

		// check if the dog object has a dad/mom
		bool hasDad = false, hasMom = false;

		// set the dad/mom pointers to the correct object
		for(unsigned int i = 0; i < inventory.size(); i++) {
			// ensure the inventory is not null
			if(!inventory.empty()) {

				// find the parent object in the inventory
				if(inventory[i].getName() == dadName) {
					Breed *ptr1 = &inventory[i];
					// set the pointer to the parent object found
					dog.setDad(ptr1);
					// set the boolean variable as the parent was found
					hasDad = true;
				}

				if(inventory[i].getName() == momName) {
					Breed *ptr2 = &inventory[i];
					dog.setMom(ptr2);
					hasMom = true;
				}
			}	
		}

		// methods to add a "N/A" parent object if the parent is not in the inventory
		if(!hasDad) {
			Breed dog2("N/A", "black", "Husky");

			Breed *ptr3 = &dog2;
			dog.setDad(ptr3);
		}

		if(!hasMom) {
			Breed dog3("N/A", "black", "Husky");

			Breed *ptr4 = &dog3;
			dog.setMom(ptr4);
		}

		// add the dog to the inventory vector
		inventory.push_back(dog);

	}

	// call the paternal tree method since the file has been successfully parsed
	paternalTree();
}
