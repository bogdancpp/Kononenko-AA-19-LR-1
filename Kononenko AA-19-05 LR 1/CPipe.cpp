#include "CPipe.h"
#include "Utils.h"
#include <iostream>
#include <string>

int CPipe::CountP = 0;

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

CPipe::CPipe()
{
	id = CountP;
	CountP++;
}

int CPipe::GetId()
{
	return id;
}
