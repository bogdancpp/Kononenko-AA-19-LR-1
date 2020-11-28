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
void ViewAllId(vector<C>& pc) 
{
	bool is_first = true;
	for (C& i : pc) 
	{
		if (!is_first)
			cout << ", ";
		cout << i.GetId();
		is_first = false;
	}
	cout << endl;
}
template<typename C>
void ViewAllName(const vector<C>& pc)
{
	bool is_first = true;
	for (const C& i : pc)
	{
		if (!is_first)
			cout << ", ";
		cout << i.name;
		is_first = false;
	}
	cout << endl;
}

template <typename C>
int CheckChoiceId(vector<C>& pc)
{
	int choice = CheckNum(0, 100000);
	do
	{
		for (C& i : pc)
		{
			if (choice == i.GetId())
				return choice;
		}

	} while (true);
}
//Стоит ли в range based for писать const & ? он сам автоматически это не делает?
// почему вызывается повтор? // еду в поезде без интернета 
// почему на против while стоят воск знаки, надо передлать в просто while?
template<typename C>
string CheckChoiceName(const vector<C>& pc)
{
	string choice = "";
	do
	{
		cout << "\nChoice Name - ";
		cin.ignore(100, '\n'); // почему вызывается повтор?
		getline(cin, choice);
		for (const C& i : pc) 
		{
			if (choice == i.name)
				return choice;
		}
	} while (true);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl
		<< "0. Exit" << endl << endl << "Selected action - ";

}

template<typename C>
ostream& operator << (ostream& out, const vector<C>& object)// non pc
{
	for (const C& i : object)
	{
		out << i;
	}
	return out;
}
template<typename C>
ofstream& operator << (ofstream& fout,const vector<C>& object)
{
	for (const C& c : object)
	{
		fout << c;
	}
	return fout;
} 
//библиотеки можно объявлеть только в хэдере а cpp не надо? //рубрика еду в поезде без интернета
template <typename C>
ifstream& operator >> (ifstream& in, vector<C>& object)
{
	for (C& c : object)
	{
		in >> c;
	}
	return in;
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
		res.push_back(ch); // нужен вектор id, так как у меня пакетное редактирование
		cout << "\n1. To select one more pipe\n2. Enough\nSelect - ";
	} while (CheckNum(1, 2) == 1);

	cout << "\n0. The pipe is serviceable\n1. Pipe repair\nChoose - ";
	int choice = CheckNum(0, 1);
	for (int i : res) 
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
		EditAllPipes(pipes); 
	}

	else
	{
		cout << endl;
		EditSeveralPipes(pipes);
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
			if (cs[i].totalShop > cs[i].workShop)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor stations\nSelect - ";
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
// что мы убираем ? 
void SaveAll(vector<CPipe>& pipes, vector<CCS>& cs)
{
	ofstream fout;
	string name;
	cout << "Enter name file: ";
	cin.ignore(1, '\n');// что мы убираем?
	getline(cin, name);
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
		cout << "File is not open" << endl;
	}
}
// что мы убираем?
void LoadAll(vector<CPipe>& pipes, vector<CCS>& cs)
{
	ifstream fin;
	string name;
	cout << "Enter name file: ";
	cin.ignore(1, '\n');// что мы убираем?
	getline(cin, name);
	fin.open(name, ios::in);
	
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
bool SearchByName(CCS& cs, string name)
{
	return cs.name == name;
}
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
void SearchByFilterPipes(vector<CPipe>& pipes)
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
void SearchByFilterCs(vector<CCS>& cs)
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

void DeleteObject(vector <CPipe>& pipes,vector <CCS>& cs)
{
	cout << "1. Delete pipe\n2. Delete compressor station\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "Enter ID: ";
		ViewAllId(pipes);
		int ch = CheckChoiceId(pipes);
		vector<CPipe>::iterator it1 = pipes.begin() + ch;
		pipes.erase(it1);    // https://ru.cppreference.com/w/cpp/container/vector/erase
		cout << endl;
	}
	else
	{
		cout << "Enter ID: ";
		ViewAllId(cs);
		int ch = CheckChoiceId(cs);
		auto it2 = cs.begin() + ch;
		cs.erase(it2);
		cout << endl;
	}
}

// case 1 и 2 см ?
int main()
{
	system("color 03");
	vector <CPipe> pipes;
	vector <CCS> cs;

	while (true)
	{
		menu();
		switch (CheckNum(0, 9))
		{
			case 1:
			{
				//pipes.push_back(AddPipe()); // Почему так вам не нравится?
				CPipe p;
				cin >> p;
				pipes.push_back(p);
				break;
			}
			case 2:
			{
				//cs.push_back(AddCS()); // вопрос выше
				CCS c;
				cin >> c;
				cs.push_back(c);
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
				cout << "1. Search by pipes\n2. Search by compressor stations\nSelect action - ";
				if (CheckNum(1, 2) == 1)
					SearchByFilterPipes(pipes);
				else
					SearchByFilterCs(cs);
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

