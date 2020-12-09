#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include "KS.h"
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
//сохранение данных в файл
template <typename T,typename K>
void SaveData(const unordered_map<int, T>& t, const unordered_map<int, K>& k)
{
	fstream fout;
	string filename;
	cout << "Filename: ";
	cin >> filename;
	fout.open(filename + ".txt", fstream::out);
	if (fout.is_open()) {
		cout << "Obrabotka.....";
		fout << t.size() << endl << k.size()<<endl;
		for (const auto& it:t)
		{
			fout << it.second << endl;
		}
		for (const auto& itk : k)
		{
			fout << itk.second << endl;
		}
		fout.close();
		cout << "Data saved";
	}
}
// загрузка данных из файла
template <typename T,typename K>
void LoadData(unordered_map<int, T>& t,unordered_map<int, K>& k)
{
	fstream fin;
	int countPipe;
	int countKS;
	unordered_map<int, T> t2;
	unordered_map<int, K> k2;
	string filename;
	cout << "Filename: ";
	cin >> filename;
	fin.open(filename + ".txt", fstream::in);
	if (fin.is_open()) {
		fin >> countPipe >> countKS;
		while(countPipe--)
		{
			T p(fin);
			t2.insert(pair<int, T>(p.get_id(), p));
		}
		while(countKS--)
		{
			K p(fin);
			k2.insert(pair<int, K>(p.get_id(), p));
		}

		fin.close();
		t=t2;
		k = k2;
	}
}
//вывод графа на консоль
template <typename T>
void PrintGraph(T graph)
{
	for (auto& i : graph)
	{
		cout << "KS ID " << i.first << " connected by Truba ID ";
		for (auto j = i.second.begin(); j != i.second.end(); j++)
		{
			cout << j->id << " wiht KS ID " << j->idin;
			if (j + 1 != i.second.end()) cout << ", ";
		}
		cout << endl;
	}
}