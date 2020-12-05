#pragma once
#include <unordered_map>

class GTNet
{
public:
	std::unordered_map<int, std::pair<int, int>> InOutPipes;
	int** matrix;
	void FillingIncidentMatrix();
};

