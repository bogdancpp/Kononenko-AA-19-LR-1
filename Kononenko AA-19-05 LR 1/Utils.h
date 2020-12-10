#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

template <typename T>
T CheckNum(T less, T more)
{
	T num;
	while ((cin >> num).fail() || num < less || num > more)
	{
		cout << "Please enter a valid value - ";
		cin.clear();
		cin.ignore(100, '\n');
	}
	return num;
}

template <typename C>
void ViewAllId(const unordered_map<int, C>& object)
{
	bool is_first = true;
	for (const auto& i : object)
	{
		if (!is_first)
			cout << ", ";
		cout << i.first;
		is_first = false;
	}
	cout << endl;
}

template <typename C>
int CheckChoiceId(unordered_map<int, C>& object)
{
	do
	{
		cout << "select - ";
		int choice = CheckNum(0, 100000);
		for (auto& i : object)
		{
			if (choice == i.second.GetId())
				return choice;
			else
				continue;
		}
	} while (true);
}

template<typename C>
void ViewAllName(const unordered_map<int, C> object)
{
	bool is_first = true;
	for (const auto& i : object)
	{
		if (!is_first)
			cout << ", ";
		cout << i.second.name;
		is_first = false;
	}
	cout << endl;
}

//—тоит ли в range based for писать const & ? 
// почему вызываетс€ повтор? мен€л на while
// почему на против while сто€т воск знаки мен€л и туда и туда
template<typename C>
string CheckChoiceName(unordered_map<int, C>& pc)
{
	string choice = "";
	do
		//{
		//while (true)
	{
		cout << "\nChoice Name - ";
		cin.ignore(100, '\n'); // почему вызываетс€ повтор?
		getline(cin, choice);
		for (auto& i : pc)
		{
			if (choice == i.second.name)
				return choice;
		}
		//}
	} while (true);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}