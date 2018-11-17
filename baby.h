#include <array>

using namespace std;


class Baby {
public:
	/* 8 actions*/
	void initMemory();
	void setPresent();
	void increment_CI();
	void fetch();
	void decode();
	void execute();
	void readFile();
	void printMemory();
	void assignArray();
	int binaryToDecimal(int arr[], int size);
	void decimalToBinary(int n, int size, int arr[]);
	int getOperand(int arr[]);
	void testDisplay();
	void display();
	//void initOpcodes();


	void jmp();
	void jrp();
	void ldn();
	void sto();
	void sub();
	void cmp();
	void stp();

};
