#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include "KS.h"
#include "Truba.h"


//создание структуры для вектора - строки словаря (граф)
struct id_in_pipe
{
	int id;
	int idin;
};
id_in_pipe createStruct(int& id, int& idin)
{
	id_in_pipe new_pair;
	new_pair.id = id;
	new_pair.idin = idin;
	return new_pair;
}
//топологическая сортировка и проверка на циклы
bool dfspr(int v, unordered_map<int, vector<id_in_pipe>>& g, unordered_map<int, char> cl, unordered_map<int, int> p, int& cycle_st, vector<int>& ans) {
	cl[v] = 1;
	vector<id_in_pipe> arr;
	arr = g[v];

	for (auto& i : arr) {
		int to = i.idin;
		if (cl[to] == 0)
		{
			p[to] = v;
			if (dfspr(to, g, cl, p, cycle_st, ans))
				return true;
		}
		else if (cl[to] == 1)
		{
			cycle_st = to;
			return true;
		}

	}
	cl[v] = 2;
	int k = 0;
	int n = ans.size();
	for (int j = 0;j < n;j++)
		if (ans[j] == v)
			k = k + 1;
	if (k == 0) ans.push_back(v);
	return false;

}
void topolog_sort(unordered_map<int, vector<id_in_pipe>>& g, vector<int>& ans) {
	ans.clear();
	unordered_map<int, char> cl;
	unordered_map<int, int> p;
	for (auto& i : g)
	{
		cl[i.first] = false;
		p[i.first] = -1;
	}
	int cycle_st = -1;
	for (auto& el : cl)
	{
		if (dfspr(el.first, g, cl, p, cycle_st, ans))
			break;
	}

	if (cycle_st == -1)
		reverse(ans.begin(), ans.end());
	else cout << "Cycle";
}
//создание графа по условиям
unordered_map<int, vector<id_in_pipe>> Graph(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe)
{
	graph.clear();
	if (pipe.size() != 0)
		for (auto it = pipe.begin(); it != pipe.end(); ++it)
		{
			if (it->second.get_idin() != 0 && it->second.get_remont() == false)
			{
				int id = it->second.get_id();
				int idin = it->second.get_idin();
				int idout = it->second.get_idout();
				graph[idout].push_back(createStruct(id, idin));
			}
		}
	return graph;
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


