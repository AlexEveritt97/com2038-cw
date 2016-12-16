#include <stdio.h>
#include <iostream>
#include "Breed.h"
#include "FileReader.h"

using namespace std;

int main() {

	// create a new file reader object
	FileReader* read = new FileReader();

	// error handling opening the file
	try{
		// try to read the csv file
		read -> fileReader("bin/inventory.csv");
	}
	catch(const invalid_argument& e){
		// catch the exception if the file name is not valid
		cout << e.what() << endl;
	}
}