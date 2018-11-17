#include<string>
#include<iostream>
#include<fstream>
#include <array>
#include <vector>
#include <istream>
#include <sstream>
#include <algorithm>
#include <iterator>

class LookUpNode {
public:
	  int opcode;
	  int refence;
	  bool numbers[32];
		string name;
};

LookUpNode::LookUpNode(){
	opcode = 0;
	reference = 0;
	numbers= {};
	name == "";
}

void LookUpNode::setNumbers(int n){
	// counter for binary array
	int i = 0;
	while (n > 0) {
			// storing remainder in binary array
			numbers[i] = n % 2;

			n = n / 2;
			i++;

}
