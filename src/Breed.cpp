#include "Breed.h"
#include <string>
#include <stdexcept>

using namespace std;

// constructor for the breed inheriting from the dog class
Breed::Breed(string name, string color, string bn) : Dog(name, color){
	name = name;
	color = color;

	// error handling the breed name so it can only one of the three breeeds - Husky, Corgi or Boxer
	if(bn.compare("Husky") == 0 || bn.compare("Corgi") == 0 || bn.compare("Boxer") == 0) {
		breedName = bn;
	}
	else{
		throw invalid_argument(bn+ " is not a valid breed name - must be Husky, Corgi or Boxer");
	}
}

// destructor for the breed
Breed::~Breed(){

}

