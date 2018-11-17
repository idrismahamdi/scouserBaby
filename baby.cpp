#include "baby.h"
#include "opcodes.h"
#include<string>
#include<iostream>
#include<fstream>
#include <array>
#include <vector>
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

bool testFlop = false;
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



void Baby::setPresent()
{
	for(int i = 0; i < 32; i++)
	{
		present[i] = control[i];
	}
}
void Baby::increment_CI()
{
  int temp = getOperand(control);

  if(testFlop == true)
  {
    temp += 2;
  }
  else
  {
    temp++;
  }
  decimalToBinary(temp, 5, control);
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
}

void Baby::decimalToBinary(int numberToConvert, int size, int arr[])
{

    int binaryNum[1000];
    int i = 0;
    while (numberToConvert > 0) {

        binaryNum[i] = numberToConvert % 2;
        numberToConvert = numberToConvert / 2;
        i++;
    }

  for(int i = 0; i < size; i++)
  {
  	arr[i]= binaryNum[i];
  }
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

int Baby::getOperand(int arr[])
{
	int tempOperand[5];

	for(int i = 0; i < 5 ; i++){
		tempOperand[i] = present[4 - i];
	}

	int result = binaryToDecimal(tempOperand, 5);

	if(accumulator[31] == 1)
	{
		result = -result;
	}

	return result;
}

void Baby::jmp(){

	for(int i = 0; i < 32; i++)
	{
		control[i] = (memory[decimalOperand][i]);
	}

 }

 void Baby::jrp(){
 	int tempControl = getOperand(control);

 	int tempStore[32];

 	for(int i = 0; i < 32; i++)
 	{
 		tempStore[i] = memory[decimalOperand][i];
 	}

 	int storeOperand = getOperand(tempStore);

 	tempControl = tempControl + storeOperand;

 	decimalToBinary(tempControl, 32, control);

 }

 void Baby::ldn(){

  	int tempStore[32];

 	for(int i = 0; i < 32; i++)
 	{
 		tempStore[i] = memory[decimalOperand][i];
 	}

 	int storeOperand = getOperand(tempStore);

 	int acc = storeOperand;
 	decimalToBinary(acc, 32, accumulator);
 	accumulator[31] = 1;

 }

 void Baby::sto(){
 	for(int i = 0; i < 32; i++)
 	{
 		memory[decimalOperand][i] = accumulator[i];
 	}

 }

 void Baby::sub(){
 	int tempStore[32];

 	for(int i = 0; i < 32; i++)
 	{
 		tempStore[i] = memory[decimalOperand][i];
 	}

 	int acc = getOperand(accumulator);
 	int store = getOperand(tempStore);

 	int newAcc = acc - store;

 	decimalToBinary(newAcc, 32, accumulator);

 }

 void Baby::cmp(){
   if(accumulator[31] == 1)
   {
     testFlop = true;
   }
 }

 void Baby::stp(){
 	Exit = true;
 }

void Baby::execute()
{
	switch(decimalOpcode) {
    case 0 : Baby::jmp();
        cout << "jmp" << endl;
    		break;
    case 1 : Baby::jrp();
        cout << "jrp" << endl;
    		break;
    case 2 : Baby::ldn();
        cout << "ldn" << endl;
    		break;
    case 3 : Baby::sto();
        cout << "sto" << endl;
    		break;
    case 4 : Baby::sub();
        cout << "sub" << endl;
    		break;
    case 5 : Baby::sub();
        cout << "sub" << endl;
    		break;
    case 6 : Baby::cmp();
        cout << "cmp" << endl;
    		break;
    case 7 : Baby::stp();
    		break;
    default: cout << "no opcode found" << endl;
    		break;

     // We need to remember in the execute function to set the control
     // instruction array to the memory array at the position of the operand

      for(int i = 0; i < 5; i++ )
    {
    	control[i] = memory[decimalOperand][i];
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

void Baby::display()
{
  cout << "Control instruction: ";
  for(int i = 0; i < 32; i++)
  {
    cout << control[i];
  }

  cout << " present: ";
  for(int i = 0; i < 32; i++)
  {
    cout << present[i];
  }

  cout << " operand: ";
  for(int i = 0; i < 5; i++) 
  {
    cout << operand[i];
  }

  cout << " opcode: ";
  for(int i = 0; i < 3; i++)
	{
		cout << opcode[i];
	}
  cout << ""<< endl;

  cout << "decimalOperand: "<< decimalOperand << endl;
  cout << "decimalOpcode: "<< decimalOpcode << endl;
}

int main(){
	Baby baby;
	 baby.initMemory();
	 baby.readFile();
	// baby.printMemory();

	// while (Exit == false){

  for(int i = 0; i < 4; i++)
  {
	   baby.setPresent();
     baby.increment_CI();
	   baby.fetch();
	   baby.decode();
	   baby.execute();
     baby.display();
	}
}
