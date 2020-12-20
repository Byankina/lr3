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
#include"Work_with_graph.h"
using namespace std;
//фильтры
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
	return t.get_remont() == param;
}
bool CheckByIDIN(const Truba& t, int param)
{
	return t.get_idin() == param;
}
bool CheckByIDOUT(const Truba& t, int param)
{
	return t.get_idout() == param;
}
bool CheckByName(const KS& k, string param)
{
	return k.Name == param;
}
bool CheckByProcent(const KS& k, double param)
{
	double q;
	q =100*(k.get_kol_ceh() - k.get_kol_ceh_inwork()) / k.get_kol_ceh() ;
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
//удаление трубы
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
//удаление КС с подключенными к ней трубами
void delks(unordered_map <int, KS>& kss, unordered_map <int, Truba>& pipe)
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
}
//Получение ID КС
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
//вывод меню
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
		<< "16. Create Graph" << endl
		<< "17. Print Graph" << endl
		<< "18. Topologicheskaya sortirovka" << endl
		<< "19. Maximal potok" << endl
		<< "0. Exit" << endl;
}

//основная программа
int main()
{
	unordered_map<int, Truba> pipe;
	unordered_map<int, KS>kss;
	unordered_map<int, vector<id_in_pipe>> graph;
	unordered_set<int>idks;
	int i;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		i = GetCorrectNumber(20);
		switch (i)
		{
		case 1:
		{
			pipe.insert(pair<int, Truba>(Truba::MaxID, Truba()));
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
					cout << (*it).second << endl;
				}
			else
				cout << "Have not KSs";
			break;
		}
		case 5:
		{
			unordered_map <int, Truba> ::iterator nom;
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
			cout << "ID KS to change: ";
			int id = GetCorrectNumber(KS::MaxID);
			nom = kss.find(id);
			if (nom == kss.end())
				cout << "KS with this ID is not found";
			else
				nom->second.Edit_KS();
			break;
		}
		case 7:
		{	if (pipe.size() != 0 || kss.size() != 0)
			SaveData(pipe, kss);
		break;
		}
		case 8:
		{	LoadData(pipe, kss);

		Truba::MaxID = FindMaxID(pipe);
		KS::MaxID = FindMaxID(kss);
		break;
		}
		case 9:
		{ delPipe(pipe);
		break;
		}
		case 10:
		{delks(kss, pipe);
		break;
		}
		case 11:
		{	double param;
		cout << "Filter diametr > ";
		cin >> param;
		if (pipe.size() != 0)
		{
			for (int& i : FindPipeByFilter<double>(pipe, CheckByDiametr, param))
				cout << pipe[i] << endl;
		}
		else
		{
			cout << "Have not pipes" << endl;
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
				cout << "Have not pipes" << endl;
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
				cout << "Have not KSs" << endl;
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
			bool param;
			cout << "Edit Sostoyznie Truby(0/1): ";
			param = GetCorrectNumber(1);
			for (int& i : FindPipeByFilter<bool>(pipe, CheckByRemont, param))
			{
				cout << pipe[i] << endl;
			}
			cout << "0.Edit all pipe" << endl << "1.Edit some from found" << endl << "Select action: ";
			int vybor = GetCorrectNumber(1);
			if (vybor == 0) {
				for (int& i : FindPipeByFilter<bool>(pipe, CheckByRemont, param))
					pipe[i].Edit_pipe();
				cout << "Done";
			}
			else cout << "Select p.5" << endl;

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
			if (nom == pipe.end() || (nom->second.get_idout() != 0))
				cout << "Truba with this ID is not found or used\n";
			else
			{
				cout << "Truba out (KS ID): ";
				idout = GetIDKS(kss);
				cout << "Truba in (KS ID): ";
				idin = GetIDKS(kss);
				nom->second.Truba_in_out(idout, idin);
			}
			break;
		}
		case 17:
		{
			graph = Graph(graph, kss, pipe, idks);
			PrintGraph(graph);
			break;
		}
		case 18:
		{
			graph = Graph(graph, kss, pipe, idks);
			PrintGraph(graph);
			vector<int> ans;
			topolog_sort(graph, ans);
			for (auto index = ans.begin(); index != ans.end(); index++)
			{
				cout << *index;
				if (index + 1 != ans.end()) cout << " > ";
			}
			break;
		}
		case 19:
		{
			graph = Graph(graph, kss, pipe, idks);
			Potok(graph,kss,pipe,idks);
			break;
		}
		case 20:
		{
			graph = Graph(graph, kss, pipe, idks);
			Puti(graph, kss, pipe, idks);
			break;
		}
		case 0:
			return 0;
			break;
		}
		cout << endl;
	}
}

