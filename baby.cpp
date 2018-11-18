#include "baby.h"
//The store of memory for the program 
store memory (32, line(32,0));
// stores the current/next address to be processed
line controlInstruction(32, 0);
//holds the opcode of the current instruction
line present(32, 0);
//holds results of instructions
line accumulator(32, 0);

//Holds the current operand bewteen fetch and decode
line tempOperand(5, 0);

// //holds the operand of the current line being processed -- this is the address of the number in the store
// //To be accessed and used in the instructions.
int currentOperand; 
//Holds the decimal opcode from the present
int decimalPresent;


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
	//Gets the size of the vector
	int size = vec.size();

	int j =0;

	//This for loop flips the vector around so that when the binary 
	//is converted it is interpreted as big-endian
	for (int i = 0; i < (size / 2); i++) {
        float temporary = vec[i];             
        vec[i] = vec[(size - 1) - i];
        vec[(size - 1) - i] = temporary;
    }

	int out = 0;
	int power = 1;
	//This converts the binary to decimal and stores it using the variable out
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

    //this converts the number from decimal to the binary array
	 while(numberToConvert!=0)
	{
	  r = numberToConvert%2;
	  binaryNum[i++] = r;
	  numberToConvert /= 2;
	}

	//this ensures that the vector that is returned is only of size 32
	for(int i = 0; i < 32; i++)
  	{
  	result[i]= binaryNum[i];
  	}

  return result;
}


//Increments the control instruction by 1 
// Tested and working for vectors
void Baby::incrementCI()
{
	//gets the decimal number from the control instruction
	int controlDecimal = getLineDecimal(controlInstruction);

	//checks to see if the testFlop boolean has been set to true, which is done in the CMP function
	//if the number in the accumulator is negative. If it is 2 is added to the control instruction.
	if(testFlop == true)
	{
		controlDecimal = controlDecimal + 2;
		testFlop = false;
	}

	//Otherwise only 1 is added to the control instruction
	else
	{
		controlDecimal = controlDecimal + 1;
	}

	//sets the control instruction vector to the new decimal value converted to binary.
	controlInstruction = decimalToBinary(controlDecimal);
}

//Gets the memory address of the line to be accessed in the instructions, as well as the present opcode
//and sets them to their global variables to be used later on in the program.
//Tested and working with vectors
void Baby::fetch()
{
	int controlDecimal = binaryToDecimal(controlInstruction);

	//Takes the first 5 elements from the memory at the current address in the control instruction and places
	//it into a temporary operand.
	for(int i = 0; i < 5 ; i++){
		tempOperand[i] = memory[controlDecimal][i];
	}
	
	//Sets the opcode from the memory at the current address in the control instruction and places it into present.
	for(int j = 13; j < 16; j++){
		present[j - 13] = memory[controlDecimal][j];
	}
}

//Checks the decimal version of present and uses this number to call the correct function corresponding 
//to the instruction set.
void Baby::execute()
{
	switch(decimalPresent) {
    case 0 : Baby::JMP();
        cout << "JMP" << endl;
    		break;
    case 1 : Baby::JRP();
        cout << "JRP" << endl;
    		break;
    case 2 : Baby::LDN();
        cout << "LDN" << endl;
    		break;
    case 3 : Baby::STO();
        cout << "STO" << endl;
    		break;
    case 4 : Baby::SUB();
        cout << "SUB" << endl;
    		break;
    case 5 : Baby::SUB();
        cout << "SUB" << endl;
    		break;
    case 6 : Baby::CMP();
        cout << "CMP" << endl;
    		break;
    case 7 : Baby::STP();
    	cout << "STP" << endl;
    		break;
    default: cout << "no opcode found" << endl;
    		break;
}
}

//Set the control instruction to the contents at the location of the store 
void Baby::JMP()
{
	//sets a temporary line variable to the the memory at the address of the control instruction in binary
	line tempLine = getCurrentMemoryLine();
	//sets a temporary variable to hold the decimal representation of tempLine.
	int decimalStore = getLineDecimal(tempLine);

	//If the decimal number at the store has somehow become negative, it will be set back to positive
	if(decimalStore < 0)
		decimalStore = -decimalStore;

	//The binary control instruction is set back using the decimal number being converted to binary.
	controlInstruction = decimalToBinary(decimalStore);
}

//Adds the content of the store to the control instruction
void Baby::JRP()
{
	//sets a temporary line variable to the the memory at the address of the control instruction in binary
	line tempLine = getCurrentMemoryLine();
	//sets a temporary variable to hold the decimal representation of tempLine.
	int decimalStore = getLineDecimal(tempLine);
	//Gets the decimal of the control line
	int decimalControl = getLineDecimal(controlInstruction);

	int result = decimalControl + decimalStore;

	if(result< 0)
	{
		result = -result;
	}

	controlInstruction = decimalToBinary(result);
}

//copies the accumulator to the store location
void Baby::STO()
{
	//Gets the decimal of the accumulator and holds it in a decimal temporary variable
	int decimalAccumulator = getLineDecimal(accumulator);
	//bool used to show whether or not the number is negative.
	bool negative = false;

	//checks to see if the number is negative
	if(decimalAccumulator < 0)
	{
		//If it is then make it positive so it can be properly added back to the store location.
		decimalAccumulator = -decimalAccumulator;
		//Sets the negative boolean to true so it can be used further down.
		negative = true;
	}

	line tempLine = decimalToBinary(decimalAccumulator);

	//If the number is negative the 32nd bit in the line is set to 1. this is used to act kind of like
	//a signed bit, to show that a number is negative. 
	if(negative == true)
	{
		tempLine[31] = 1;
	}

	//sets the specified line in the store to the temporary line variable 
	for(int i = 0; i < 32; i++)
	{
		memory[currentOperand][i] = tempLine[i];
	}
}

//Sets the accumulator to the negative of the contents of the store.
void Baby::LDN()
{
	//Gets the contents of the store first as binary then converts to decimal.
	line tempLine = getCurrentMemoryLine();
	int decimalStore = getLineDecimal(tempLine);

	//sets the accumulator to the number from the store
	accumulator = decimalToBinary(decimalStore);
	//sets the last bit to 1 to show the number is negative.
	accumulator[31] = 1;
}

//sets the accumulator to the contents of the accumulator minus the contents of the store.
void Baby::SUB()
{
	//gets the number from the vector accumulator and holds it as a decimal
	int decimalAccumulator = getLineDecimal(accumulator);

	//gets the line from the store in binary and converts to the decimal.
	line tempLine = getCurrentMemoryLine();
	int decimalStore = getLineDecimal(tempLine);

	int result = decimalAccumulator - decimalStore;
	//Checking to see if the result is negative so it can be correctly added back to the accumulator
	if(result < 0)
	{
		result = -result;
		accumulator = decimalToBinary(result);
		accumulator[31] = 1;
	}

	else
	{
		accumulator = decimalToBinary(result);
	}
}

//increments the control instruction by 2 if the number in the accumulator is negative.
void Baby::CMP()
{
	int decimalAccumulator = getLineDecimal(accumulator);
	//Checks to see if the accumulator is negative and if it is the test flop boolean is set to true,
	//So that the increment CI function increments by two if it is.
	if(decimalAccumulator < 0)
	{
		testFlop = true;
	}
}

//Used to break the loop when the stop command is reached
void Baby::STP()
{
	Exit = true;
}

//Returns the line from the current address in memory.
line Baby::getCurrentMemoryLine()
{
	//Creates a vector to return.
	line tempLine(32, 0);

	//sets the tempLine vector to be the same as the vector of the current address in memory. 
	for(int i = 0; i < 32; i++)
	{
		tempLine[i] = memory[currentOperand][i];
	}

	return tempLine;
}

//Returns the decimal of the line vector that is passed into them.
int Baby::getLineDecimal(line vec)
{
	//Creates variable to hold the result to return
	int decimalVec;

	//checks to see if the number is negative
	if(vec[31] == 1)
	{
		//sets the last bit back to 0 so the number can be converted to decimal properly
		vec[31] = 0;
		decimalVec = binaryToDecimal(vec);
		//sets the currently positive decimal number to negative.
		decimalVec = -decimalVec;
		//sets the last bit in the vector back to one so that it is still represented as negative.
		vec[31] = 1;
	}

	else
	{
		decimalVec = binaryToDecimal(vec);
	}

	return decimalVec;
	
	}


//Reads the file in initialise each vector line.
//working with vectors
void Baby::readFile(){
	char letter;
	string line;
	//opens the file to be read from
	ifstream out("BabyTest1-MC.txt");
	int lineCount = 0;

	//while the next line is not null
	while(getline(out, line))
	{
		//for each line of the vector
		for(int i = 0; i < 32; i++) {
		//variable takes the int from the char and subtracts 48, so that value is just the number.
		int value;
		value = line.at(i) - 48;
		//sets the memory location in the store to the 
		memory[lineCount][i] = value;
  		}

  	lineCount++;
	}

	//closes the file again.
	out.close();
}

//sets the present and operand to the correct number.
void Baby::decode()
{
	//gets the binary from the tempOperand and present and sets them to their correct decimal value.
	decimalPresent = binaryToDecimal(present);
	currentOperand = binaryToDecimal(tempOperand);
}

//Displays the state of the memory at the end of each loop
void Baby::displayEverything()
{ 
    	int controlDecimal = getLineDecimal(controlInstruction);
	int decimalAccumulator = getLineDecimal(accumulator);
	int decimalPresent = getLineDecimal(present);

	cout << "The accumulator was " << decimalAccumulator <<  " when the control instruction was " << controlDecimal << endl;
	cout << "The present was " << decimalPresent <<  " when the control instruction was " << controlDecimal << endl;

	cout << "This was the memory state when the control instruction was " << controlDecimal << endl;
	//Prints out the whole memory
	for (int i =0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			cout << memory[i][j];
		}
		cout << endl;
	}
}

int main()
{
	Baby baby;

	baby.readFile();

	//This loop runs the whole simulation, and will only break when the STP function is reached in
	//The source file.
	while(Exit == false)
	{
		baby.incrementCI();
		baby.fetch();
		baby.decode();
		baby.execute();
		baby.displayEverything();
	}

	return 0;
}


