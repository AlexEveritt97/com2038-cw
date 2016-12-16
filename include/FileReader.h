#include "Breed.h"
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class FileReader {

	public:
		template<typename T> void printElement(T t, const int& width);
		void printHeaders(int total);
		void paternalTree();
		string traverseTree(Dog* dog, string output);
		int totalDogs(string filename);
		void fileReader(string filename);

	private:
		vector<Breed> inventory;
		bool first;
};