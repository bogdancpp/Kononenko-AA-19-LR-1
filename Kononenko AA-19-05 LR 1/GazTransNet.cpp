#include "GazTransNet.h"

using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2

//int capacity[100][100], // Матрица пропускных способнотей
int n;
vector<vector<int>> flow;  // Матрица потока
vector<int> color;  // Матрица потока
vector<int> pred;  // Матрица потока
vector<int> q;  // Матрица потока

//flow[100][100],
//color[100],      // Цвета для вершин
//pred[100];       // Массив пути
int head, tail;  // Начало, Конец
//int q[102];      // Очередь, хранящ

//Сравнение двух целых значений
int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}
//Добавить в очередь(мы ступили на вершину)
void enque(int x)
{
	q[tail] = x;     // записать х в хвост
	tail++;          // хвостом становиться следующий элемент
	color[x] = GREY; // Цвет серый (из алгоритма поиска)
}
//Убрать из очереди(Вершина чёрная, на неё не ходить)
int deq()
{
	int x = q[head];  // Записать в х значение головы
	head++;           // Соответственно номер начала очереди увеличивается
	color[x] = BLACK; // Вершина х - отмечается как прочитанная
	return x;         // Возвращается номер х прочитанной вершины
}
//Поиск в ширину
int GazTransNet::bfs(int start, int end)
{
	int u, v;
	for (u = 0; u < n; u++) // Сначала отмечаем все вершины не пройденными
		color[u] = WHITE;

	head = 0;   // Начало очереди 0
	tail = 0;   // Хвост 0
	enque(start);      // Вступили на первую вершину
	pred[start] = -1;   // Специальная метка для начала пути
	while (head != tail)  // Пока хвост не совпадёт с головой
	{
		u = deq();       // вершина u пройдена
		for (v = 0; v < n; v++) // Смотрим смежные вершины
		{
			// Если не пройдена и не заполнена
			if (color[v] == WHITE && (link[u][v] - flow[u][v]) > 0) {
				enque(v);  // Вступаем на вершину v
				pred[v] = u; // Путь обновляем
			}
		}
	}
	if (color[end] == BLACK) // Если конечная вершина, дошли - возвращаем 0
		return 0;
	else return 1;
}

int GazTransNet::max_flow(int source, int stock)
{
	int i, j, u;
	int maxflow = 0;            // Изначально нулевой
	for (i = 0; i < n; i++)  // Зануляем матрицу потока
	{
		for (j = 0; j < n; j++)
			flow[i][j] = 0;
	}
	while (bfs(source, stock) == 0)             // Пока сеществует путь
	{
		int delta = 10000;
		for (u = n - 1; pred[u] >= 0; u = pred[u]) // Найти минимальный поток в сети
		{
			delta = min(delta, (link[pred[u]][u] - flow[pred[u]][u]));//!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		for (u = n - 1; pred[u] >= 0; u = pred[u]) // По алгоритму Форда-Фалкерсона 
		{
			flow[pred[u]][u] += delta;
			flow[u][pred[u]] -= delta;
		}
		maxflow += delta;                       // Повышаем максимальный поток
	}
	return maxflow;
}

void GazTransNet::view_max_flow(const unordered_map<int, CPipe>& pipes, int& source, int& stock)
{
	vector <pair<int, int>> InOut;
	pair<int, int> io;// заполнение пригодными трубами, узлами
	for (const auto& i : pipes)
	{
		if (!(i.second.begin == -1 || i.second.end == -1 || i.second.begin == -2 || i.second.end == -2))//можно скоратить в 2 раза
		{
			io.first = i.second.begin;
			io.second = i.second.end;
			cout << i.first << " Pipe (" << i.second.length << ")  " << io.first << " -> " << io.second << endl;
			InOut.push_back(io);
		}
	}

	vector<int> nodes;
	int add = 1;// беру неповторяющиеся узлы для матрицы
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

	for (size_t i = 0; i < size; i++) {
		if (nodes[i] == stock)
			stock = i;
		if (nodes[i] == source)
			source = i;
	}

	if (stock > source)
		n = stock + 1;
	else
		n = source + 1;



	//cout << "\n\nn = " << n << endl;

	//n = stock + 1;
	link.resize(size, vector<int>(size));
	flow.resize(size, vector<int>(size));
	color.resize(size);  // Матрица потока
	pred.resize(size);  // Матрица потока
	q.resize(size);

	for (auto& i : link) {
		for (int& j : i) {
			j = 0;// потом 88
		}
	}

	FillingLink(InOut, nodes, pipes);
	cout << endl;
	ViewLink(nodes);
	cout << "Max flow: " << max_flow(source, stock) << endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	cout << "\n\nn = " << n << endl;

}


void GazTransNet::ViewAllReadyPipe(const unordered_map<int, CPipe>& pipes)
{
	bool is_first = true;
	for (const auto& i : pipes)
	{
		if ((i.second.begin == -1) && (i.second.end == -1)) // условия на ремонт не надо, тк равно -2 будет
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
		cout << "\n " << i.first << " Pipe (" << i.second.length << ") " << i.second.begin << " -> " << i.second.end;
	}
	cout << endl;
}

void GazTransNet::EstablishСonnection(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs)
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
	std::pair<int, int> io;//инедксы хранятся
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
		matrix[i][i] = 0; // если вдруг будет петля
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

int GazTransNet::SearchZeroHalfStepNodes(const vector<int>& nodes, deque<int> TopologicNodes)
{
	int size = nodes.size();
	std::cout << "2. Search for the first vertex with a zero half-step of the outcome: ";
	int addNode = 0;
	int index = -1;
	int k = 1;
	vector <int> Included;
	for (size_t i = 0; i < size; i++)
	{
		k = 1;
		Included.clear();
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 1)
				k *= 1;
			else
				k *= 0;
			if (matrix[i][j] < 0)
			{
				Included.push_back(j);// не здесь инкллюд и не тот 
			}
		}
		if (TopologicNodes.empty())
		{
			if (k == 1)
			{
				index = i;
				break;
			}
		}
		else
		{
			int q = 1;
			for (const int& t : TopologicNodes)
			{
				if (i != t)
					q *= 1;
				else
					q *= 0;
			}
			if (k == 1 && q == 1)
			{
				index = i;
				break;
			}
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
			i.second.begin = -2;//на всякий случай
			i.second.end = -2;
		}
	}
}

void BubbleSort(vector<int>& values) {
	for (size_t idx_i = 0; idx_i + 1 < values.size(); ++idx_i) {
		for (size_t idx_j = 0; idx_j + 1 < values.size() - idx_i; ++idx_j) {
			if (values[idx_j + 1] < values[idx_j]) {
				swap(values[idx_j], values[idx_j + 1]);
			}
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
	int add = 1;// беру неповторяющиеся узлы для матрицы
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
	//for (int i : nodes) {
	//	cout << "add node - " << i << endl;
	//}	
	BubbleSort(nodes);
	//cout << "\n\nBubbleSort" << endl << endl;
	//for (int i : nodes) {
	//	cout << "add node - " << i << endl;
	//}




	//int size = nodes.size();
	size = nodes.size();
	matrix = new int* [size];// создание матрицы и заполнение нулями
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

	FillingMatrix(InOut, nodes);// заполняю матрицу соединениями
	ViewMatrix(nodes);

	std::cout << "\nTopological sorting...\n";
	deque<int> TopologicNodes;
	bool loop = true;
	int addNode = 0;
	while ((!ZeroMatrix(size)) && loop)// пока матрица не нулевая и нет цикла
	{
		addNode = 0;
		addNode = SearchZeroHalfStepNodes(nodes, TopologicNodes);// ищем 0-ую степень исхода
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
		matrix[i] = new int[size];
}

GazTransNet::~GazTransNet()
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void GazTransNet::ViewLink(const vector<int>& nodes) {

	int size = nodes.size();
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
			cout << link[count][i] << "\t";
		}
		cout << endl;
		++count;
	}
}

void GazTransNet::FillingLink(const vector<pair<int, int>>& InOut, const vector<int>& nodes, const unordered_map<int, CPipe>& pipes) {

	int size = nodes.size();
	std::pair<int, int> io;//инедксы хранятся
	for (const auto& i : InOut)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i.first == nodes[j])
				io.first = j;
			if (i.second == nodes[j])
				io.second = j;
		}

		for (const auto& j : pipes) {
			if (j.second.begin == i.first && j.second.end == i.second)
			{
				link[io.first][io.second] = j.second.length;
			}
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		link[i][i] = 0; // если вдруг будет петля
	}
}

void GazTransNet::Shortcut(const unordered_map<int, CPipe>& pipes, const int& choice){

	vector <pair<int, int>> InOut;
	pair<int, int> io;// заполнение пригодными трубами, узлами
	for (const auto& i : pipes)
	{
		if (!(i.second.begin == -1 || i.second.end == -1 || i.second.begin == -2 || i.second.end == -2))//можно скоратить в 2 раза
		{
			io.first = i.second.begin;
			io.second = i.second.end;
			cout << i.first << " Pipe (" << i.second.length << ")  " << io.first << " -> " << io.second << endl;
			InOut.push_back(io);
		}
	}

	vector<int> nodes;
	int add = 1;// беру неповторяющиеся узлы для матрицы
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

	//int size = nodes.size();
	int size = nodes.size();

	link.resize(size, vector<int>(size));

	for (auto& i : link) {
		for (int& j : i) {
			j = 0;// потом 88
		}
	}

	FillingLink(InOut, nodes, pipes);
	cout << endl;
	ViewLink(nodes);

	vector<int> distance(size);
	vector<bool> visited(size);
	int count, index, i, u, m = choice;// m - это начальная вершина
	for (i = 0; i < size; i++)
	{
		distance[i] = INT_MAX; visited[i] = false;
	}
	distance[choice] = 0; //[0] это я 0 вершину выбрал

	for (count = 0; count < size - 1; count++)// не уверен что - 1 нужен
	{
		int min = INT_MAX;
		for (i = 0; i < size; i++)
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; index = i;
			}
		u = index;
		visited[u] = true;
		for (i = 0; i < size; i++)
			if (!visited[i] && link[u][i] && distance[u] != INT_MAX &&
				distance[u] + link[u][i] < distance[i])
				distance[i] = distance[u] + link[u][i];
	}
	cout << "All shortcut:\t\n";
	for (i = 0; i < size; i++) if (distance[i] != INT_MAX)
		cout << m << " -> " << i << " = " << distance[i] << endl;
	else cout << m << " -> " << i << " = " << "infinity" << endl;
}






