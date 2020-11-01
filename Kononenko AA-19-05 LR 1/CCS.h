#pragma once
#include <iostream>
#include <string>
#include "Utils.h"

class CCS
{

private:
	friend std::ostream& operator << (std::ostream& out, const CCS& cs);

public:
	static int CountCs;
	int id;
	int totalShop, workShop;
	float efficiency;
	std::string name;

	CCS();
	int GetId();
	void SetId(int& id);
};

