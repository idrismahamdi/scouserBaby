#include <array>

using namespace std;


class Baby {
private:
	int memory[32][32];
public:
	/* 8 actions*/ 
	void initMemory();
	void increment_CI();
	void fetch();
	void decode();
	void execute();
	void readFile();
	void printMemory();
	void assignArray();
	//void initOpcodes();


};
