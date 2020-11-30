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

std::ostream& operator << (std::ostream& out,  CCS& cs)
{
	out.precision(2);
	out << "\nCS id: " << cs.id << std::endl << "Name: " << cs.name
		<< std::endl << "Quantity of workshops: " << cs.totalShop << std::endl
		<< "Quantity of workshop workers: " << cs.workShop << std::endl
		<< "Efficiency: " << cs.efficiency << std::endl << std::endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& in, CCS& c)
{
	in >> c.id;
	in.ignore();
	std::getline(in, c.name);
	in >> c.totalShop;
	in >> c.workShop;
	in >> c.efficiency;

	return in;
}

std::istream& operator>>(std::istream& in, CCS& cs)
{
	cout << "Enter the name of the compressor station - ";
	cin.ignore();
	getline(cin, cs.name);

	cout << "Enter the number of workshops - ";
	cs.totalShop = CheckNum(0, 1000);
	cout << "Enter the number of workshop workers - ";
	cs.workShop = CheckNum(0, cs.totalShop);

	srand(time(NULL));
	cs.efficiency = 1. / (rand() % 10);
	cout << endl;
	return in;
}

std::ofstream& operator<<(std::ofstream& fout,  CCS& c)
{
	fout.precision(2);
	fout << c.id << endl << c.name << endl << c.totalShop << endl
		<< c.workShop << endl << c.efficiency << endl << endl;
	return fout;
}


