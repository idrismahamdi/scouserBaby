#include "baby.cpp"
#include "Assembler.cpp"
#include "baby.h"
#include "Assembler.h"
#include "LookUpNode.cpp"
using namespace std;

void Menu()
{
	cout<<"Please select an action from the following options:"<<endl;
	cout<<"Option 1: Insert the name of a file to run the Manchester baby."<<endl;
	cout<<"Option 2: Insert the name of a file to run the Assembler."<<endl;
	int choice;
	switch(choice):
	case "1":
		choice1();
	break;
	case "2":
		choice2();
	break;
}

void choice1()
{
	string file = inputVal();
	runBaby(file);
}

// void choice2()
// {
// 	string file = inputVal();
// 	runBaby(file); method 
// }

string inputVal()
{
	bool accepted = false;
	while(accepted==false)
	{
		string input;
		cout <<"Please include the file name with the .txt extension."<< endl;
		cin>>input;
		if(fexists(input)==false)
		{
			cout <<"The input was valid, please try again."<< endl;
		}
		else
		{
			accepted=true;
			return input;
		}
	}
}

bool fexists(string filename)
{
  ifstream ifile(filename);
  return ifile;
}

int main()
{
	Menu();
}