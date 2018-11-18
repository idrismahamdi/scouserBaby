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
				//	cout << codeLine << endl;

				if(testOperand(codeLine) != true && getVariable != true){
					lookUpTable.at(lineNum).setVarNam(codeLine.substr(0, codeLine.size()-1));
				}
				if(getVariable == true){
					std::cout << "inLoop" << '\n';
						lookUpTable.at(lineNum).setVariableNumber(codeLine);
						getVariable = false;
				}
					if(testOperand(codeLine)==true){
						lookUpTable.at(lineNum).setName(codeLine);
						std::cout << lineNum<< '\n';
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

				cout <<  "Opcode: "<<lookUpTable.at(lineNum).getName() << endl;
				cout <<  "Line Number: "<<lookUpTable.at(lineNum).getlineNumber() << endl;
				cout <<  "START: " <<lookUpTable.at(lineNum).getStart() << endl;
				cout <<  "End: "<<lookUpTable.at(lineNum).getEnd() << endl;
				cout <<  "variable Number "<<lookUpTable.at(lineNum).getVariableNumber() << endl;
				cout <<  "var Name "<<lookUpTable.at(lineNum).getVarNam() << endl;

				lineNum++;
}




}

  out.close();
}

bool Assembler::testOperand(string substring){

  if(!substring.compare("JMP")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
  else if(!substring.compare("JRP")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
  }
  else if(!substring.compare("LDN")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
  else if(!substring.compare("STO")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
  else if(!substring.compare("SUB")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
  else if(!substring.compare("CMP")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
  else if(!substring.compare("STP")){
    cout <<"Successful process of substring: " <<substring << endl;
		return true;
	}
	else if(!substring.compare("VAR")){
		cout <<"Successful process of substring:	 " <<substring << endl;
		return true;
	}else{
		return false;
	}
}

void Assembler::createMachineCode(){

	for (LookUpNode &node : lookUpTable) {
		if(!node.getName().compare("JMP")){

		}
	  else if(!node.getName().compare("JRP")){
			std::cout << "cunt monkey2" << '\n';
	  }
	  else if(!node.getName().compare("LDN")){
			int lineRef = findVarName(node.getVariableNumber());
			vector<bool> binary = this->decimalToBinary(lineRef);
			int lineIndex = 0;
			for (unsigned int i = 0; i < binary.size(); i++){
				machineCode(node.getlineNumber()).push_back(binary.at(i));
			}


			cout << lineRef << endl;
		}
	  else if(!node.getName().compare("STO")){
			std::cout << "cunt monkey4" << '\n';
		}
	  else if(!node.getName().compare("SUB")){
			std::cout << "cunt monkey5" << '\n';
		}
	  else if(!node.getName().compare("CMP")){
			std::cout << "cunt monkey6" << '\n';
		}
	  else if(!node.getName().compare("STP")){
			std::cout << "cunt monkey7" << '\n';
		}
		else if(!node.getName().compare("VAR")){
			std::cout << "cunt monkey8" << '\n';
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

int main(){
  Assembler ass;
	ass.init();
  ass.readSource();
	ass.createMachineCode();
  return 0;
}
