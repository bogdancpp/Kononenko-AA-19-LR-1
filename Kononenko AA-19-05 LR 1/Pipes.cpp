#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl 
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl
		<< "6. Save to file" << endl << "7. Download from file" << endl << "0. Exit" << endl << endl;
}

void CheckInt(int& n, int less, int more, string s)
{
	cin >> n;
	while (cin.fail() || n < less || n > more)
	{
		cout << s;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> n;
	}
}

void CheckFloat(float& n, string s)
{
	cin >> n;
	while (cin.fail() || n < 0)
	{
		cout << s;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> n;
	}
}

struct Pipe
{
	unsigned short id; 
	float diametr, length; // diameter mm, length metr
	bool repair = false;
};

struct CprStn
{
	unsigned short id;
	int totalShop, workShop;
	float efficiency;
	string name;
};

CprStn AddCS(int j)
{
	CprStn r;
	r.id = j;
	cout << "Adding a compressor station..." << endl;

	cout << "Enter the name of the compressor station - " ;
	cin.ignore();
	getline(cin, r.name);
	//cin >> r.name;//getline

	cout << "Enter the number of workshops - ";
	CheckInt(r.totalShop, 0, 10000, "Enter the number of workshops (enter correct value) - ");

	cout << "Enter the number of workshop workers - ";
	CheckInt(r.workShop, 0, r.totalShop, "Enter the number of workshops  workers (enter correct value) - ");

	r.efficiency = 1. / (rand() % 100);

	cout << endl;
	return r;
}

Pipe AddPipe(int i)
{
	Pipe p;
	p.id = i;

	cout <<"Adding a pipe..." << endl;

	cout << "Enter the diameter in millimeters - ";
	CheckFloat(p.diametr, "Enter the diameter in millimeters (more zero and not letter) - ");

	cout << "Enter the length in meters - ";
	CheckFloat(p.length, "Enter the length in meters (more zero and not letter) - ");

	cout << endl;
	return p;
} 

void EditPipe(vector<Pipe>& pipes)
{
	cout << "Id of the pipe you want to edit: " << 0 << " - " << pipes.size() << endl;

	cout << "Choose - ";
	int id;
	CheckInt(id, 0, pipes.size()-1, "Select an existing id ");

	cout << "0. The pipe is serviceable" << endl << "1. Pipe repair" << endl;
	int choice;
	cout << "Choose - ";
	CheckInt(choice, 0, 1, "Select 0 or 1 not otherwise - ");

	pipes[id].repair = choice;
	cout << endl;
}

void EditCs(vector<CprStn>& cs)
{
	cout << "Id of the compressor station you want to edit: " << 0 << " - " << cs.size() << endl;

	cout << "Choose - ";
	int id;
	CheckInt(id, 0, cs.size() - 1, "Select an existing id ");

	cout << "0. Start the workshop" << endl << "1. Stop the workshop" << endl;
	int choice;
	cout << "Choose - ";
	CheckInt(choice, 0, 1, "Select 0 or 1 not otherwise - ");

	if (choice == 0) // ������� �������� ��� ����� ����� ���� ��������
	{
		cs[id].workShop += 1;// ternarn
	}
	else
	{
		cs[id].workShop -= 1;
	}
	cout << endl;
}

string checkRepair(const Pipe& p) // tenarnarniy operator ne rabotaet 
{
	return (p.repair)  ?  "Unworking \n\n" : "Working \n\n"  ;
}

void ViewAll(const vector<Pipe>& pipes,const vector<CprStn>& cs)
{
	cout <<  "All available objects..." << endl << endl;
	for (size_t i = 0; i < pipes.size(); i++)
	{
		cout << "Pipe id: " << pipes[i].id << endl << "diametr: " << pipes[i].diametr << endl
			<< "length: " << pipes[i].length << endl << "pipe condition: " << checkRepair(pipes[i]) << endl;
		//	(pipes[i].repair) ? cout << "Working \n\n" : cout << "Unworking \n\n";
	}	
	for (size_t i = 0; i < cs.size(); i++)
	{
		cout.precision(2);
		cout << "CS id: " << cs[i].id << endl << "Name: " << cs[i].name 
			<< endl << "Quantity of workshops: " << cs[i].totalShop << endl
			<< "Quantity of workshop workers: " << cs[i].workShop << endl
			<< "Efficiency: " << cs[i].efficiency << endl << endl;
	}
}

void ViewThat(const vector<Pipe>& pipes, const vector<CprStn>& cs)
{
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor station\n";
	int choise;
	CheckInt(choise, 1, 3, "Enter from 1 to 3\n");
	switch (choise)
	{
	case 1:
	{
		ViewAll(pipes, cs);
		break;
	}
	case 2:
	{
		cout << "Select id you want to output: 0 - " << pipes.size() - 1 << endl;
		int OutPipe;
		cout << "Select - ";
		CheckInt(OutPipe, 0, pipes.size(), "Enter from existing pipes\n");
		cout << endl;
		cout << "Pipe id: " << pipes[OutPipe].id << endl << "diametr: " << pipes[OutPipe].diametr << endl
			<< "length: " << pipes[OutPipe].length << endl << "pipe condition: " << checkRepair(pipes[OutPipe]) << endl;
		break;
	}
	case 3:
	{
		cout << "Select id you want to output: 0 - " << cs.size() - 1 << endl;
		int OutCs;
		cout << "Select - ";
		CheckInt(OutCs, 0, cs.size(), "Enter from existing cs\n\n");
		cout << endl;
		cout.precision(2);
		cout << "CS id: " << cs[OutCs].id << endl << "Name: " << cs[OutCs].name
			<< endl << "Quantity of workshops: " << cs[OutCs].totalShop << endl
			<< "Quantity of workshop workers: " << cs[OutCs].workShop << endl
			<< "Efficiency: " << cs[OutCs].efficiency << endl << endl;
		break;
	}
	}

}

void SaveAll(const vector<Pipe>& pipes, const vector<CprStn>& cs)
{
	ofstream fout;

	fout.open("Bogdan_LR1.txt", ios::out);
	if (fout.is_open())
	{
		fout << pipes.size() << endl;
		fout << cs.size() << endl;
		fout << endl;

		if (pipes.size() != 0 || cs.size() != 0)
		{
			for (size_t i = 0; i < pipes.size(); i++)
			{
				string k = checkRepair(pipes[i]);
				fout << pipes[i].id << endl << pipes[i].diametr << endl
					<< pipes[i].length << endl << pipes[i].repair << endl << endl;
			}

			for (size_t i = 0; i < cs.size(); i++)
			{
				fout.precision(2);
				fout << cs[i].id << endl << cs[i].name << endl << cs[i].totalShop << endl
					<< cs[i].workShop << endl << cs[i].efficiency << endl << endl;
			}
			cout << "File saved" << endl << endl;
		}
		else
		{
			cout << "First, create at least one pipe or compressor station..." << endl << endl;
		}
		fout.close();
	}
	else
	{
		cout << "Fail is not open" << endl;
	}
}

void LoadAll(vector<Pipe>& pipes, vector<CprStn>& cs)
{
	ifstream fin;
	fin.open("Bogdan_LR1.txt", ios::in);
	
	if (fin.is_open())
	{
		int lenpipe, lencs;
		fin >> lenpipe;
		fin >> lencs;

		pipes.resize(lenpipe);
		cs.resize(lencs);

		for (size_t i = 0; i < pipes.size(); i++)
		{
			fin >> pipes[i].id;
			fin >> pipes[i].diametr;
			fin >> pipes[i].length;
			fin >> pipes[i].repair;
		}

		for (size_t i = 0; i < cs.size(); i++)
		{
			fin >> cs[i].id;
			fin >> cs[i].name;
			fin >> cs[i].totalShop;
			fin >> cs[i].workShop;
			fin >> cs[i].efficiency;
		}
		fin.close();
	}
	else
	{
		cout << "Fail is not open" << endl << endl;
	}
}

int main()
{
	system("color 70");
	cout << "\t\tKononenko Bogdan AA-19-05\n";
	vector <Pipe> pipes;
	vector <CprStn> cs;
	size_t i = 1, j = 1;

	while (true)
	{
		menu();

		cout << "Selected action - ";
		int n;
		CheckInt(n, 0, 7, "Selected action(enter correct value from 0 to 7) - ");
		cout << endl;

		switch (n)
		{
		case 1:
			pipes.reserve(i);
			pipes.push_back(AddPipe(--i));
			i += 2;
			break;
		case 2:
			cs.reserve(j);
			cs.push_back(AddCS(--j));
			j += 2;
			break;
		case 3:
			ViewThat(pipes, cs);
			break;
		case 4:
			if (pipes.size() != 0)
			{
				EditPipe(pipes);
			}
			else
			{
				cout << "First, create a pipe ..." << endl << endl;
			}
			break;
		case 5:
			if (cs.size() != 0)
			{
				EditCs(cs);
			}
			else
			{
				cout << "First, create a  compressor station ..." << endl << endl;
			}
			break;
		case 6:
			SaveAll(pipes, cs);
			break;
		case 7:
			LoadAll(pipes, cs);
			break;
		case 0:
			return 0;
			break;
		}
	}
	return 0;
}