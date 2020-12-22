#include "GTNet.h"
#include <iostream>
#include <string>
#include <fstream>

void GTNet::Pip(unordered_map<int, CPipe>& pipes)
{
	for (auto& i : pipes)
	{
		i.second.begin = 546;
		std::cout << "Pipes " << i.first << "in " << i.second.begin << " out " << i.second.end << endl;
	}
}

void GTNet::CreateMatrix()
{
	GTNet::matrix = new int* [size];
	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (size_t j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void GTNet::update()
{
	std::vector<int> Allinteraction;
	Allinteraction.clear();
	GTNet::nodes.clear();

	for (const auto& i : GTNet::InOutPipes)
	{
		if (!(i.second.first == -2 || i.second.second == -2)) // Check Repair
		{
			Allinteraction.push_back(i.second.first);
			Allinteraction.push_back(i.second.second);
		}
	}

	int add = 1;
	for (const int& i : Allinteraction)
	{
		add = 1;
		for (const int& j : GTNet::nodes)
		{
			if (i != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			GTNet::nodes.push_back(i);
	}

	//check

	//std::cout << " ------------------------------------------------ \n" << std::endl;
	//for (int i : GTNet::nodes)
	//	std::cout << "add nodes - " << i << std::endl;
	//std::cout << " ------------------------------------------------ \n" << std::endl;

	GTNet::size = GTNet::nodes.size();
	CreateMatrix();
}

void GTNet::ViewMatrix()
{
	std::cout << "\nMatrix state\n\n";
	for (int i = 0; i < GTNet::size; i++)
	{
		for (int j = 0; j < GTNet::size; j++)
		{
			std::cout << GTNet::matrix[i][j] << "\t";
		}
		std::cout << std::endl << std::endl;
	}
}

void GTNet::FillingIncidentMatrix()
{
	update();

	std::pair<int, int> inOut;
	for (const auto&i : GTNet::InOutPipes)
	{
		for (size_t j = 0; j < nodes.size(); j++)
		{
			if (i.second.first == nodes[j])
				inOut.first = j;
			if (i.second.second == nodes[j])
				inOut.second = j;
		}
		GTNet::matrix[inOut.first][inOut.second] = 1;
		GTNet::matrix[inOut.second][inOut.first] = -1;
	}

	//for (size_t i = 0; i < GTNet::size; i++)
	//{
	//	matrix[i][i] = 0;
	//}

	/*std::cout << "----------------------------------------" << std::endl << std::endl;

	for (const auto& i : GTNet::InOutPipes)
		std::cout << "Pipe " << i.first << " in " << i.second.first << " out " << i.second.second << std::endl << std::endl;

	std::cout << "----------------------------------------" << std::endl << std::endl;*/

	GTNet::ViewMatrix();
}

void GTNet::DeleteMatrix()
{
	// использовать умные указатели
}

bool GTNet::ZeroMatrix()
{
	int t = 1;
	GTNet::size;
	for (size_t i = 0; i < GTNet::size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (GTNet::matrix[i][j] == 0)
				t *= 1;
			else
				t *= 0;
		}
	}
	return t;
}

int GTNet::SearchZeroHalfStepNodes()
{
	std::cout << "2. Search for the first vertex with a zero half-step of the outcome: ";
	int SumRow = 0;
	int addNode = 0;
	int index = 0;
	std::vector <int> Included;
	GTNet::size = GTNet::nodes.size();//в принципе это делать не обязательно
	for (size_t i = 0; i < GTNet::size; i++)
	{
		SumRow = 0;
		Included.clear();
		for (size_t j = 0; j < GTNet::size; j++)
		{
			SumRow += matrix[i][j];
			if (matrix[i][j] < 0)
			{
				Included.push_back(j);// не здесь инкллюд и не тот 
			}
		}
		if (SumRow < 0)
		{
			index = i;
			break;
		}

	}

	if (Included.empty())
	{
		return addNode = -100;
	}

	addNode = nodes[index];

	std::cout << addNode << std::endl;
	std::cout << "3. Delete all connection" << std::endl;
	for (size_t j = 0; j < size; j++)
	{
		matrix[index][j] = 0;
	}
	for (int i : Included)
	{
		matrix[i][index] = 0;
	}

	addNode = nodes[index];

	return addNode;
}

int GTNet::LastNode()//можно было по ссылке сделать
{
	int result = -1;
	int k = 1;
	for (size_t i = 0; i < size; i++)
	{
		k = 1;
		//for (int j : useless)
		//{
		//	if (i != j)
		//		k *= 1;
		//	else
		//		k *= 0;
		//}
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

void GTNet::save()
{
	std::ofstream fout;
	std::string name;
	std::cout << "Enter name file: ";
	std::cin.ignore(1, '\n');// что мы убираем?
	getline(std::cin, name);
	fout.open(name, std::ios::out);
	if (fout.is_open())
	{
		fout << GTNet::InOutPipes.size() << std::endl;
		for (const auto& i : GTNet::InOutPipes)
		{
			fout << i.first << std::endl;
			fout << i.second.first << std::endl;
			fout << i.second.second << std::endl;
		}
		std::cout << "File saved\n\n";
		fout.close();
	}
}

void GTNet::load()
{
	std::ifstream fin;
	std::string name;
	std::cout << "Enter name file: ";
	std::cin.ignore(1, '\n');// что мы убираем?
	getline(std::cin, name);
	fin.open(name, std::ios::in);
	int id, size;
	std::pair<int, int> InOut;
	GTNet::InOutPipes.clear();
	if (fin.is_open())
	{
		fin >> size;
		for (size_t i = 0; i < size; i++)
		{
			fin >> id;
			fin >> InOut.first;
			fin >> InOut.second;
			GTNet::InOutPipes.emplace(id, InOut);
		}
		fin.close();
		std::cout << "Data downloaded\n\n";
	}
}

void GTNet::TopologicalSorting()
{
	FillingIncidentMatrix();
	std::cout << "\nTopological sorting...\n";
	bool loop = true;
	int addNode = 0;
	while ((!ZeroMatrix()) && loop)
	{
		addNode = 0;
		addNode = SearchZeroHalfStepNodes();
		if (addNode == -100)
		{
			std::cout << "\nThe graph contains a loop\n";
			loop = false;
		}
		else
		{
			TopologicNodes.push_back(addNode);
			ViewMatrix();
			std::cout << "\n3. If the matrix is nonzero do point 2\n";
		}
	}
	if (loop)
	{
		TopologicNodes.push_back(LastNode());
		std::cout << "Else answer: ";
		std::cout << "Result topological sorting: \n";
		int i = 1;
		while (!TopologicNodes.empty())
		{
			std::cout << i << " - " << TopologicNodes.back() << " " << std::endl;
			TopologicNodes.pop_back();
			++i;
		}
	}
	else
	{
		CreateMatrix();
	}
}





