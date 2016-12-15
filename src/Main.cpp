#include <stdio.h>
#include <iostream>
#include "Breed.h"
#include "FileReader.h"

using namespace std;

int main() {

	// Breed test("scooby doo", "brown", "husky");

	// Breed *ptr1 = &test;

	// Breed test1("scrappy doo", "green", "husky");
	// test1.setDad(ptr1);

	// cout << "Dad: " + test1.getDad() -> getName() << endl;
	// cout << "Son: " + test1.getName() << endl;

	FileReader* read = new FileReader();
	try{
		read -> fileReader("bin/inventory.csv");
	}
	catch(const invalid_argument& e){
		cout << e.what() << endl;
	}
}