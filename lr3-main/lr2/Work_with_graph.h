#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include "KS.h"
#include "Truba.h"


//�������� ��������� ��� ������� - ������ ������� (����)
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
//�������������� ���������� � �������� �� �����
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
//�������� ����� �� ��������
unordered_map<int, vector<id_in_pipe>> Graph(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe,unordered_set<int>idks)
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
				idks.insert(idin);
				idks.insert(idout);
			}
		}
	return graph;
}

//����� ����� �� �������
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


//����� ������������� ������
void addEdge(int u, int v, int cap,int onEnd[100],int& edgeCount,int nextEdge[100],int firstEdge[100],int capacity[100])
{
	// ������ �����
	onEnd[edgeCount] = v;                   // �� ����� ������� v
	nextEdge[edgeCount] = firstEdge[u];     // ��������� � ������ ������ ��� u
	firstEdge[u] = edgeCount;               // ������ ������ ������ - ����� �����
	capacity[edgeCount++] = cap;            // ������������� ���������� �����������
	// �������� �����
	onEnd[edgeCount] = u;                   // �� ����� ��������� u
	nextEdge[edgeCount] = firstEdge[v];     // ��������� � ������ ������ ��� v
	firstEdge[v] = edgeCount;               // ������ ������ ������ - ����� �����
	capacity[edgeCount++] = 0;				// ������������� ���������� �����������
}
int findFlow(int u, int flow, int destinationVertex,int visited[100],int firstEdge[100],int nextEdge[100],int onEnd[100],int capacity[100]) {
	if (u == destinationVertex) return flow; // ���������� ���������� ������� �� ����
	visited[u] = true;
	for (int edge = firstEdge[u]; edge != 0; edge = nextEdge[edge]) {
		int to = onEnd[edge];
		if (!visited[to] && capacity[edge] > 0) {
			int minResult = findFlow(to, min(flow, capacity[edge]), destinationVertex,visited,firstEdge,nextEdge,onEnd,capacity); // ���� ����� � ���������
			if (minResult > 0) {                    // ���� �����
				capacity[edge] -= minResult;   // � ������ ����� �������� �����
				//capacity[edge ^ 1] += minResult;   // � �������� ����������
				return minResult;
			}
		}
	}
	return 0; // ���� �� ����� ����� �� ���� ������� ������ 0
}
void Potok(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe, unordered_set<int>idks)
{
	size_t n = pipe.size();
	int* capacity=new int [n];
	int* onEnd = new int[n];
	int* nextEdge = new int[n];
	int* firstEdge = new int[n];
	int* visited = new int[n];
	for (size_t i = 0; i < n;i++)
	{
		capacity[i] = 0;
		onEnd[i] = 0;
		nextEdge[i] = 0;
		firstEdge[i] = 0;
		visited[i] = 0;
	}
	int edgeCount = 1;

int numOfVertex = idks.size();
//int numOfEdge = 0;
int sourceVertex, destinationVertex;
cout << "Istok: ";
cin >> sourceVertex;
cout << "Stok: ";
cin >> destinationVertex;   // ��������� �������� � ����
if (destinationVertex == sourceVertex)
	cout << "This KS as start and finish" << endl;
else if ((kss.find(sourceVertex) == kss.end()) || (kss.find(destinationVertex) == kss.end()))
	cout << "Have not this KSs or one of this KSs";
else
{
	for (auto it = pipe.begin(); it != pipe.end(); ++it) {
		int u, v, cap;
		if (it->second.get_idin() != 0)
		{
			u = it->second.get_idout();
			v = it->second.get_idin();
			cap = it->second.get_propusk();
			addEdge(u, v, cap,onEnd,edgeCount,nextEdge,firstEdge,capacity);
		}
	}
	// ���������� ������������� ������
	int maxFlow = 0;
	int iterationResult = 0;
	while ((iterationResult = findFlow(sourceVertex, 1000000, destinationVertex,visited,firstEdge,nextEdge,onEnd,capacity))>0 )
		maxFlow += iterationResult;
	// ������� ������������ �����
	cout << maxFlow << endl;
}
}






struct item { //��������� ��� �������� �������� �����
	int s, c; //��������� � �������� ����
	int v; //"���" ����
};
item CreateItem(int s, int c, int v)
{
	item newitem;
	newitem.s = s;
	newitem.c = c;
	newitem.v = v;
	return newitem;
}



int find(int s, int c,vector<item>map) { //��� ���� �� s � c ��� 0, ���� ���� ���
	for (int i = 0; i < map.size(); i++)
		if (map[i].s == s && map[i].c == c ||
			map[i].s == c && map[i].c == s) return map[i].v;
	return 0;
}

void step(int s, int f, int p,vector<item>map,bool found,int len,int c_len,int waylen,int way[100],int road[100], int n,bool incl[100]) { //����������� ����� ���� ����
	int c; //����� �������, ���� ������ ���
	if (s == f)  //���� ������
	{
		found = true; //��������� ������ "�������"
		len = c_len; //��������� ����� ��� ����
		cout <<"weight="<< len << " ";
		waylen = p; //��������� ����� ���� (���������� �����)
		for (int i = 0; i < waylen; i++) 
			way[i] = road[i]; //��������� ��� ����
		//	cout << way[i] << endl;
		//}
		
		//return true;
	}
	else { //����� ��������� �����
		for (c = 0; c < n; c++) { //��������� ��� �������
			int w = find(s, c,map); //���� �� ���� �� s � c
			if (w && !incl[c] && (len == 0 || c_len + w < len)) { //������ ����� �� ��������?
				road[p] = c; //�������� ����� � ����
				incl[c] = true; //�������� ��� ����������
				c_len += w; //������ � ����� ���� ����
				step(c, f, p + 1,map,found,c_len,c_len,waylen,way,road,n,incl); //������� ���� ��� ������ ��������� �����
				road[p] = 0; //������� �� ��� ����
				incl[c] = false;
				c_len -= w;
			}
		}
	}
}

void Puti(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe, unordered_set<int>idks)
{
	
	vector<item>map;

	//struct item map[m] = { //��� ����, ��������� ����� � ����
	// {0,1,1}, {0,2,1}, {2,3,1}, {1,4,1}, {2,4,1},
	// {4,5,1}, {4,7,1}, {5,6,1}, {6,7,1}
	//};
	const int n = 4; //���������� ������ �����
	int road[n]; //������ ����� ������� "������"
	bool incl[n]; //true, ���� i-�� ������� �������� � ����
	int way[n]; //������� ����� �������� ����
	int waylen; //��� �����
	int start, finish; //��������� � �������� �������
	bool found;
	int len; //��������� "���" ��������
	int c_len; //������� "���" ��������
	//if (destinationVertex == sourceVertex)
	//	cout << "This KS as start and finish" << endl;
	//else if ((kss.find(sourceVertex) == kss.end()) || (kss.find(destinationVertex) == kss.end()))
	//	cout << "Have not this KSs or one of this KSs";
	//else
	{
		for (auto it = pipe.begin(); it != pipe.end(); ++it) {
			int s,c,v;
			if (it->second.get_idin() != 0)
			{
				s = it->second.get_idout();
				c = it->second.get_idin();
				v = it->second.get_dlina();
				map.push_back(CreateItem(s,c,v));
			}
		}
		for (int i = 0; i < n; i++) {
			road[i] = way[i] = 0; incl[i] = false;
		}
		len = c_len = waylen = 0;

		start = 1; //������ ���� - ��������� � 0
		finish = 2; //����� ���� - ��������� � 0
		road[0] = start; //������ ����� ������ � �������
		incl[start] = true; //� �������� ��� ����������
		found = false; //�� ���� ���� �� ������
	
		step(start, finish, 1, map, found, len, c_len, waylen, way, road, n, incl); //���� ������ �����
		
		int a=0;
		for (auto& i : way)
		{
			if (way[i]!=0)
			a =a+1;
		}
		if (a>0) {
			//for (auto& j:way)
			//for (int i=0;i< map.size();i++)
			//{
			//	if ((map[i].s == way[j]) && (map[i].c == way[j + 1]))
			//		len = len +map[i].v;
			//}
			cout << "Way is";
			for (auto&i:way) cout << " " << way[i];
			cout << ", weight is " << len;
		}
		else cout << "Way not found!";
		cout << endl;
	}

}





//void Puti(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe, unordered_set<int>idks)
//{
//	unordered_map<int,unordered_map<int,int>>matr;
//	int n = idks.size();
//	int a = 0;
//	int b = 0;
//	for (int i=0;i< n;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			if ()
//			b = b + 1;
//		}
//		a = a + 1;
//	}
//}