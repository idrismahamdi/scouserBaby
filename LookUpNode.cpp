#include<string>
#include<iostream>
#include<fstream>
#include <array>
#include <vector>
#include <istream>
#include <sstream>
#include <algorithm>
#include <iterator>

class LookUpNode {

private:
	int opcode;
	int lineNumber;
	bool numbers[32];
	string name;
	bool start;
	bool end;
	string variableNumber;
	string varNam;


public:

		void setNumbers(int);
		LookUpNode();
		LookUpNode(int,int,string);

		int getOpcode();
		void setOpcode(int);
		string getName();

		void setName(string);
		bool getStart();

		void setStart(bool);
		bool getEnd();

		string getVariableNumber();
		void setVariableNumber(string);

		string getVarNam();
		void setVarNam(string);

		void setEnd(bool);
		int getlineNumber();

		void setlineNumber(int);
		void printNumbers();

};

LookUpNode::LookUpNode(){
	opcode = 0;
	lineNumber = 0;
	for (int i = 0; i < 32; i++){
		numbers[i]=0;
	}
	name == "";
}
LookUpNode::LookUpNode(int opcode,int lineNum,string name){
	opcode = opcode;
	lineNumber = lineNum;
	name == name;
}
int LookUpNode::getOpcode(){
	return opcode;
}

void LookUpNode::setOpcode(int n){
	this->opcode = n;
}

int LookUpNode::getlineNumber(){
	return lineNumber;
}
void LookUpNode::setlineNumber(int n){
	this->lineNumber = n;
}

string LookUpNode::getName(){
	return name;
}
void LookUpNode::setName(string name){
	this->name = name;
}

bool LookUpNode::getStart(){
	return start;
}
void LookUpNode::setStart(bool start){
	this->start = start;
}

bool LookUpNode::getEnd(){
	return end;
}
void LookUpNode::setEnd(bool end){
	this->end = end;
}

string LookUpNode::getVariableNumber(){
	return variableNumber;
}
void LookUpNode::setVariableNumber(string varNumber){
	this->variableNumber = varNumber;
}

string LookUpNode::getVarNam(){
	return varNam;
}
void LookUpNode::setVarNam(string varNam){
	this->varNam = varNam;
}

void LookUpNode::setNumbers(int n){
	// counter for binary array

	int i = 0;

	while (n > 0) {
			// storing remainder in binary array
			numbers[i] = n % 2;
			n = n / 2;
			i++;

		}

}

void LookUpNode::printNumbers(){
	for(int i = 0; i < 32; i++){
		cout<<numbers[i]<<endl;
	}
}
