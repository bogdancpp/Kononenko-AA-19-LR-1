#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "CPipe.h"
#include "CCS.h"
#include "Utils.h"
#include <unordered_map>
#include <stack>
#include "LR.h"
#include <deque>
#include "GTNet.h"

using namespace std;

template <typename C> 
void ViewAllId(unordered_map<int, C>& pc)
{
	bool is_first = true;
	for (auto& i : pc) 
	{
		if (!is_first)
			cout << ", ";
		cout << i.second.GetId();
		is_first = false;
	}
	cout << endl;
}
template<typename C>
void ViewAllName(unordered_map<int, C>& pc)
{
	bool is_first = true;
	for ( auto& i : pc)
	{
		if (!is_first)
			cout << ", ";
		cout << i.second.name;
		is_first = false;
	}
	cout << endl;
}

template <typename C>
int CheckChoiceId(unordered_map<int, C>& object)
{
	do
	{
		cout << "select - ";
		int choice = CheckNum(0, 100000);
		for (auto& i : object)
		{
			if (choice == i.second.GetId())
				return choice;
			else
				continue;
		}
	} while (true);
}
//Стоит ли в range based for писать const & ? 
// почему вызывается повтор? менял на while
// почему на против while стоят воск знаки менял и туда и туда
template<typename C>
string CheckChoiceName(unordered_map<int,C>& pc)
{
	string choice = "";
	do
	//{
	//while (true)
	{
		cout << "\nChoice Name - ";
		cin.ignore(100, '\n'); // почему вызывается повтор?
		getline(cin, choice);
		for (auto& i : pc) 
		{
			if (choice == i.second.name)
				return choice;
		}
	//}
	} while (true);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void menu()
{
	cout << "\n1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl
		<< "0. Exit mode" << endl << endl << "Selected action - ";

}

template<typename C>
ostream& operator << (ostream& out, unordered_map<int , C>& object)
{
	for ( auto& i : object)
	{
		out << i.second;
	}
	return out;
}
template<typename C>
ofstream& operator << (ofstream& fout, unordered_map<int, C>& object)
{
	for ( auto& i : object)
	{
		fout << i.second;
	}
	return fout;
} 
//библиотеки можно объявлеть только в хэдере а cpp не надо? 
template <typename C>
ifstream& operator >> (ifstream& in, unordered_map<int, C>& object)
{
	
	for (auto& i : object)
	{
		in >> i.second;
	}
	return in;
}

void EditAllPipes(unordered_map<int , CPipe>& pipes)
{
	cout << "0. The pipes is serviceable\n1. Pipes repair\nChoose - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (pair<int const,CPipe>& i : pipes) 
	{
		i.second.repair = choice;
	}
}
unordered_map<int, CPipe> EditSeveralPipes(unordered_map<int,CPipe>& pipes)
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
void EditPipe(unordered_map<int, CPipe>& pipes)
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

unordered_map<int,CCS> EditAllCs(unordered_map<int,CCS>& cs)
{
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (pair<int const,CCS>& i : cs)
	{
		if (choice == 0 && (i.second.totalShop > i.second.workShop)) 
		{
			i.second.workShop += 1;
		}
		else if (i.second.workShop > 0)
		{
			i.second.workShop -= 1;
		}
	}
	return cs;
}
unordered_map<int,CCS> EditSeveralCs(unordered_map<int,CCS>& cs)
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
		for (int i : res)
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
void EditCs(unordered_map<int, CCS>& cs)
{
	cout << "1. Edit all existing ones\n2. Edit several by choice\nSelect - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << endl;
		EditAllCs(cs);
	}
	else
	{
		cout << endl;
		EditSeveralCs(cs);
	}
}

void ViewThat(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs)
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
void SaveAll(unordered_map<int,CPipe>& pipes, unordered_map<int,CCS>& cs)
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
void LoadAll(unordered_map<int,CPipe>& pipes, unordered_map<int,CCS>& cs)
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
		for (size_t i = 0; i < lenpipe; i++)
		{
			fin >> pipes[i];
		}
		for (size_t i = 0; i < lencs; i++)
		{
			fin >> cs[i];
		}
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
void СonByFilter(unordered_map<int,C>& map, bool(*f)(C& p, N param), N param)
{
	for (auto& i : map)
	{
		if (f(i.second, param))
		{
			cout << endl << i.second;
		}
	}
	cout << endl;
}
void SearchByFilterPipes(unordered_map<int,CPipe>& pipes)
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
void SearchByFilterCs(unordered_map<int,CCS>& cs)
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

void DeleteObject(unordered_map <int,CPipe>& pipes, unordered_map <int,CCS>& cs)
{
	cout << "1. Delete pipe\n2. Delete compressor station\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "Enter ID: ";
		ViewAllId(pipes);
		int ch = CheckChoiceId(pipes);
		pipes.erase(ch); 
		cout << endl;
	}
	else
	{
		cout << "Enter ID: ";
		ViewAllId(cs);
		int ch = CheckChoiceId(cs);
		cs.erase(ch);
		cout << endl;
	}
}

void ModeMenu() 
{
	cout << "\n1. CRUD mode\n2. Graph mode\n0. Exit program\nSelect - ";
}
void MenuGraph()
{
	cout << "\n1. Build graph\n2. Perform topological sorting\n0. Exit mode\nSelect - ";
}

void ViewMatrix(int** matrix, int size)
{
	cout << "\nMatrix state\n\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout <<  matrix[i][j] << "\t";
		}
		cout << endl << endl;
	}
}
void SearchUselessNodes(int** matrix, int size,vector<int>& useless)
{
	cout << "\n1. Search for unused nodes: ";
	int t = 1;
	for (size_t i = 0; i < size; i++)
	{
		t = 1;
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
				t *= 1;
			else
				t *= 0;
		}
		if (t == 1)
		{
			useless.push_back(i);
		}
	}
	for (int i : useless)
		cout << i << " ";
	cout << endl;
}
int SearchZeroHalfStepNodes(int** matrix, int size)
{
	cout << "2. Search for the first vertex with a zero half-step of the outcome: ";
	int SumRow = 0;
	int result = 0;
	vector <int>Included;
	for (size_t i = 0; i < size; i++)
	{
		SumRow = 0;
		Included.clear();
		for (size_t j = 0; j < size; j++)
		{
			SumRow += matrix[i][j];
			if (matrix[i][j] < 0)
			{
				Included.push_back(j);// не здесь инкллюд и не тот 
			}
		}
		if (SumRow < 0)
		{
			result = i;
			break;
		}
	}
	if (Included.empty())
	{
		return result = -100;
	}
	cout << result << endl;
	cout << "3. Delete all connection" << endl;
	for (size_t j = 0; j < size; j++)
	{
		matrix[result][j] = 0;
	}
	for (int i : Included)
	{
		matrix[i][result] = 0;
	}
	return result;
}
void ClearDiagonal(int** matrix, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		matrix[i][i] = 0;
	}
}
bool ZeroMatrix(int** matrix, int size)
{
	int t = 1;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
				t *= 1;
			else
				t *= 0;
		}
	}
	return t;
}
int LastNode(int** matrix, int size,vector<int> useless, deque<int>nodes)//можно было по ссылке сделать
{
	int result = -1;
	int k = 1;
	for (size_t i = 0; i < size; i++)
	{
		k = 1;
		for (int j : useless)
		{
			if (i != j)
				k *= 1;
			else
				k *= 0;
		}
		for (int l : nodes)
		{
			if (i != l)
				k *= 1;
			else
				k *= 0;
		}
		if (k == 1)
			result = i;
	}
	return result;
}
void ZeroizeMatrix(int** matrix, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}

	}
}

int main()
{
	system("color 03");
	unordered_map <int, CPipe> pipes;
	unordered_map <int, CCS> cs;
	while (true)
	{
		bool CRUD = true;
		bool graph = true;
		ModeMenu();
		switch (CheckNum(0, 2))
		{
		case 1:
		{
			while (CRUD)
			{
				menu();
				switch (CheckNum(0, 9))
				{
				case 1:
				{
					CPipe p;
					cin >> p;
					pipes.emplace(p.GetId(), p);
					break;
				}
				case 2:
				{
					CCS c;
					cin >> c;
					cs.emplace(c.GetId(), c);
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
					CRUD = false;
					break;
				}
				}

			}
			break;
		}
		case 2:
		{
			GTNet connect;
			int NumberNodes = cs.size();
			int** matrix = new int* [NumberNodes];
			vector<int> useless;
			deque<int> nodes; 
			for (int i = 0; i < NumberNodes; i++) // вынести в отдельный метод
			{
				matrix[i] = new int[NumberNodes];
				for (int j = 0; j < NumberNodes; j++)
				{
					matrix[i][j] = 0;
				}
			}
			while (graph)
			{
				MenuGraph();
				switch (CheckNum(0, 2))
				{
				case 1:
				{
					bool repeat = true;
					while (repeat)
					{
						pair<int, int> InOutPipe;
						cout << "Connecting nodes...\nWhat kind of pipe to connect\nList id pipes: ";
						ViewAllId(pipes);
						bool repeat2 = false;
						int res;
						do
						{
							repeat2 = false;
							res = CheckChoiceId(pipes);
							if (!(pipes[res].begin == -1 && pipes[res].end == -1))
							{
								repeat2 = true;
							}
						} while (repeat2);
						cout << "List id CS: ";
						ViewAllId(cs);
						cout << "From ";
						InOutPipe.first = CheckChoiceId(cs);
						//pipes[res].begin = n.first;
						cout << "Where ";
						InOutPipe.second = CheckChoiceId(cs);
						connect.InOutPipes.emplace(res, InOutPipe);
						connect.FillingIncidentMatrix();
						system("pause");
						//pipes[res].end = n.second;
						matrix[InOutPipe.first][InOutPipe.second] = 1;
						matrix[InOutPipe.second][InOutPipe.first] = -1;
						ViewMatrix(matrix, NumberNodes);

						cout << "\nExit?\n1. Yes\n2. No\nSelect - ";
						if (CheckNum(1, 2) == 1)
						{
							repeat = false;
						}
					}
					break;
				}
				case 2:
				{
					cout << "\nTopological sorting...\n";
					ClearDiagonal(matrix, NumberNodes);
					SearchUselessNodes(matrix, NumberNodes, useless);
					bool loop = true;
					while ((!ZeroMatrix(matrix, NumberNodes)) && loop)
					{
						int res = 0;
						res = SearchZeroHalfStepNodes(matrix, NumberNodes);
						if (res == -100)
						{
							cout << "\nThe graph contains a loop\n";
							loop = false;
						}
						else
						{
							nodes.push_back(res);
							ViewMatrix(matrix, NumberNodes);
							cout << "\n3. If the matrix is nonzero do point 2\n";
						}
					}
					if (loop)
					{
						nodes.push_back(LastNode(matrix, NumberNodes, useless, nodes));
						cout << "Else answer: ";
						cout << "Result topological sorting: \n";
						int i = 1;
						while (!nodes.empty())
						{
							cout << i << " - " << nodes.back() << " " << endl;
							nodes.pop_back();
							++i;
						}
					}
					else
					{
						ZeroizeMatrix(matrix, NumberNodes);
					}
					break;
				}
				case 0:
				{
					graph = false;
					break;
				}
				}
			}
			delete[] matrix;
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