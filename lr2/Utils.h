#pragma once
#include<iostream>
#include<unordered_map>
#include "KS.h"
//#include<unordered_set>
using namespace std;
//��������
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
//��������
template <typename T>
void del(unordered_map <int, T>& t,int id)
{
		t.erase(id);
}
//����� ���������
template <typename T>
int FindMaxID(const unordered_map<int, T>& t)
{
	int MaxID = -100;
	for (const auto& i : t)
		if (i.second.set_id() > MaxID)
			MaxID = i.second.set_id();
	return MaxID;
}
//template <typename T>
//int GetIDKS(const unordered_map<int, T>& kss,)
//{
//	//unordered_map <int, T>::iterator id;
//	//unordered_map <int, KS> ::iterator id;
//	int i;
//	while ((cin >> i)&&(id == kss.end()))
//	{
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cout << "KS with this ID is not found";
//	}
//	return i;
//}