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
			cout << i.GetId() << ",  "; // как убрать последнюю запятую
		counter++;
	}
	cout << endl << endl;
}

template <typename C>
int CheckChoiceId(vector<C>& pc)
{
	int choice;
	do
	{
		cout << "\nChoice ID - ";
		cin >> choice;
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

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl 
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl << "0. Exit" << endl << endl;
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

// как это в класс убрать
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
	int id;
	in >> id;
	c.SetId(id);
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
	r.totalShop = CheckNum(0, 1000);

	cout << "Enter the number of workshop workers - ";
	r.workShop = CheckNum(0, r.totalShop);

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
	p.diametr = CheckNum<double>(0, 10000);

	cout << "Enter the length in meters - ";
	p.length = CheckNum<double>(0, 10000);

	cout << endl;
	return p;
} 

void EditAllPipes(vector<CPipe>& pipes)
{
	cout << "0. The pipes is serviceable" << endl << "1. Pipes repair" << endl << "Choose - ";
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
		cout << "Id of the pipe you want to edit: ";// << 0 << " - " << pipes.size() - 1 << endl << "Choose - ";
		ViewAllId(pipes);
		int ch = CheckChoiceId(pipes);
		res.push_back(ch); // проверка введенного числа с существующем id
		cout << "\n1. To select one more pipe\n2. Enough\nSelect - ";
	} while (CheckNum(1, 2) == 1);

	cout << "\n0. The pipe is serviceable" << endl << "1. Pipe repair" << endl << "Choose - ";
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
		if (choice == 0 && (i.totalShop > i.workShop)) // сделать проверку ещё когда вывод всех объектов
		{
			i.workShop += 1;// ternarn
		}
		else if (i.workShop > 0)
		{
			i.workShop -= 1;
		}
		else
		{
			cout << "\nThis action is impossible \n";
		}
		cout << endl;
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
	cout << endl;
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
	//cout << "Id of the compressor station you want to edit: " << 0 << " - " << cs.size()-1 << endl;

	//cout << "Choose - ";
	//int id,u;
	//u = cs.size() - 1;
	//id = CheckNum(0, u);
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
		int OutPipe;
		OutPipe = CheckChoiceId(pipes);
		cout << endl;
		cout << pipes[OutPipe] << endl;
		break;
	}
	case 3:
	{
		cout << "Select id you want to output: ";
		ViewAllId(cs);
		int OutCs;
		OutCs = CheckChoiceId(cs);
		cout << endl;
		cout << cs[OutCs] << endl;
		break;
	}
	}
}

void SaveAll( vector<CPipe>& pipes,  vector<CCS>& cs)// убрал const
{
	ofstream fout;
	string name;
	cout << "Enter name fail: ";
	cin >> name;
	//fout.open("Bogdan_LR1.txt", ios::out);
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
		cs.reserve(lencs);*/

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
//vector<int> SearchByFilter(vector<T>& vect, bool(*f)(CPipe& p, T param), T param)
//{
//	vector<int> res;
//	int indx = 0;
//	for (T& i : vect)
//	{
//		//if (i.repair == (status - 1))
//		if (f(i, param))
//		{
//			res.push_back(indx);
//		}
//		indx++;
//	}
//	return res;
//}
void SearchByFilter(vector<CPipe>& pipes, vector<CCS>& cs)
{
	cout << "1. Search by pipes\n" << "2. Search by compressor stations\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "\n1. By ID\n" << "2. By condition\nSelect action - ";
		if (CheckNum(1, 2) == 1)
		{
			cout << "Enter ID: ";
			ViewAllId(pipes);
			int ch = CheckChoiceId(pipes);
			СonByFilter(pipes, SearchById,ch);
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
			for (CCS& i : cs)
			{
				++counter;
				cout << counter << "." << i.name << " ";
			}
			cout << "\nSelect - ";
			string name;
			cin >> name;
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
	cout << "1. Delete pipe\n" << "2. Delete compressor station\nSelect action - ";
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
	cout << "\t\tKononenko Bogdan AA-19-05\n";
	vector <CPipe> pipes;
	vector <CCS> cs;

	while (true)
	{
		menu();
		cout << "Selected action - ";
		int n;
		n = CheckNum(0, 9);
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
				EditPipe(pipes);
			else
				cout << "First, create a pipe ..." << endl << endl;
			break;
		case 5:
			if (cs.size() != 0) 
				EditCs(cs);
			else
				cout << "First, create a  compressor station ..." << endl << endl;
			break;
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
			SaveAll(pipes, cs);
			break;
		case 9:
			LoadAll(pipes, cs);
			break;
		case 0:
			return 0;
			break;
		}
	}
	return 0;
}

