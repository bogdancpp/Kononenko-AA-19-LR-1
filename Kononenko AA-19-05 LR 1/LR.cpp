#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "CPipe.h"
#include "CCS.h"
#include "Utils.h"

using namespace std;

template <typename C> 
void ViewAllId(vector<C>& pc) // если бы не было одинакого метода GetId пришлось бы писать if C == CPipe?
{
	int counter = 0;
	for (C& i : pc) 
	{
		if (counter == pc.size() - 1)
			cout << i.GetId();
		else
			cout << i.GetId() << ",  ";
		counter++;
	}
	cout << endl;
}

template<typename C>
void ViewAllName(vector<C> pc)
{
	int counter = 0;
	for (C& i : pc)
	{
		if (counter == pc.size() - 1)
			cout << i.name;
		else
			cout << i.name << ",  ";
		counter++;
	}
	cout << endl;
}

template <typename C>
int CheckChoiceId(vector<C>& pc)
{
	int choice = 0;
	do
	{
		cout << "\nChoice ID - ";
		cin >> choice;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
		{
			for (C& i : pc)
			{
				if (choice == i.GetId())
					return choice;
			}
		}
	} while (true);
}

template<typename C>
string CheckChoiceName(vector<C>& pc)
{
	string choice = "";
	do
	{
		cout << "\nChoice Name - ";
		cin >> choice;
		for (C& i : pc)
		{
			if (choice == i.name)
				return choice;
		}
	} while (true);
}

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl
		<< "0. Exit" << endl << endl << "Selected action - ";

}

template<typename C>
ostream& operator << (ostream& out, const vector<C>& pc)
{
	for (const C& i : pc)
	{
		out << i;
	}
	return out;
}

ofstream& operator << (ofstream& fout, vector<CCS>& cs)
{
	for (CCS& c : cs)
	{
		fout.precision(2);
		fout << c.GetId() << endl << c.name << endl << c.totalShop << endl
			<< c.workShop << endl << c.efficiency << endl << endl;
	}
	return fout;
} 
ofstream& operator << (ofstream& fout, vector<CPipe>& pipes)
{
	for (CPipe& p : pipes)
	{
		fout << p.GetId() << endl << p.diametr << endl
			<< p.length << endl << p.repair << endl << endl;
	}
	return fout;
}

ifstream& operator >> (ifstream& in, CPipe& p) // 
{
	int k;
	in >> k;
	p.SetId(k);
	in >> p.diametr;
	in >> p.length;
	in >> p.repair;

	return in;
}
ifstream& operator >> (ifstream& in, CCS& c)
{
	int id;
	in >> id;
	c.SetId(id);
	in >> c.name;
	in >> c.totalShop;
	in >> c.workShop;
	in >> c.efficiency;
	
	return in;
}

template <typename C>
ifstream& operator >> (ifstream& in, vector<C>& pc)
{
	for (C& c : pc)
	{
		in >> c;
	}
	return in;
}

CCS AddCS()
{
	CCS r;
	cout << "Enter the name of the compressor station - ";
	cin.ignore();
	getline(cin, r.name);

	cout << "Enter the number of workshops - ";
	r.totalShop = CheckNum(0, 1000);
	cout << "Enter the number of workshop workers - ";
	r.workShop = CheckNum(0, r.totalShop);

	srand(time(NULL));
	r.efficiency = 1. / (rand() % 10);
	cout << endl;
	return r;
}

CPipe AddPipe()
{
	CPipe p;
	cout << "\nEnter the diameter in millimeters - ";
	p.diametr = CheckNum<double>(0, 10000);
	cout << "Enter the length in meters - ";
	p.length = CheckNum<double>(0, 10000);
	cout << endl;
	return p;
} 

void EditAllPipes(vector<CPipe>& pipes)
{
	cout << "0. The pipes is serviceable\n1. Pipes repair\nChoose - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (CPipe& i : pipes)
	{
		i.repair = choice;
	}
}

vector<CPipe> EditSeveralPipes(vector<CPipe>& pipes)
{
	vector<int> res;
	do
	{
		cout << "Id of the pipe you want to edit: ";
		ViewAllId(pipes);
		int ch = CheckChoiceId(pipes);
		res.push_back(ch);
		cout << "\n1. To select one more pipe\n2. Enough\nSelect - ";
	} while (CheckNum(1, 2) == 1);

	cout << "\n0. The pipe is serviceable\n1. Pipe repair\nChoose - ";
	int choice = CheckNum(0, 1);
	for (int i : res) // как лучше так или через res.size()
	{
		pipes[i].repair = choice;
	}
	cout << endl;
	return pipes;
}

void EditPipe(vector<CPipe>& pipes)
{
	cout << "1. Edit all existing ones\n2. Edit several by choice\nSelect - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << endl;
		EditAllPipes(pipes); // что лучше здесь метод или функция? что быстрее?
	}
	else
	{
		cout << endl;
		EditSeveralPipes(pipes); // что лучше здесь метод или функция? что быстрее?
	}
}

vector<CCS> EditAllCs(vector<CCS>& cs)
{
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (CCS& i : cs)
	{
		if (choice == 0 && (i.totalShop > i.workShop)) 
		{
			i.workShop += 1;
		}
		else if (i.workShop > 0)
		{
			i.workShop -= 1;
		}
	}
	return cs;
}

vector<CCS> EditSeveralCs(vector<CCS>& cs)
{
	vector<int> res;
	do
	{
		cout << "Id of the compressor station you want to edit: ";
		ViewAllId(cs);
		int ch = CheckChoiceId(cs);
		res.push_back(ch);
		cout << "\n1. To select one more pipe\n2. Enough\nSelect - ";
	} while (CheckNum(1, 2) == 1);

	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	if (CheckNum(0, 1) == 0)
	{
		for (int i : res) // как лучше так или через res.size()
		{
			if (cs[i].totalShop > cs[i].workShop)
				cs[i].workShop += 1;
		}
	}
	else
	{
		for (int i : res)
		{
			if (cs[i].workShop > 0)
				cs[i].workShop -= 1;
		}
	}
	return cs;
}

void EditCs(vector<CCS>& cs)
{
	cout << "1. Edit all existing ones\n2. Edit several by choice\nSelect - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << endl;
		EditAllCs(cs); // что лучше здесь метод или функция? что быстрее?
	}
	else
	{
		cout << endl;
		EditSeveralCs(cs); // что лучше здесь метод или функция? что быстрее?
	}
}

void ViewThat(vector<CPipe>& pipes, vector<CCS>& cs)
{
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor station\nSelect - ";
	switch (CheckNum(1, 3))
	{
		case 1:
		{
			cout << endl;
			cout << pipes;
			cout << cs;
			break;
		}
		case 2:
		{
			cout << "Select id you want to output: ";
			ViewAllId(pipes);
			int OutPipe = CheckChoiceId(pipes);
			cout << pipes[OutPipe] << endl;
			break;
		}
		case 3:
		{
			cout << "Select id you want to output: ";
			ViewAllId(cs);
			int OutCs;
			OutCs = CheckChoiceId(cs);
			cout << endl << cs[OutCs] << endl;
			break;
		}
	}
}

void SaveAll(vector<CPipe>& pipes, vector<CCS>& cs)
{
	ofstream fout;
	string name;
	cout << "Enter name fail: ";
	cin >> name;
	fout.open(name, ios::out);
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
	string name;
	cout << "Enter name fail: ";
	cin >> name;
	fin.open(name, ios::in);
	
	if (fin.is_open())
	{
		int lenpipe, lencs;
		fin >> lenpipe;
		fin >> lencs;

		pipes.resize(lenpipe);
		cs.resize(lencs);
	/*	pipes.reserve(lenpipe);
		cs.reserve(lencs);*/  ///////////// почему так не работает
		fin >> pipes;
		fin >> cs;
		fin.close();
		cout << "Data downloaded\n\n";
	}
	else
	{
		cout << "The file does not exist" << endl << endl;
	}
}

bool SearchById(CPipe& p, int param)
{
	return p.GetId() == param;
}

bool SearchByRepair(CPipe& p, int param)
{
	return p.repair == param - 1;
}

//template <typename T> почему нельзя использовать шаблоны 
bool SearchByName(CCS& cs, string name)
{
	return cs.name == name;
}
//{
//	if (T == CCS)
//	{
//		return pc.name == name;
//	}
//	else
//	{
//		// у трубы нет имени
//	}
//}

bool SearchByPercent(CCS& cs, int param)
{
	return 100 * (1 - (1. * cs.workShop) / cs.totalShop) >= param;
}

template <typename N, typename C>
void СonByFilter(vector<C>& vect, bool(*f)(C& p, N param), N param)
{
	for (C& i : vect)
	{
		if (f(i, param))
		{
			cout << endl << i;
		}
	}
	cout << endl;
}

void SearchByFilter(vector<CPipe>& pipes, vector<CCS>& cs)
{
	cout << "1. Search by pipes\n2. Search by compressor stations\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "\n1. By ID\n2. By condition\nSelect action - ";
		if (CheckNum(1, 2) == 1)
		{
			cout << "Enter ID: ";
			ViewAllId(pipes);
			int ch = CheckChoiceId(pipes);
			СonByFilter(pipes, SearchById, ch);
		}
		else
		{
			cout << "\n1. Working\n2. Unworking\nSelect action - ";
			СonByFilter(pipes, SearchByRepair, CheckNum(1, 2));
		}
	}
	else
	{
		cout << "\n1. By name\n" << "2. By percentage of unused workshops\nSelect action - ";
		if (CheckNum(1, 2) == 1)
		{
			int counter = 0;
			cout << "\nEnter a name from this list: ";
			ViewAllName(cs);
			string name = CheckChoiceName(cs);
			СonByFilter(cs, SearchByName, name);
		}
		else
		{
			cout << "\nEnter the number of percentages - ";
			СonByFilter(cs, SearchByPercent, CheckNum(0, 100));
		}
	}
}

void DeleteObject(vector <CPipe>& pipes,vector <CCS>& cs)
{
	cout << "1. Delete pipe\n2. Delete compressor station\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "Enter ID: ";
		ViewAllId(pipes);
		int ch = CheckChoiceId(pipes);
		pipes.erase(pipes.begin() + ch);    // https://ru.cppreference.com/w/cpp/container/vector/erase
		cout << endl;
	}
	else
	{
		cout << "Enter ID: ";
		ViewAllId(cs);
		int ch = CheckChoiceId(cs);
		cs.erase(cs.begin() + ch);
		cout << endl;
	}
}

int main()
{
	system("color 70");
	vector <CPipe> pipes;
	vector <CCS> cs;

	while (true)
	{
		menu();
		switch (CheckNum(0, 9))
		{
			case 1:
			{
				pipes.push_back(AddPipe());
				break;
			}
			case 2:
			{
				cs.push_back(AddCS());
				break;
			}
			case 3:
			{
				ViewThat(pipes, cs);
				break;
			}
			case 4:
			{
				if (pipes.size() != 0)
					EditPipe(pipes);
				else
					cout << "First, create a pipe ...\n\n";
				break;
			}
			case 5:
			{
				if (cs.size() != 0)
					EditCs(cs);
				else
					cout << "First, create a  compressor station ...\n\n";
				break;
			}
			case 6:
			{
				SearchByFilter(pipes, cs);
				break;
			}
			case 7:
			{
				DeleteObject(pipes, cs);
				break;
			}
			case 8:
			{
				SaveAll(pipes, cs);
				break;
			}
			case 9:
			{
				LoadAll(pipes, cs);
				break;
			}
			case 0:
			{
				return 0;
				break;
			}
		}
	}
	return 0;
}

