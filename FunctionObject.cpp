/**
 * This is a function object example. Neat stuff.
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <time.h>

struct S {
	int a;
	int b;
};

struct Compare {
	bool operator () (const S & s1, const S & s2) {
		return s1.a < s2.a;
	}
};

std::string S_to_string(const S & s) {
	std::string toReturn;
	toReturn += "(";
	toReturn += std::to_string(s.a);
	toReturn += ", ";
	toReturn += std::to_string(s.b);
	toReturn += ")";

	return toReturn;
}

#define ELEMENTS 200000
int main (int argc, char ** argv) {
	srand(time(NULL));
	S array[ELEMENTS];

	// std::cout<<"Generated list:\n{";

	for (int x = 0; x < ELEMENTS; ++x) {
		array[x].a = rand() % 1000;
		// srand(time(NULL));
		array[x].b = rand() % 1000;
		// srand(time(NULL));
		// std::cout<<S_to_string(array[x]);
		// if (x + 1 < ELEMENTS) std::cout<<", ";
	}

	// std::cout<<"}"<<std::endl;

	std::sort(array, array + ELEMENTS, Compare());

	// std::cout<<"\nSorted list:\n{";
	// for (int x = 0; x < ELEMENTS; ++x) {
	// 	// Since dist is [a, b), but we want 1000 included.
	// 	std::cout<<S_to_string(array[x]);
	// 	if (x + 1 < ELEMENTS) std::cout<<", ";
	// }
	// std::cout<<"}"<<std::endl;

	return 0;
}