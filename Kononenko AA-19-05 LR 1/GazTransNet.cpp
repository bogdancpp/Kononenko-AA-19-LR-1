#include "GazTransNet.h"

using namespace std;

void GazTransNet::ViewAllReadyPipe(const unordered_map<int, CPipe>& pipes)
{
	bool is_first = true;
	for (const auto& i : pipes)
	{
		if ((i.second.begin == -1) && (i.second.end == -1)) // услови€ на ремонт не надо, тк равно -2 будет
		{
			if (!is_first)
				cout << ", ";
			cout << i.first;
			is_first = false;
		}
	}
	cout << endl;
}

void GazTransNet::CurrentState(const unordered_map<int, CPipe>& pipes)
{
	for (const auto& i : pipes)
	{
		cout << "\n " << i.first << " Pipe " << i.second.begin << " -> " << i.second.end;
	}
	cout << endl;
}

void GazTransNet::Establish—onnection(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs)
{
	int selectPipe = 0;
	do
	{
		cout << "\nWhat kind of pipe to connect?\n\nList id pipes: ";
		ViewAllReadyPipe(pipes);// не сломана и не задействована
		selectPipe = CheckChoiceId(pipes);
		cout << "\nList id CS: ";
		ViewAllId(cs);

		cout << "From ";
		pipes[selectPipe].begin = CheckChoiceId(cs);

		cout << "Where ";
		pipes[selectPipe].end = CheckChoiceId(cs);

		cout << "\nExit?\n1. Yes\n2. No\nSelect - ";
	} while (CheckNum(1, 2) == 2);
	cout << endl;

	CurrentState(pipes);
}

void GazTransNet::ViewMatrix(const vector<int>& nodes)
{
	size = nodes.size();
	cout << endl << "\t";
	for (const auto& s : nodes)
	{
		cout << s << "\t";
	}
	cout << endl;
	int count = 0;

	for (const auto& s : nodes)
	{
		cout << s << "\t";
		for (size_t i = 0; i < size; i++)
		{
			cout << matrix[count][i] << "\t";
		}
		cout << endl;
		++count;
	}
}

void GazTransNet::FillingMatrix(const vector<pair<int, int>>& InOut, const vector<int>& nodes)
{
	int size = nodes.size();
	std::pair<int, int> io;//инедксы хран€тс€
	for (const auto& i : InOut)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i.first == nodes[j])
				io.first = j;
			if (i.second == nodes[j])
				io.second = j;
		}
		matrix[io.first][io.second] = 1;
		matrix[io.second][io.first] = -1;
	}

	for (size_t i = 0; i < size; i++)
	{
		matrix[i][i] = 0; // если вдруг будет петл€
	}
}

bool GazTransNet::ZeroMatrix(const int& size)
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

int GazTransNet::SearchZeroHalfStepNodes(const vector<int>& nodes)
{
	int size = nodes.size();
	std::cout << "2. Search for the first vertex with a zero half-step of the outcome: ";
	int SumRow = 0;
	int addNode = 0;
	int index = -1;
	int k = 1;
	vector <int> Included;
	for (size_t i = 0; i < size; i++)
	{
		k = 1;
		SumRow = 0;
		Included.clear();
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 1)
				k *= 1;
			else
				k *= 0;
			SumRow += matrix[i][j];
			if (matrix[i][j] < 0)
			{
				Included.push_back(j);// не здесь инкллюд и не тот 
			}
		}
		if (k == 1)
		{
			index = i;
			break;
		}
	}

	if ((index == -1))
	{
		return addNode = -100;
	}
	else
	{
		addNode = nodes[index];

		std::cout << addNode << std::endl;
		std::cout << "3. Delete all connection" << std::endl;
		for (size_t j = 0; j < size; j++)
		{
			matrix[index][j] = 0;
		}
		for (int i : Included)// здесь ошибка!!!!!!!!!!
		{
			matrix[i][index] = 0;
		}

		return addNode;
	}
}

void GazTransNet::DeleteGraph(unordered_map<int, CPipe>& pipes)
{
	for (auto& i : pipes)
	{
		if (i.second.repair == 0)
		{
			i.second.begin = -1;
			i.second.end = -1;
		}
		else
		{
			i.second.begin = -2;//на вс€кий случай
			i.second.end = -2;
		}
	}
}


void GazTransNet::TopologicalSorting(const unordered_map<int, CPipe>& pipes)
{
	vector <pair<int, int>> InOut;
	pair<int, int> io;// заполнение пригодными трубами, узлами
	for (const auto& i : pipes)
	{
		if (!(i.second.begin == -1 || i.second.end == -1 || i.second.begin == -2 || i.second.end == -2))//можно скоратить в 2 раза
		{
			io.first = i.second.begin;
			io.second = i.second.end;
			cout << i.first << " Pipe " << io.first << " -> " << io.second << endl;
			InOut.push_back(io);
		}
	}

	vector<int> nodes;
	int add = 1;// беру неповтор€ющиес€ узлы дл€ матрицы
	for (const auto& i : InOut)
	{
		add = 1;
		for (const int& j : nodes)
		{
			if (i.first != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			nodes.push_back(i.first);

		add = 1;
		for (const int& j : nodes)
		{
			if (i.second != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			nodes.push_back(i.second);

	}

	int size = nodes.size();
	matrix = new int* [size];// создание матрицы и заполнение нул€ми
	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new int[size]; // не забыть удалить
		for (size_t j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}

	for (const int& i : nodes)
		cout << "add - " << i << endl;

	FillingMatrix(InOut, nodes);// заполн€ю матрицу соединени€ми
	ViewMatrix(nodes);

	std::cout << "\nTopological sorting...\n";
	deque<int> TopologicNodes;
	bool loop = true;
	int addNode = 0;
	while ((!ZeroMatrix(size)) && loop)// пока матрица не нулева€ и нет цикла
	{
		addNode = 0;
		addNode = SearchZeroHalfStepNodes(nodes);// ищем 0-ую степень исхода
		ViewMatrix(nodes);
		if (addNode == -100)
		{
			std::cout << "\nThe graph contains a loop\n";
			loop = false;
		}
		else
		{
			TopologicNodes.push_back(addNode);
			std::cout << "\n3. If the matrix is nonzero do point 2\n";
		}
	}
	if (loop)
	{
		//TopologicNodes.push_back(LastNode(nodes));
		int k = 1;
		for (const int& i : nodes)
		{
			k = 1;
			for (const int& j : TopologicNodes)
			{
				if (i != j)
					k *= 1;
				else
					k *= 0;
			}
			if (k == 1)
			{
				TopologicNodes.push_back(i);
			}
		}
		std::cout << "Else answer: ";
		std::cout << "Result topological sorting: \n";
		bool is_first = true;
		while (!TopologicNodes.empty())
		{
			if (!is_first)
				cout << " -> ";
			cout  << TopologicNodes.back();
			TopologicNodes.pop_back();
			is_first = false;
		}
		cout << endl << endl;
	}

}

void GazTransNet::DeleteConnect(unordered_map<int, CPipe>& pipes)
{
	cout << "Select the pipe you want to break the connection - ";
	ViewAllId(pipes);
	int choice = CheckChoiceId(pipes);
	pipes[choice].begin = -1;
	pipes[choice].end = -1;
}

GazTransNet::GazTransNet()
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[1];
}

GazTransNet::~GazTransNet()
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}




	//int node;
	//int k;
	//int count;
	//do
	//{
	//	for (size_t i = 0; i < InOut.size(); i++)
	//	{
	//		k = 1;
	//		node = InOut[i].second;
	//		for (auto& j : InOut)
	//		{
	//			if (node != j.first)
	//				k *= 1;
	//			else
	//				k *= 0;
	//		}
	//		if (k == 1)
	//		{
	//			cout << "!!! --- " << node << endl;
	//			nodes.push_back(node);
	//			count = 0;
	//			for (auto& s : InOut)
	//			{
	//				if (node == s.second)
	//					break;
	//				else
	//					++count;
	//			}
	//			InOut.erase(InOut.begin() + count);
	//		}
	//	}
	//} while (!InOut.empty());


	////nodes.
	//deque<int> answer;
	//int add = 1;
	//for (size_t i = nodes.size(); i > 0; --i)
	//{
	//	add = 1;
	//	int last = nodes[i-1];
	//	cout << last << " - last\n";
	//	for (const int& j : answer)
	//	{
	//		if (nodes[i-1] != j)
	//			add *= 1;
	//		else
	//			add *= 0;
	//	}
	//	if (add == 1)
	//		answer.push_back(last);
	//}
	//cout << "--------------" << endl;

	//for (int i : answer)
	//{
	//	cout << "answer - " << i << endl;
	//}
	//cout << "--------------" << endl;
	//while (!answer.empty())
	//{
	//	cout << "!!!!!!!!!!!!! ---  " << answer.back() << endl;
	//	answer.pop_back();
	//}
//}


