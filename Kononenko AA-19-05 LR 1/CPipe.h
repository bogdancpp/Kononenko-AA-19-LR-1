#pragma once
#include <iostream>
#include <string>
#include "Utils.h"


class CPipe
{
	private:
		int id;
		friend std::ostream& operator << (std::ostream& out, const CPipe& p);
		friend std::string checkRepair(const CPipe& p);
		//friend std::ofstream& operator << (std::ofstream& fout, const CPipe& p) не понимаю в чем проблема
	
	public:
		static int CountP;
		float diametr, length;
		bool repair = false;
	
		CPipe();
		int GetId();
		void SetId(int& id);
};

