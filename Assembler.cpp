#include "baby.h"
#include "LookUpNode.cpp"
#include<string>
#include<iostream>
#include<fstream>
#include <array>
#include <vector>
#include <istream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
typedef vector<string> seperatedLine;

class Assembler {

public:
	void readSource();
  bool testOperand(string);
	void init();
	void createMachineCode();
	int findVarName(string varName);
	vector<bool> decimalToBinary(int);
	void displayMachineCode();
	void insertLine(int, vector<bool> ,vector<bool>);

  vector<LookUpNode> lookUpTable;
	vector<vector<bool>> machineCode;
};

void Assembler::init(){
 lookUpTable.resize(32);

	machineCode.resize(32);
	for (vector<bool> nodeList : machineCode){
			nodeList.resize(32);
		}
}


void Assembler::readSource()
{
string line;
ifstream out("BabyTest1-Assembler.txt");
std::string delimiter = ";";
string codeLine;
int lineNum = 0;




  while(getline(out, line))
  {
    std::string delimiter = ";";
    size_t pos = 0;
    string token;
		bool getVariable = false;
		  while ((pos = line.find(delimiter)) != string::npos) {
          token = line.substr(0, pos);

          codeLine = token;
          line.erase(pos, pos+ line.length());
        }





if(codeLine!=""){
				istringstream iss(codeLine);
		    for(string codeLine; iss >> codeLine; ){


				if(testOperand(codeLine) != true && getVariable != true){
					lookUpTable.at(lineNum).setVarNam(codeLine.substr(0, codeLine.size()-1));
				}
				if(getVariable == true){

						lookUpTable.at(lineNum).setVariableNumber(codeLine);
						getVariable = false;
				}
					if(testOperand(codeLine)==true){
						lookUpTable.at(lineNum).setName(codeLine);
						lookUpTable.at(lineNum).setlineNumber(lineNum);
						getVariable = true;
					}
					else if (codeLine == "START:"){
						lookUpTable.at(lineNum).setStart(true);
						}
					else if (codeLine == "END:"){
						lookUpTable.at(lineNum).setEnd(true);
					}
				}


				lineNum++;
}




}

  out.close();
}

bool Assembler::testOperand(string substring){

  if(!substring.compare("JMP")){
		return true;
	}
  else if(!substring.compare("JRP")){
		return true;
  }
  else if(!substring.compare("LDN")){

		return true;
	}
  else if(!substring.compare("STO")){
		return true;
	}
  else if(!substring.compare("SUB")){
		return true;
	}
  else if(!substring.compare("CMP")){
		return true;
	}
  else if(!substring.compare("STP")){
		return true;
	}
	else if(!substring.compare("VAR")){
		return true;
	}else{
		return false;
	}
}

void Assembler::createMachineCode(){

	for (LookUpNode &node : lookUpTable) {
		if(!node.getName().compare("JMP")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {0,0,0};
			insertLine(node.getlineNumber(),binary,opcode);
		}
	  else if(!node.getName().compare("JRP")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {1,0,0};
			insertLine(node.getlineNumber(),binary,opcode);
	  }
	  else if(!node.getName().compare("LDN")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {0,1,0};
			insertLine(node.getlineNumber(),binary,opcode);

		}
	  else if(!node.getName().compare("STO")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {1,1,0};
			insertLine(node.getlineNumber(),binary,opcode);
		}
	  else if(!node.getName().compare("SUB")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {0,0,1};
			insertLine(node.getlineNumber(),binary,opcode);
		}
	  else if(!node.getName().compare("CMP")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			vector<bool> opcode = {0,1,1};
			insertLine(node.getlineNumber(),binary,opcode);
		}
	  else if(!node.getName().compare("STP")){
			vector<bool> binary{0,0,0};
			vector<bool> opcode = {1,1,1};
			insertLine(node.getlineNumber(),binary,opcode);
		}
		else if(!node.getName().compare("VAR")){
			stringstream intVal(node.getVariableNumber());
    int x = 0;
    intVal >> x;

			vector<bool> binary  = this->decimalToBinary(x);
			int lineNumber = node.getlineNumber();
			for (unsigned int i = 0; i < 32; i++){
			if(i < binary.size()){
				machineCode.at(lineNumber).push_back(binary.at(i));
			}else{
				machineCode.at(lineNumber).push_back(0);
			}
		}
	}
}
}

void Assembler::insertLine(int lineNumber, vector<bool> binary,vector<bool> opcode){
	int j = 0;
	for (unsigned int i = 0; i < 32; i++){
			if(i < binary.size()){
				machineCode.at(lineNumber).push_back(binary.at(i));
			}else if( i >12 && i <16){
					machineCode.at(lineNumber).push_back(opcode.at(j));
					j++;
			}else{
					machineCode.at(lineNumber).push_back(0);
			}
		}
}

int Assembler::findVarName(string varName){
		for (LookUpNode &node : lookUpTable){
			if(node.getVarNam() == varName){
				return node.getlineNumber();
			}
		}
		return 0;
}


vector<bool> Assembler::decimalToBinary(int numberToConvert)
{

  	vector<bool>binaryNum;
    int i = 0;
    while (numberToConvert > 0) {

        binaryNum.push_back(numberToConvert % 2);
        numberToConvert = numberToConvert / 2;
        i++;
    }
		return binaryNum;
}
void Assembler::displayMachineCode(){
	for (unsigned int i =0; i < machineCode.size(); i++)
	{
		for(unsigned int j = 0; j < machineCode.at(i).size(); j++)
		{
			cout << machineCode.at(i).at(j);
		}
		cout << endl;
	}
}


int main(){
  Assembler ass;
	ass.init();
  ass.readSource();
	ass.createMachineCode();
	ass.displayMachineCode();
  return 0;
}
