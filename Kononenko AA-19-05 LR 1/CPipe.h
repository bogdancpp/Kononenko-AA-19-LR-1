#pragma once
#include <iostream>
#include <string>
#include "Utils.h"


class CPipe
{
private:
	//int id;
	friend std::ostream& operator << (std::ostream& out, const CPipe& p);
	friend std::string checkRepair(const CPipe& p);

public:
	int id;
	static int CountP;
	float diametr, length;
	bool repair = false;

	CPipe();
	int GetId();


};

