#ifndef  DOG_H
#define  DOG_H
#include <stdio.h>
#include <string>

using namespace std;

class Dog {

	private:
		string name;
		string color;
		Dog* dad;
		Dog* mom;

	public:
		Dog(string name, string color);
		~Dog();

		// getters for the name and color
		// made virtual so they can be accessed in the breed class
		virtual string getName() {
			return name;
		}

		virtual string getColor() {
			return color;
		}

		// pointer getters for the dad and mom pointer
		Dog * getDad() {
			return dad;
		}

		Dog * getMom() {
			return mom;
		}

		// use to set the dad/mom pointer at object creation
		// after parsing in the CSV file
		void setDad(Dog* d) {
			dad = d;
		}

		void setMom(Dog* m) {
			mom = m;
		}

};

#endif