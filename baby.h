#include <iostream>
#include <fstream>
#include <math.h>
#include <vector> 

using namespace std;

//Typedef for a vector of integers to be named line.
typedef vector<int> line;
//Typedef for a vector of lines to be names store.
typedef vector<line> store;

class Baby{
	public: 
	void readFile();
	void incrementCI();
	line decimalToBinary(int numberToConvert);
	int binaryToDecimal(line vec);
	void fetch();
	void decode();
	void execute();
	void JMP();
	void JRP();
	void LDN();
	void SUB();
	void STO();
	void CMP();
	void STP();
	line getCurrentMemoryLine();
	int getLineDecimal(line vec);
	void displayEverything();
};