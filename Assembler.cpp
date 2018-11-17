#include "baby.h"
#include "opcodes.h"
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

class Assembler {

public:
	void readSource();
  void testOperand(string, int);

  vector<LookUpNode> lookUpTable;
};

void Assembler::readSource(){

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
      while ((pos = line.find(delimiter)) != string::npos) {
          token = line.substr(0, pos);
          //cout << token << endl;
          codeLine = token;
          line.erase(pos, line.length());
        }


        string word;
        vector<string> words;

        for (stringstream s(line); s >> word; )
        words.push_back(word);

        for (int i=0; i<words.size(); i++)
        {
          if(!words.at(i).compare("VAR")){
            lookUpTable.at(lineNum).setNumbers(line.at(lineNum));
          }
          cout << words.at(i) << '\n';
        }

    lineNum++;

  }
  out.close();
}

void Assembler::testOperand(string substring, int lineIndex){

  if(!substring.compare("JMP")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("JRP")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("LDN")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("STO")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("SUB")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("CMP")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
  else if(!substring.compare("STP")){
    cout <<"Successful process of substring: " <<substring << endl;
  }
}


int main(){
  Assembler ass;
  ass.readSource();
  return 0;
}
