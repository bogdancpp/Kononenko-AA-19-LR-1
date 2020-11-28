#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"


class CPipe
{
	private:
		int id;
	
	public:
		static int CountP;
		float diametr, length;
		bool repair = false;
		friend std::ostream& operator << (std::ostream& out, const CPipe& p);  
		friend std::ifstream& operator >> (std::ifstream& in, CPipe& p); 
		friend std::ofstream& operator << (std::ofstream& fout, const CPipe& p);
		friend std::istream& operator >> (std::istream& in, CPipe& p); // почему  должен его объ€вл€ть как дружественный метод
		friend std::string checkRepair(const CPipe& p);

		CPipe();
		int GetId();
};

