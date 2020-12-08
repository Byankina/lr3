#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include<iterator>
#include "Truba.h"
#include "Utils.h"
#include "KS.h"
using namespace std;

template<typename T>
using Filter = bool(*)(const Truba&  t, T param);
template<typename T>
using FilterKS = bool(*)(const KS&  t, T param);

bool CheckByDiametr(const  Truba&  t, double param)
{
	return (t.get_diameter()) > param;
}
bool CheckByRemont(const Truba& t,bool param)
{
	return t.remont == param;
}
bool CheckByIDIN(const Truba& t, int param)
{
	return t.idin == param;
}
bool CheckByIDOUT(const Truba& t, int param)
{
	return t.idout == param;
}
bool CheckByName(const KS& k, string param)
{
	return k.Name == param;
}
bool CheckByProcent(const KS& k, double param)
{
	double q;
	q =100*(k.kol_ceh - k.kol_ceh_inwork) / k.kol_ceh ;
	return (q) > param;
}
template<typename T>
vector<int> FindPipeByFilter( const unordered_map<int,Truba>& pipe, Filter<T> f, T param)
{
	vector  <int> res;
	res.reserve(pipe.size());
	for (const auto& p : pipe)
	{
		if (f(p.second, param))
			res.push_back(p.first);
	}
	return res;
}

template<typename T>
vector <int> FindKSByFilter(const unordered_map<int,KS>& kss, FilterKS<T> f, T param)
{
	vector<int>resks;
	resks.reserve(kss.size());
	for (const auto& t : kss)
	{
		if (f(t.second, param))
			resks.push_back(t.first);
	}
	return resks;
}

void delPipe(unordered_map <int, Truba>& pipe)
{
	unordered_map <int, Truba> ::iterator nom;
	cout << endl << "ID Pipe to delite: " << endl;
	int id = GetCorrectNumber(Truba::MaxID);
	nom = pipe.find(id);
	if (nom == pipe.end())
		cout << "Truba with this ID is not found";
	else
		del(pipe, id);
}

void delks(unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe, unordered_set <int> ver)
{
	unordered_map <int, KS> ::iterator nom;
	cout << endl << "ID KS to delite: " << endl;
	int id = GetCorrectNumber(KS::MaxID);
	nom = kss.find(id);
	if (nom == kss.end())
		cout << "KS with this ID is not found";
	else
		del(kss, id);
	for (int& i : FindPipeByFilter<int>(pipe, CheckByIDIN, id))
	{
		pipe.erase(i);
	}
	for (int& i : FindPipeByFilter<int>(pipe, CheckByIDOUT, id))
	{
		pipe.erase(i);
	}
	ver.erase(id);
}

int GetIDKS(const unordered_map<int, KS>& kss)
{
	unordered_map <int, KS> ::iterator id;
	int i;
	while ((cin >> i).fail() || (kss.find(i) == kss.end()))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "KS with this ID is not found. Return: ";
	}
	return i;
}

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

bool dfspr(int v,unordered_map<int,vector<id_in_pipe>>& g, unordered_map<int,char> cl, unordered_map<int,int> p, int& cycle_st, vector<int>& ans) {
	cl[v] = 1;
	vector<id_in_pipe> arr;
	arr = g[v];

	for (auto& i:arr) {
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
	for (int j = 0;j < ans.size();j++)
		if (ans[j] == v)
			k = k + 1;	
	if (k==0) ans.push_back(v);
	return false;

}

void topologicalSort(unordered_map<int, vector<id_in_pipe>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
	ans.clear();
	unordered_map<int,char> cl;
	unordered_map<int,int> p;
	for (auto& i:g)
	{
		cl[i.first] = false;
		p[i.first] = -1;
	}
	int cycle_st=-1;
	for (auto& el : cl)
	{
		if (dfspr(el.first, g, cl, p, cycle_st,ans))
			break;
	}

	if (cycle_st == -1)
		reverse(ans.begin(), ans.end());
	else cout << "Cycle";
}

void PrintMenu() {
	cout << endl;
	cout << "1. Add pipe" << endl
	<< "2. Add KS" << endl
	<< "3. Show the pipe" << endl
	<< "4. Show the KS" << endl
	<< "5. Change the pipe(remont/ne remont)" << endl
	<< "6. Change the KS" << endl
	<< "7. Save the data" << endl
	<< "8. Load from file the data" << endl
	<< "9. Delete pipe" << endl
	<< "10. Delete KS" << endl
	<< "11. Find pipe by diametr" << endl
	<< "12. Find pipe in work" << endl
	<< "13. Find KS by name" << endl
	<< "14. Find KS by % kol ceh not in work" << endl
	<< "15. Edit pipe" << endl
	<< "16. Create Graf"<<endl
	<< "17. Topologicheskaya sortirovka" << endl
	<< "0. Exit" << endl;
}

int main()
{
	unordered_map<int, Truba> pipe;
	unordered_map<int, KS>kss;
	unordered_set <int> ver;
	unordered_map<int, vector<id_in_pipe>> graph;

	int i;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		i = GetCorrectNumber(18);
		switch (i)
		{
		case 1:
		{
			pipe.insert(pair<int, Truba>(Truba::MaxID,Truba()));
			break;
		}
		case 2:
		{	
			kss.insert(pair<int, KS>(KS::MaxID, KS()));
			break;
		}
		case 3:
		{	
			if (pipe.size() != 0)
			for (auto it = pipe.begin(); it != pipe.end(); ++it)
			{
				cout << it->second << endl;
	
			}
			else
				cout << "Have not pipes";
			break;
		}
		case 4:
		{
			if (kss.size() != 0)
			for (auto it = kss.begin(); it != kss.end(); ++it)
			{
				cout  << (*it).second << endl;
			}
			else
				cout << "Have not KSs";
			break;
		}
		case 5:
		{unordered_map <int, Truba> ::iterator nom;
		cout << "ID Pipe to change: ";
		int id = GetCorrectNumber(Truba::MaxID);
		nom = pipe.find(id);
		if (nom == pipe.end())
			cout << "Truba with this ID is not found";
		else
			nom->second.Edit_pipe();
			break;
		}
		case 6:
		{
			unordered_map <int, KS> ::iterator nom;
			cout << "ID Pipe to change: ";
			int id = GetCorrectNumber(KS::MaxID);
			nom = kss.find(id);
			if (nom == kss.end())
				cout << "KS with this ID is not found";
			else
				nom->second.Edit_KS();
			break;
		}
		case 7:
		{	if (pipe.size()!=0 || kss.size()!=0)
			SaveData(pipe,kss);
			break;
		}
		case 8:
		{	LoadData(pipe, kss);
			Truba::MaxID = FindMaxID(pipe);
			KS::MaxID = FindMaxID(kss);
			graph.clear();
			if (pipe.size() != 0)
				for (auto it = pipe.begin(); it != pipe.end(); ++it)
				{
					if (it->second.get_idin() != 0)
					{
						int id = it->second.get_id();
						int idin = it->second.get_idin();
						int idout = it->second.get_idout();
						ver.insert(it->second.get_idin());
						ver.insert(it->second.get_idout());
						graph[idout].push_back(createStruct(id, idin));
					}
				}
			cout << "KSs ID in Graf: ";
			copy(ver.begin(), ver.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			PrintGraph(graph);
			break;
		}
		case 9:
		{ delPipe(pipe);
		break;
		}
		case 10:
		{delks(kss,pipe,ver);
		break;
		}
		case 11:
		{	double param;
			cout << "Filter diametr > ";
			cin >> param;
			if (pipe.size() != 0)
			{for (int& i : FindPipeByFilter<double>(pipe, CheckByDiametr, param))
				cout << pipe[i]<<endl;
			}
			else
			{
				cout << "Have not pipes"<<endl;
			}
			break;
		}
		case 12:
		{
			if (pipe.size() != 0)
			{
				for (int& i : FindPipeByFilter<bool>(pipe, CheckByRemont, false))
					cout << pipe[i] << endl;
			}
			else
			{
				cout << "Have not pipes"<<endl;
			};
		break;
		}
		case 13:
		{
			string name;
			cout << "Filter Name:  ";
			cin >> name;
			if (kss.size() != 0)
			{
				for (int& i : FindKSByFilter<string>(kss, CheckByName, name))
					cout << kss[i] << endl;
			}
			else
				cout << "Have not KSs"<<endl;
			break;
			}
		case 14:
		{	double param;
			cout << "Filter % not in work > ";
			param = GetCorrectNumber(100.0);
			if (kss.size() != 0)
			{
				for (int& i : FindKSByFilter<double>(kss, CheckByProcent, param))
					cout << kss[i] << endl;
			}
			else
				cout << "Have not KSs" << endl;
		break;
		}
		case 15:
		{
				double d;
		cout << "Edit pipe d>";
		d= GetCorrectNumber(2000.0);
		for (int& i : FindPipeByFilter<double>(pipe, CheckByDiametr, d))
		{
			pipe[i].Edit_pipe();
		}
		cout << "Done";
			break;
		}
		case 16:
		{
			unordered_map <int, Truba> ::iterator nom;
			int idout;
			int idin;
			cout << "Truba ID, which connected KSs: ";
			int id = GetCorrectNumber(Truba::MaxID);
			nom = pipe.find(id);
			if (nom == pipe.end())
				cout << "Truba with this ID is not found";
			else
			{
				cout << "Truba out (KS ID): ";
				idout = GetIDKS(kss);
				cout << "Truba in (KS ID): ";
				idin = GetIDKS(kss);
				nom->second.Truba_in_out(idout, idin);
				ver.insert(idout);
				ver.insert(idin);
				
				graph[idout].push_back(createStruct(id, idin));
			}
			cout << "KSs ID in Graf: ";
			copy(ver.begin(), ver.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			PrintGraph(graph);

			break;
		}
		case 17:
		{
			unordered_map<int, bool> count;
			vector<int> ans;
			topologicalSort(graph, count, ans);
			for (auto index = ans.begin(); index != ans.end(); index++)
			{
				cout << *index;
				if (index + 1 != ans.end()) cout << " -> ";
			}
			break;
		}
		case 0:
			return 0;
			break;
		}
		cout << endl;
	}
}