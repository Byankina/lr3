#pragma once
#include<iostream>
#include<unordered_map>

using namespace std;
//проверка
template <typename T>
T GetCorrectNumber(T max)
{
	T x;
	while ((cin >> x).fail() || x < 0 || x>max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type number (" << 0 << "-" << max << "):";
	}
	return x;
}
//удаление
template <typename T>
void del(unordered_map <int, T>& t,int id)
{
		t.erase(id);
}
//поиск максимума
template <typename T>
int FindMaxID(const unordered_map<int, T>& t)
{
	int MaxID = -100;
	for (const auto& i : t)
		if (i.second.get_id() > MaxID)
			MaxID = i.second.get_id();
	return MaxID;
}