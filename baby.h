#include <array>

using namespace std;

struct opcode{
	array<bool, 3> opcode;
};

class Baby {
private:
	bool memory[32][32];
public:
	/* 8 actions*/ 
	void initMemory();
//	void Baby::fetch();
//	void Baby::decode();
//	void Baby::execute();
	void readFile();
	void printMemory();
	//void initOpcodes();


};
