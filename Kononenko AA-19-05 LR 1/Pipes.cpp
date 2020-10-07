#include <iostream>
#include <string>
#include <vector>

using namespace std;

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. View all objects" << endl
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

Pipe AddPipe(int i) //1
{
	Pipe p;
	p.id = i;
	cout <<"Adding a pipe..." << endl;
	cout << "Enter the diameter in millimeters - ";
	cin >> p.diametr;
	cout << "Enter the length in meters - ";
	cin >> p.length;
	cout << endl;
	return p;
}

void ViewAll(vector<Pipe> pipes) // add CS
{
	cout <<  "All available objects..." << endl;
	for (size_t i = 0; i < pipes.size(); i++)
	{
		cout << "Pipe id: " << pipes[i].id << endl << "diametr: " << pipes[i].diametr << endl
			<< "length: " << pipes[i].length << endl << "pipe condition: " +
			(pipes[i].repair) ? cout << "Working \n\n" : cout << "Unworking \n\n";
	}
}


int main()
{
	system("color 70");
	vector <Pipe> pipes;
	while (true)
	{
		menu();
		int n;
		size_t i = 0;
		cin >> n; 
		cout << endl;
		switch (n)
		{
		case 1:
			pipes.resize(i + 1);
			pipes[i] = AddPipe(i);
			i++;
			break;
		case 2:
			//AddCS(p);
			break;
		case 3:
			ViewAll(pipes);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 0:
			break;
		}
	}
	return 0;
}