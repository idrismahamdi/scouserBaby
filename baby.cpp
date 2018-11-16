#include "baby.h"
#include<string>
#include<iostream> 
#include<fstream>
#include <array>

using namespace std;

//holds the line adress in the store of where the next line will be fetched
int control[32]={0};
//holds the instructions opcode
int present[32]={0};
//accumulator
int accumulator[32]={0};
 
int operand[5]={0};

int decimalOperand = 1;

int decimalOpcode = 0;

int opcode[3]={0};
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
*/

void Baby::increment_CI()
{
	

	for(int i = 0; i < 32; i++)
	{
		present[i] = control[i];
	}
}


void Baby::fetch(){
	
	operand[0]=present[4];
	operand[1]=present[3];
	operand[2]=present[2];
	operand[3]=present[1];
	operand[4]=present[0];

	opcode[0]=present[15];
	opcode[1]=present[14];
	opcode[2]=present[13];
}

void Baby::initMemory(){
	for(int i = 0; i<32; i++)
	{
		for(int j = 0; j<32; j++)
		{
			memory[i][j] = 0;
		}
	}

	
}

void Baby::decode()
{
	int out=0, power=1;
	int a = 5; //find size of operand array
	int b = 3;	//find size of opcode array
	for(int i=0; i<a; i++)
	{
		out += operand[4-i]*power;
		power *= 2;
	}
	decimalOperand = out;
	out = 0;
	power = 1;
	for(int i=0; i<b; i++)
	{
		out += opcode[2-i]*power;
		power *= 2;
	}

	decimalOpcode = out;

	cout<< decimalOperand << endl;
	cout<< decimalOpcode << endl;
}

void Baby::readFile(){


	char letter;
	string line;
	ifstream out("BabyTest1-MC.txt");
	int lineCount = 0;
	
	while(getline(out, line))
	{
		for(int i = 0; i < 32; i++) {
		int value;
		value = line.at(i) - 48;
		memory[lineCount][i] = value;
  		}

  	lineCount++;
	}

	for(int i=0; i<32; i++)
	{
		control[i]=memory[1][i];
	}

	out.close();
}

void Baby::execute(){

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
	// baby.printMemory();
	baby.increment_CI();
	baby.fetch();
	baby.decode();
}