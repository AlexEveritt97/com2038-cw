#ifndef  BREED_H
#define  BREED_H
#include <stdio.h>
#include <string>
#include "Dog.h"

using namespace std;

// class breed inherits dog so the breed name is added to the object
class Breed: public Dog {

	private:
		string breedName;

	public:
		Breed(string name, string color, string bn);
		
		~Breed();

		string getBreedName() {
			return breedName;
		}
};

#endif