#include "CCS.h"
#include "Utils.h"

int CCS::CountCs = 0;

CCS::CCS()
{
	id = CountCs;
	CountCs++;
}

int CCS::GetId()
{
	return id;
}

void CCS::SetId(int& id)
{
	this->id = id;
}

std::ostream& operator << (std::ostream& out, const CCS& cs)
{
	out.precision(2);
	out << "\nCS id: " << cs.id << std::endl << "Name: " << cs.name
		<< std::endl << "Quantity of workshops: " << cs.totalShop << std::endl
		<< "Quantity of workshop workers: " << cs.workShop << std::endl
		<< "Efficiency: " << cs.efficiency << std::endl << std::endl;
	return out;
}
