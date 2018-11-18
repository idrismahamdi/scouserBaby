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
	
	int size = vec.size();

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


//Increments the control instruction by 1 
// Tested and working for vectors
void Baby::incrementCI()
{
	int controlDecimal = binaryToDecimal(controlInstruction);

	if(testFlop == true)
	{
		controlDecimal = controlDecimal + 2;
	}

	else
	{
		controlDecimal = controlDecimal + 1;
	}

	controlInstruction = decimalToBinary(controlDecimal);
}

//Gets the memory address of the line to be accessed in the instructions, as well as the present opcode
//and sets them to their global variables to be used later on in the program.
//Tested and working with vectors
void Baby::fetch()
{
	int controlDecimal = binaryToDecimal(controlInstruction);

	for(int i = 0; i < 5 ; i++){
		tempOperand[i] = memory[controlDecimal][i];
	}
	
	for(int j = 13; j < 16; j++){
		present[j - 13] = memory[controlDecimal][j];
	}
}

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
	line tempLine = getCurrentMemoryLine();
	int decimalStore = getLineDecimal(tempLine);

	if(decimalStore < 0)
		decimalStore = -decimalStore;

	controlInstruction = decimalToBinary(decimalStore);
}

//Adds the content of the store to the control instruction
void Baby::JRP()
{
	line tempLine = getCurrentMemoryLine();
	int decimalStore = getLineDecimal(tempLine);
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
	int decimalAccumulator = getLineDecimal(accumulator);
	bool negative = false;

	if(decimalAccumulator < 0)
	{
		decimalAccumulator = -decimalAccumulator;
		negative = true;
	}

	line tempLine = decimalToBinary(decimalAccumulator);

	if(negative == true)
	{
		tempLine[31] = 1;
	}

	for(int i = 0; i < 32; i++)
	{
		memory[currentOperand][i] = tempLine[i];
	}
}

//Sets the accumulator to the negative of the contents of the store.
void Baby::LDN()
{
	line tempLine = getCurrentMemoryLine();

	int decimalStore = getLineDecimal(tempLine);

	accumulator = decimalToBinary(decimalStore);
	accumulator[31] = 1;
}

//sets the accumulator to the contents of the accumulator minus the contents of the store.
void Baby::SUB()
{
	int decimalAccumulator = getLineDecimal(accumulator);

	line tempLine = getCurrentMemoryLine();

	int decimalStore = getLineDecimal(tempLine);

	int result = decimalAccumulator - decimalStore;
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
	if(decimalAccumulator < 0)
	{
		testFlop = true;
	}
}

//Used to break the loop
void Baby::STP()
{
	Exit = true;
}

//Returns the line from the current address in memory.
line Baby::getCurrentMemoryLine()
{
	line tempLine(32, 0);

	for(int i = 0; i < 32; i++)
	{
		tempLine[i] = memory[currentOperand-1][i];
	}

	return tempLine;
}

//Returns the decimal of the line vector that is passed into them.
int Baby::getLineDecimal(line vec)
{
	int decimalVec;

	if(vec[31] == 1)
	{
		vec[31] = 0;
		decimalVec = binaryToDecimal(vec);
		decimalVec = -decimalVec;
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
		controlInstruction[i]=memory[0][i];
	}

	out.close();
}

//sets the present and operand to the correct number.
void Baby::decode()
{
	decimalPresent = binaryToDecimal(present);
	currentOperand = binaryToDecimal(tempOperand);
}

//Displays the state of the memory at the end of each loop
void Baby::displayEverything()
{
	int controlDecimal = getLineDecimal(controlInstruction);

	cout << "This was the memory state when the control instruction was " << controlDecimal << endl;
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


