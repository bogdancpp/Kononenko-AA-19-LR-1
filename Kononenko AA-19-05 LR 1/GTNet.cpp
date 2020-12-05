#include "GTNet.h"
#include <iostream>

void GTNet::FillingIncidentMatrix()
{
	std::vector<int> allnodes;// мб создать просто пары интов
	std::vector<int> nodes;
	for (auto i : GTNet::InOutPipes)
	{
		allnodes.push_back(i.second.first);
		allnodes.push_back(i.second.second);
	}
	int add = 1;
	for (int i : allnodes)
	{
		add = 1;
		for (int j : nodes)
		{
			if (i != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			nodes.push_back(i);
	}
	for (int i : nodes)
		std::cout << "add nodes - " << i << std::endl;
	
	int size = nodes.size();
	GTNet::matrix = new int* [size];
	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (size_t j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
	int in;
	int out;
	int indexIn = 0;
	int indexOut = 0;
	// попробовать до минус одного
	//std::vector<int>  p;
	//for (int i : allnodes)
	//{
	//	indexIn = 0;
	//	indexOut = 0;
	//	for (int j : nodes)
	//	{
	//		if (i != j)
	//		{
	//			++indexIn;
	//		}
	//		if ((i+1) != j)
	//		{
	//			++indexOut;
	//		}
	//		GTNet::matrix[indexIn][indexOut] = 1;
	//		GTNet::matrix[indexOut][indexIn] = -1;
	//	}
	//}

	//for (size_t i = 0; i < allnodes.size(); i++)
	//{
	//	indexIn = 0;
	//	indexOut = 0;
	//	for (int j : nodes)
	//	{
	//		if ((i % 2) == 0)
	//		{
	//			if (allnodes[i] == j)
	//				indexIn = ;
	//		}
	//		else
	//		{
	//			if (allnodes[i] != j)
	//				++indexOut;
	//		}
	//	}
	//	GTNet::matrix[indexIn][indexOut] = 1;
	//	GTNet::matrix[indexOut][indexIn] = -1;
	//}
	for (auto i : InOutPipes)
	{
		std::cout << " 1 connect - " << i.second.first << std::endl;
		std::cout << " 2 connect - " << i.second.second << std::endl;
	}

	std::pair<int, int> inout;
	for (auto i : InOutPipes)
	{
		for (size_t j = 0; j < nodes.size(); j++)
		{
			std::cout << "CHECK WORK: " << i.second.first << " - " << nodes[j] << std::endl;
			std::cout << "2CHECK WORK: " << i.second.second << " - " << nodes[j] << std::endl;
			if (i.second.first == nodes[j])
				inout.first = j;
			if (i.second.second == nodes[j])
				inout.second = j;
		}
		std::cout << " 1 result: " << inout.first << std::endl;
		std::cout << " 2 result: " << inout.second << std::endl;
		matrix[inout.first][inout.second] = 1;
		matrix[inout.second][inout.first] = -1;
	}

	//for (size_t i = 0; i < allnodes.size(); i++)
	//{
	//	for (size_t j = 0; j < nodes.size(); j++)
	//	{
	//		if ((i % 2) == 0)
	//		{
	//			if (allnodes[i] == nodes[j])
	//				indexIn = j;//0
	//		}
	//		else
	//		{
	//			if (allnodes[i] == nodes[j])
	//				indexOut = j;//null
	//		}
	//	}
	//	GTNet::matrix[indexIn][indexOut] = 1;
	//	GTNet::matrix[indexOut][indexIn] = -1;
	//}
	//for (auto i : GTNet::InOutPipes)
	//{
	//	in = i.second.first;
	//	out = i.second.second;
	//	indexIn = 0;
	//	indexOut = 0;
	//	for (auto j : nodes)
	//	{
	//		if (in != j)
	//		{
	//			++indexIn;
	//		}
	//		if (out != j)
	//		{
	//			++indexOut;
	//		}
	//		GTNet::matrix[indexIn][indexOut] = 1;
	//		GTNet::matrix[indexOut][indexIn] = -1;
	//	}
	//}
	// просто чистим диагональ
	std::cout << "\nMatrix state\n\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << GTNet::matrix[i][j] << "\t";
		}
		std::cout << std::endl << std::endl;
	}
}
