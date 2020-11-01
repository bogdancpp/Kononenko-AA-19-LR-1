#include "CPipe.h"
#include "Utils.h"
#include <iostream>
#include <string>

int CPipe::CountP = 0;

CPipe::CPipe()
{
	id = CountP;
	CountP++;
}

int CPipe::GetId()
{
	return id;
}

void CPipe::SetId(int& id)
{
	this->id = id;
}

std::string checkRepair(const CPipe& p)
{
	return (p.repair) ? "Unworking \n\n" : "Working \n\n";

}

std::ostream& operator << (std::ostream& out, const CPipe& p)
{
	out << "Pipe id: " << p.id << std::endl << "diametr: " << p.diametr << std::endl
		<< "length: " << p.length << std::endl << "pipe condition: " << checkRepair(p);
	return out;
}

//std::ofstream& operator << (std::ofstream& fout, const CPipe& p) // не понимаю в чем проблема
//{
//	fout << p.id << endl << p.diametr << endl
//			<< p.length << endl << p.repair << endl << endl;
//
//	return fout;
//}


