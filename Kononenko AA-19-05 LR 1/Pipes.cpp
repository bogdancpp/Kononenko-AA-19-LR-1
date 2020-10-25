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

template <typename T>
T CheckNum(T less, T more, string s)
{
	T num;
	cin >> num;
	while (cin.fail() || num < less || num > more)
	{
		cout << s;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> num;
	}
	return num;
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

ostream& operator << (ostream& out, const vector<CprStn>& cs)
{
	for (const CprStn& c : cs)
	{
		out.precision(2);
		out << "CS id: " << c.id << endl << "Name: " << c.name
			<< endl << "Quantity of workshops: " << c.totalShop << endl
			<< "Quantity of workshop workers: " << c.workShop << endl
			<< "Efficiency: " << c.efficiency << endl << endl;
	}
	return out;
}

ostream& operator << (ostream& out, const CprStn& cs)
{
		out.precision(2);
		out << "CS id: " << cs.id << endl << "Name: " << cs.name
			<< endl << "Quantity of workshops: " << cs.totalShop << endl
			<< "Quantity of workshop workers: " << cs.workShop << endl
			<< "Efficiency: " << cs.efficiency << endl << endl;
	return out;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "Pipe id: " << p.id << endl << "diametr: " << p.diametr << endl
		<< "length: " << p.length << endl << "pipe condition: ";
	return out;
}

ofstream& operator <<(ofstream& fout, const vector<CprStn>& cs)
{
	for (const CprStn& c : cs)
	{
		fout.precision(2);
		fout << c.id << endl << c.name << endl << c.totalShop << endl
			<< c.workShop << endl << c.efficiency << endl << endl;
	}
	return fout;
}

ofstream& operator <<(ofstream& fout, const vector<Pipe>& pipes)
{
	for (const Pipe& p : pipes)
	{
		fout << p.id << endl << p.diametr << endl
			<< p.length << endl << p.repair << endl << endl;
	}
	return fout;
}

ifstream& operator >> (ifstream& in, vector<Pipe>& pipes)
{
	for(Pipe& p : pipes)
	{
		in >> p.id;
		in >> p.diametr;
		in >> p.length;
		in >> p.repair;
	}
	return in;
}

ifstream& operator >> (ifstream& in, vector<CprStn>& cs)
{
	for (CprStn& c : cs)
	{
		in >> c.id;
		in >> c.name;
		in >> c.totalShop;
		in >> c.workShop;
		in >> c.efficiency;
	}
	return in;
}

CprStn AddCS(int j)
{
	CprStn r;
	r.id = j;
	cout << "Adding a compressor station..." << endl;

	cout << "Enter the name of the compressor station - " ;
	cin.ignore();
	getline(cin, r.name);

	cout << "Enter the number of workshops - ";
	r.totalShop = CheckNum(0, 1000, "Enter the number of workshops (enter correct value) - ");

	cout << "Enter the number of workshop workers - ";
	r.workShop = CheckNum(0, r.totalShop, "Enter the number of workshops  workers (enter correct value) - ");

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
	p.diametr = CheckNum<double>(0, 10000, "Enter the diameter in millimeters (more zero and not letter) - ");

	cout << "Enter the length in meters - ";
	p.length = CheckNum<double>(0, 10000, "Enter the length in meters (more zero and not letter) - ");

	cout << endl;
	return p;
} 

void EditPipe(vector<Pipe>& pipes)
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

void EditCs(vector<CprStn>& cs)
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


	if (choice == 0) // сделать проверку ещё когда вывод всех объектов
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
	for (const Pipe& p : pipes)
	{
		cout << p << checkRepair(p);
	}
	cout << cs;
}

void ViewThat(const vector<Pipe>& pipes, const vector<CprStn>& cs)
{
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor station\n";
	int choise;
	choise = CheckNum(1, 3, "Enter from 1 to 3\n");
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
		int OutPipe, u;
		u = pipes.size();
		cout << "Select - ";
		OutPipe = CheckNum(0, u, "Enter from existing pipes\n");
		cout << endl;
		cout << pipes[OutPipe] << checkRepair(pipes[OutPipe]) << endl;
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
	vector <Pipe> pipes;
	vector <CprStn> cs;
	size_t i = 1, j = 1;

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