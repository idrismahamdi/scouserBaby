#include "baby.h"
#include "opcodes.h"
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

int memory[32][32];

bool Exit = false;
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
	
	for(int i = 0; i < 5 ; i++){
		operand[i] = present[4 - i];
	}
	for(int j = 0; j < 3; j++){
		opcode[j]=present[15-j];
	}
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
	decimalOperand = binaryToDecimal(operand, 5);
	decimalOpcode = binaryToDecimal(opcode, 3);


	cout<< decimalOperand << endl;
	cout<< decimalOpcode << endl;
}

int Baby::binaryToDecimal(int arr[], int size)
{

	int out = 0;
	int power = 1;
	for(int i=0; i<size; i++)
	{
		out += arr[(size-1)-i]*power;
		power *= 2;
	}
	return out;
}

void Baby::decimalToBinary(int n){
	vector<bool> a;
	for(i=0; n>0; i++){    
		a[i].pushbackn%2;    
		n= n/2;  
	}     	
}
void Baby::jmp(){
	
		control[i] = (memory[decimalOperand]);

 }

 void Baby::jrp(){
 	
 }

 void Baby::ldn(){
 	
 }

 void Baby::sto(){
 	memory[decimalOpcode] = accumulator;
 }

 void Baby::sub(){
 	
 }

 void Baby::cmp(){
 	if(binaryToDecimal(accumulator)<0){increment_CI();}
 }

 void Baby::stp(){
 	exit = true;
 }

void Baby::execute()
{
	switch(decimalOpcode) {
    case 0 : Baby::jmp();
    case 1 : Baby::jrp();
    case 2 : Baby::ldn();
    case 3 : Baby::sto();
    case 4 : Baby::sub();
    case 5 : Baby::sub();
    case 6 : Baby::cmp();
    case 7 : Baby::stp();
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

	 while (Exit = false){
	baby.fetch();
	baby.decode();
	}	
}