#include "baby.h"
#include<string>
#include<iostream> 
#include<fstream>

//holds the line adress in the store of where the next line will be fetched
bool control[32];
//holds the instructions opcode
bool present[32];
//accumulator
bool accumulator[32];
 

/*
void Baby::initOpcodes(){

	//swap round code values
	opcode[0].input = {0,0,0};
	opcode[1].input = {0,0,1};
	opcode[2].input = {0,1,0};
	opcode[3].input = {0,1,1};
	opcode[4].input = {1,0,0};
	opcode[5].input = {1,0,1};
	opcode[6].input = {1,1,0};
	opcode[7].input = {1,1,1};
}

void Baby::fetch(){

}
*/
void Baby::initMemory(){
	for(int i = 0; i<32; i++)
	{
		for(int j = 0; j<32; j++)
		{
			memory[i][j] = 0;
		}
	}
}

void Baby::readFile(){


	char letter;
	string line;
	ifstream out("BabyTest1-MC.txt");
	int lineCount = 0;
	
	while(getline(out, line))
	{
		for(int i = 0; i < 32; i++) {
		memory[lineCount][i] = line.at(i);
    	cout << line.at(i);
  		}

  	lineCount++;
  	cout << "End of line"<< endl;
	}


	out.close();*/
}
void Baby::printMemory(){
	for(int i = 0; i<32; i++)
	{
		for(int j = 0; j<32; j++)
		{
			cout << memory[i][j];
		}
		cout << "" << endl;
	}
}

int main(){
	Baby baby;
	baby.initMemory();
	baby.readFile();
	baby.printMemory();
}