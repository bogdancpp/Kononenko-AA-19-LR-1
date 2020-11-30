#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"
#include <ctime>


class CCS
{
	private:
		int id;
	
	public:
		static int CountCs;
		int totalShop, workShop;
		float efficiency;
		std::string name;
		friend std::ostream& operator << (std::ostream& out,  CCS& cs);
		friend std::ifstream& operator >> (std::ifstream& in, CCS& c);
		friend std::istream& operator >> (std::istream& in, CCS& cs);// почему как дружественный метод? в коде его нет
		friend std::ofstream& operator << (std::ofstream& fout,  CCS& c);

		CCS();
		int GetId();
};

