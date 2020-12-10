#include "CPipe.h"
#include "Utils.h"
#include <iostream>
#include <string>

int CPipe::CountP = 0;

CPipe::CPipe()
{
	id = CountP++;
}

int CPipe::GetId()
{
	return id;
}

std::string checkRepair( CPipe& p)//rename and class
{
	return (p.repair) ? "Unworking \n\n" : "Working \n\n";

}

std::ostream& operator << (std::ostream& out,  CPipe& p)
{
	out << "Pipe id: " << p.id << std::endl << "diametr: " << p.diametr << std::endl
		<< "length: " << p.length << std::endl << "pipe condition: " << checkRepair(p);
	return out;
}

std::ofstream& operator<<(std::ofstream& fout,  CPipe& p)
{
	fout << p.id << endl << p.diametr << endl
		<< p.length << endl << p.repair << endl << p.begin << endl << p.end << endl;
	return fout;
}

std::istream& operator>> (std::istream& in, CPipe& p)
{
	std::cout << "\nEnter the diameter in millimeters - ";
	p.diametr = CheckNum<double>(0, 10000);
	std::cout << "Enter the length in meters - ";
	p.length = CheckNum<double>(0, 10000);
	std::cout << endl;
	return in;
}

std::ifstream& operator >> (ifstream& in, CPipe& p) //!!!!! 
{
	in >> p.id;
	in >> p.diametr;
	in >> p.length;
	in >> p.repair;
	in >> p.begin;
	in >> p.end;
	return in;
}


