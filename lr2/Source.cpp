#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "Truba.h"
#include "Utils.h"
#include"KS.h"
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
	return t.get_remont() == param;
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

void PrintMenu() {
	cout << endl;
	cout << "1. Add pipe" << endl
	<< "2. Add KS" << endl
	<< "3. Show the pipe" << endl
	<< "4. Show the KS" << endl
	<< "5. Change the pipe(remont/ne remont)" << endl
	<< "6. Change the KS" << endl
	<< "7. Save the pipe" << endl
	<< "8. Save the KS" << endl
	<< "9. Load from file the pipe" << endl
	<< "10. Load from file the KS" << endl
	<< "11. Delete pipe" << endl
	<< "12. Delete KS" << endl
	<< "13. Find pipe by diametr" << endl
	<< "14. Find pipe in work" << endl
	<< "15. Find KS by name" << endl
	<< "16. Find KS by % kol ceh not in work" << endl
	<< "17. Edit pipe" << endl
	<< "0. Exit" << endl;
}

void del(unordered_map <int,Truba>& pipe)
{
	unordered_map <int, Truba> ::iterator nom;
	cout <<endl<< "ID Pipe to delite: " << endl;
		int id = GetCorrectNumber(Truba::MaxID);
		nom = pipe.find(id);
		if (nom == pipe.end())
			cout << "Truba with this ID is not found";
		else
			del(pipe,id);
}

void delks(unordered_map <int, KS>& kss)
{
	unordered_map <int, KS> ::iterator nom;
	cout << endl << "ID KS to delite: " << endl;
	int id = GetCorrectNumber(KS::MaxID);
	nom = kss.find(id);
	if (nom == kss.end())
		cout << "KS with this ID is not found";
	else
		del(kss,id);
}

int main()
{
	unordered_map<int, Truba> pipe;
	unordered_map<int, KS>kss;
	int i;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		i = GetCorrectNumber(17);
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
			for (auto it = pipe.begin(); it != pipe.end(); ++it)
			{
				cout << it->second << endl;
	
			}
			if (pipe.size() == 0)
				cout << "Have not pipes";
			break;
		}
		case 4:
		{
			for (auto it = kss.begin(); it != kss.end(); ++it)
			{
				cout  << (*it).second << endl;
			}
			if (kss.size() == 0)
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
		{	
			fstream fout;
			string filename;
			cout << "Filename: ";
			cin >> filename;
			fout.open(filename+".txt", fstream::out);
			if (fout.is_open()) {
				cout << "Obrabotka.....";
				for (auto it = pipe.begin(); it != pipe.end(); ++it)
				{
					fout << it->second << endl;
				}
				fout.close();
				cout << "Pipe saved";
			}
			break;
		}
		case 8:
		{
			fstream fout;
			string filename;
			cout << "Filename: ";
			cin >> filename;
			fout.open(filename+".txt", ios::out);
			if (fout.is_open()) {
				cout << "Obrabotka.....";
				for (auto it = kss.begin(); it != kss.end(); ++it)
				{
					fout<< (*it).second << endl;
				}
				fout.close();
				cout << "KS saved";
			}
			break;
		}
		case 9:
		{		
			fstream fin;
			unordered_map<int, Truba> pipe2;
			string filename;
			cout << "Filename: ";
			cin >> filename;
			fin.open(filename+".txt", fstream::in);
			if (fin.is_open()) {
			while (!fin.eof())
			{
				Truba p(fin);
				pipe2.insert(pair<int, Truba>(p.get_id(), p));
			}
			fin.close();
			pipe = pipe2;
			Truba::MaxID = FindMaxID(pipe);
		}
		break;
		}
		case 10:
		{
			ifstream fin;
			unordered_map<int, KS> kss2;
			string filename;
			cout << "Filename: ";
			cin >> filename;
			fin.open(filename+".txt", ifstream::in);
			if (fin.is_open()) {
				while (!fin.eof())
				{
					KS k(fin);
					kss2.insert(pair<int, KS>(k.get_id(), k));
				}
				fin.close();
				kss = kss2;
				KS::MaxID = FindMaxID(kss);
			}
			break;
		}
		case 11:
		{ del(pipe);
		break;
		}
		case 12:
		{delks(kss);
		break;}
		case 13:
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
		case 14:
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
		case 15:
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
		case 16:
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
		case 17:
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
		case 0:
			return 0;
			break;
		}
		cout << endl;
	}

}