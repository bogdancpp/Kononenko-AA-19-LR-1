#include <iostream>
#include <string>

using namespace std;

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl
		<< "6. Save to file" << endl << "7. Download from file" << endl << "0. Exit" << endl << endl
		<< "Selected action - ";
}

struct Pipe
{
	unsigned short id; 
	float diametr, length; // diameter mm, length metr
	bool repair = false;
};

struct CprStn
{
	unsigned short id, totalShop, workShop;
	string name;
};

int main()
{
	system("color 70");
	while (true)
	{
		menu();
		int n;
		cin >> n; 
		cout << endl;
	}
	return 0;
}