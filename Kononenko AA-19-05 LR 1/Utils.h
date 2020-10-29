#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
T CheckNum(T less, T more, string s)
{
	T num;
	while ((cin >> num).fail() || num < less || num > more)
	{
		cout << s;
		cin.clear();
		cin.ignore(100, '\n');
	}
	return num;
}

