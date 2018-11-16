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
//global variable storing the array of operands
int operand[5]={0};
//global varable storing the decimal version of the operand
int decimalOperand = 1;
//global variable storing the decimal version of the opcode
int decimalOpcode = 0;
//global variable storing the array of opcode
int opcode[3]={0};
//memory array
int memory[32][32];
//boolean used to break loops
bool Exit = false;


/*
	This method increments the present line to be what the control line was 
*/
void Baby::increment_CI()
{
	for(int i = 0; i < 32; i++)
	{
		present[i] = control[i];
	}
}

/*
	This method saves the present's line operand and opcode
*/
void Baby::fetch(){
	
	for(int i = 0; i < 5 ; i++){
		operand[i] = present[4 - i];
	}
	for(int j = 0; j < 3; j++){
		opcode[j]=present[15-j];
	}
}

/*
	This method initialises the memory array
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

/*
	This method calls the binaryToDecimal method to convert the operand and the opcode to decimal
*/
void Baby::decode()
{
	decimalOperand = binaryToDecimal(operand, 5);
	decimalOpcode = binaryToDecimal(opcode, 3);
}

/*
	This method takes three parameters: a decimal integer to be converted to binary, the size of the result array and an integer array where the binary number will be stored
	The funcion of this method is converting from decimal to binary
*/
void Baby::decimalToBinary(int n, int size, int arr[]) 
{ 
	int binaryNum[1000]; 
	int i = 0; 
	while (n > 0) { 
	    
	    binaryNum[i] = n % 2; 
	    n = n / 2; 
	    i++; 
	} 

	for(int i = 0; i < size; i++){

		arr[i]= binaryNum[i];
	}
} 

/*
	This method takes two parameters: an integer array where the binary number is stored and a size integer, containing the size of the array
	The function of this method is converting from binary to decimal
*/
int Baby::binaryToDecimal(int arr[], int size)
{
	int out = 0;

	int power = 1;

	for(int i=0; i<size; i++){

		out += arr[(size-1)-i]*power;
		power *= 2;
	}
	return out;
}

/*
	This method takes an array of integers as a parameter
	The function of this method is to return the decimal version of the operand
*/
int Baby::getOperand(int arr[])
{
	int tempOperand[5];
	
	for(int i = 0; i < 5 ; i++){

		tempOperand[i] = present[4 - i];
	}

	int result = binaryToDecimal(tempOperand, 5);

	return result;
}

/*
	This method sets Control Instruction's contents to the contents of the Store location
*/
void Baby::jmp(){

	for(int i = 0; i < 32; i++)
	{
		control[i] = (memory[decimalOperand][i]);
	}

}

/*
	This method adds the content of Store location to Control Instruction
*/
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

/*
	This method loads Accumulator with negative form of Store Content
*/
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

/*
	This method copies Accumulator to the Store location
*/
void Baby::sto(){
	for(int i = 0; i < 32; i++)
	{
		memory[decimalOperand][i] = accumulator[i];
	}
	
}

/*
	This method subtracts the content of Store location from Accumulator
*/
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

/*
	This method increments Control Instruction if the Accumulator value is negative, otherwise it does not do anything
*/
void Baby::cmp(){
	if(getOperand(accumulator)<0){increment_CI();}
}

/*
	This method sets Stop lamp and halts the machine
*/
void Baby::stp(){
	Exit = true;
}

/*
	This method executes different method depending on the value of decimalOpcode
*/
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

/*
	This method reads the contents from a file to the memory array
*/
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

/*
	This method prints the content of the memory to the user
*/
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

/*
	This is the main method of the class
*/
int main(){
	Baby baby;
	 baby.initMemory();
	 baby.readFile();
	// baby.printMemory();

	 while (Exit == false){
	baby.fetch();
	baby.decode();
	}	
}