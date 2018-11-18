#include "baby.h"
//The store of memory for the program



store memory (32, line(32,0));
// stores the current/next address to be processed
line controlInstruction(32, 0);
//holds the opcode of the current instruction
line present(32, 0);
//holds results of instructions
line accumulator(32, 0);

// //holds the operand of the current line being processed -- this is the address of the number in the store
// //To be accessed and used in the instructions.
// int currentOperand[5] = {0}; // change to vector

/*
Shows if the result in the accumulator is negative or positive -- false means positive.
We are going to use the last bit in the accumulator to represent this
-- eg if accumulator[31] == 1 then it is negative
*/
bool testFlop = false;

//used to break the loop of the program
bool Exit = false;

//Function to convert an array of binary into a decimal number, passes in a line and returns a number.
//Tested and working
int Baby::binaryToDecimal(line vec)
{
	
	int size = vec.size();

	cout << "size: " << size << endl;

	int j =0;

	for (int i = 0; i < (size / 2); i++) {
        float temporary = vec[i];             
        vec[i] = vec[(size - 1) - i];
        vec[(size - 1) - i] = temporary;
    }

	int out = 0;
	int power = 1;
	for(int i=0; i<size; i++)
	{
		out += vec[(size - 1) - i]*power;
		power *= 2;
	}

	
	return out;
}

/*
This is a --working-- decimal to binary coverter. It takes the number you want to convert, 
and returns a vector of the binary number you are trying to find.
*/
line Baby::decimalToBinary(int numberToConvert)
{
    line binaryNum(100, 0);
    line result(32, 0);
    int i=0,r;

   
	 
	 while(numberToConvert!=0)
	{
	  r = numberToConvert%2;
	  binaryNum[i++] = r;
	  numberToConvert /= 2;
	}

  for(int i = 0; i < 32; i++)
  {
  	if(binaryNum[i] != 1)
  	{
  		binaryNum[i] = 0;
  	}

  	result[i]= binaryNum[i];
  }

  return result;
}

//Initialises the whole memory of the computer to 0
void Baby::initMemory(){
	for(int i = 0; i<32; i++)
	{
		for(int j = 0; j<32; j++)
		{
			memory[i][j] = 0;
		}
	}
}

// //Increments the control instruction by 1 
// void Baby::incrementCI()
// {
// 	int controlDecimal = binaryToDecimal(controlInstruction, 32);

// 	if(testFlop == true)
// 	{
// 		controlDecimal = controlDecimal + 2;
// 	}

// 	else
// 	{
// 		controlDecimal = controlDecimal + 1;
// 	}

// 	decimalToBinary(controlDecimal, 32, controlInstruction);
// }

// //Gets the memory address of the line to be accessed in the instructions, as well as the present opcode
// //and sets them to their global variables to be used later on in the program.
// void Baby::fetch()
// {
// 	int controlDecimal = binaryToDecimal(controlInstruction, 32);

// 	cout << controlDecimal << endl;

// 	for(int i = 0; i < 5 ; i++){
// 		currentOperand[i] = memory[controlDecimal][i];
// 	}
	
// 	for(int j = 0; j < 32; j++){
// 		present[j] = memory[controlDecimal][j];
// 	}
// }

// //Reads the file in initialise each array as a line.
// void Baby::readFile(){


// 	char letter;
// 	string line;
// 	ifstream out("BabyTest1-MC.txt");
// 	int lineCount = 0;

// 	while(getline(out, line))
// 	{
// 		for(int i = 0; i < 32; i++) {
// 		int value;
// 		value = line.at(i) - 48;
// 		memory[lineCount][i] = value;
//   		}

//   	lineCount++;
// 	}

// 	for(int i=0; i<32; i++)
// 	{
// 		controlInstruction[i]=memory[0][i];
// 	}

// 	out.close();
// }

int main()
{
	Baby baby;

	baby.initMemory();
	// baby.readFile();
	// baby.incrementCI();
	// baby.fetch();




	

	return 0;
}


