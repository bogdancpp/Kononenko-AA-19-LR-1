#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "CPipe.h"
#include "CCS.h"
#include "Utils.h"

using namespace std;

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl 
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl
		<< "6. Save to file" << endl << "7. Download from file" << endl << "0. Exit" << endl << endl;
}
// +++++++++++++++++++++++=
ostream& operator << (ostream& out, const vector<CCS>& cs)
{
	for (const CCS& c : cs)
	{
		out << c;
	}
	return out;
} 
// +++++++++++++++
ostream& operator << (ostream& out, const vector<CPipe>& p)
{
	for (const CPipe& pipe : p)
	{
		out << pipe;
	}
	return out;
} 
// ???????
ofstream& operator << (ofstream& fout, const vector<CCS>& cs)
{
	for (const CCS& c : cs)
	{
		fout.precision(2);
		fout << c.id << endl << c.name << endl << c.totalShop << endl
			<< c.workShop << endl << c.efficiency << endl << endl;
	}
	return fout;
} 

ofstream& operator << (ofstream& fout, const vector<CPipe>& pipes)
{
	for (const CPipe& p : pipes)
	{
		fout << p.id << endl << p.diametr << endl
			<< p.length << endl << p.repair << endl << endl;
	}
	return fout;
}

// как это в класс убрать
ifstream& operator >> (ifstream& in, CPipe& p) // 
{
	in >> p.id;
	in >> p.diametr;
	in >> p.length;
	in >> p.repair;

	return in;
}

ifstream& operator >> (ifstream& in, vector<CPipe>& pipes)
{
	for(CPipe& p : pipes)
	{
		in >> p;
	}
	return in;
}

ifstream& operator >> (ifstream& in, CCS& c)
{
	in >> c.id;
	in >> c.name;
	in >> c.totalShop;
	in >> c.workShop;
	in >> c.efficiency;
	
	return in;
}

ifstream& operator >> (ifstream& in, vector<CCS>& cs)
{
	for (CCS& c : cs)
	{
		in >> c;
	}
	return in;
}

CCS AddCS()
{
	CCS r;
	cout << "Adding a compressor station..." << endl;

	cout << "Enter the name of the compressor station - " ;
	cin.ignore();
	getline(cin, r.name);

	cout << "Enter the number of workshops - ";
	r.totalShop = CheckNum(0, 1000, "Enter the number of workshops (enter correct value) - ");

	cout << "Enter the number of workshop workers - ";
	r.workShop = CheckNum(0, r.totalShop, "Enter the number of workshops  workers (enter correct value) - ");

	srand(time(NULL));
	r.efficiency = 1. / (rand() % 100);

	cout << endl;
	return r;
}

CPipe AddPipe()
{
	CPipe p;

	cout <<"Adding a pipe..." << endl;

	cout << "Enter the diameter in millimeters - ";
	p.diametr = CheckNum<double>(0, 10000, "Enter the diameter in millimeters (more zero and not letter) - ");

	cout << "Enter the length in meters - ";
	p.length = CheckNum<double>(0, 10000, "Enter the length in meters (more zero and not letter) - ");

	cout << endl;
	return p;
} 

void EditPipe(vector<CPipe>& pipes)
{
	cout << "Id of the pipe you want to edit: " << 0 << " - " << pipes.size()-1 << endl;

	cout << "Choose - ";
	int id, u;
	u = pipes.size() - 1; // Почему то если подставить сразу - выдает ошибку???
	id = CheckNum(0, u, "Select an existing id ");

	cout << "0. The pipe is serviceable" << endl << "1. Pipe repair" << endl;
	int choice;
	cout << "Choose - ";
	choice = CheckNum(0, 1, "Select 0 or 1 not otherwise - ");


	pipes[id].repair = choice;
	cout << endl;
}

void EditCs(vector<CCS>& cs)
{
	cout << "Id of the compressor station you want to edit: " << 0 << " - " << cs.size()-1 << endl;

	cout << "Choose - ";
	int id,u;
	u = cs.size() - 1;
	id = CheckNum(0, u, "Select an existing id ");

	cout << "0. Start the workshop" << endl << "1. Stop the workshop" << endl;
	int choice;
	cout << "Choose - ";
	choice = CheckNum(0, 1, "Select 0 or 1 not otherwise - ");


	if (choice == 0 && (cs[id].totalShop > cs[id].workShop)) // сделать проверку ещё когда вывод всех объектов
	{
		cs[id].workShop += 1;// ternarn
	}
	else if (choice == 1)
	{
		cs[id].workShop -= 1;
	}
	else
	{
		cout << "\nMaking more workshops impossible\n";
	}
	cout << endl;
}

void ViewThat(const vector<CPipe>& pipes, const vector<CCS>& cs)
{
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor station\n";
	int choise;
	choise = CheckNum(1, 3, "Enter from 1 to 3\n");
	switch (choise)
	{
	case 1:
	{
		cout << pipes;
		cout << cs;
		break;
	}
	case 2:
	{
		cout << "Select id you want to output: 0 - " << pipes.size() - 1 << endl;
		int OutPipe, u;
		u = pipes.size(); // 4 byte like int sizeof
		cout << "Select - ";
		OutPipe = CheckNum(0, u, "Enter from existing pipes\n");
		cout << endl;
		cout << pipes[OutPipe] << endl;
		break;
	}
	case 3:
	{
		cout << "Select id you want to output: 0 - " << cs.size() - 1 << endl;
		int OutCs, u;
		u = cs.size();
		cout << "Select - ";
		OutCs = CheckNum(0, u, "Enter from existing cs\n\n");
		cout << endl;
		cout << cs[OutCs] << endl;
		break;
	}
	}

}

void SaveAll(const vector<CPipe>& pipes, const vector<CCS>& cs)
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
			fout << pipes;
			fout << cs;
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

void LoadAll(vector<CPipe>& pipes, vector<CCS>& cs)
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
	/*	pipes.reserve(lenpipe);
		cs.reserve(lencs);*/

		fin >> pipes;
		fin >> cs;
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
	vector <CPipe> pipes;
	vector <CCS> cs;

	while (true)
	{
		menu();

		cout << "Selected action - ";
		int n;
		n = CheckNum(0, 7, "Selected action(enter correct value from 0 to 7) - ");
		cout << endl;

		switch (n)
		{
		case 1:
			pipes.push_back(AddPipe());
			break;
		case 2:
			cs.push_back(AddCS());
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