#include "KS.h"
#include "Utils.h"
using namespace std;

istream& operator >> (istream& in, KS& new_ks)
{
	cout << "Name: " << endl;
	cin.ignore(10000, '\n');
	getline(cin, new_ks.Name);
	cout << "kol ceh=" << endl;
	new_ks.kol_ceh = GetCorrectNumber(100);
	cout << "kol ceh inwork=" << endl;
	new_ks.kol_ceh_inwork = GetCorrectNumber(new_ks.kol_ceh);
	cout << "effect=" << endl;
	new_ks.effect = GetCorrectNumber(10.0);
	return in;
}

ostream& operator << (ostream& out, const KS& k)
{
	out << "KS" << "    ID: " << k.id 
	<< "    Name: "<< k.Name<< "    in work "<< k.kol_ceh_inwork 
		<< "/"<< k.kol_ceh << "    Effect= "<< k.effect;
	return out;
}

std::fstream& operator<<(std::fstream& fout, const KS& c)
{
	fout << c.id << endl << c.Name << endl << c.kol_ceh << endl << c.kol_ceh_inwork << endl << c.effect;
	return fout;
}

std::fstream& operator>>(std::fstream& fin, KS& k)
{
	fin >> k.id >> k.Name >> k.kol_ceh >> k.kol_ceh_inwork >> k.effect;
	return fin;
}

int KS::MaxID = 0;

void KS::Edit_KS()
{
	cout << "Kol-vo cehov inwork= " << endl;
	this->kol_ceh_inwork = GetCorrectNumber(this->kol_ceh);
}

KS::KS()
{
	this->id = ++MaxID;
	cout << "Name: " << endl;
	cin.ignore(10000, '\n');
	getline(cin, this->Name);
	cout << "kol ceh=" << endl;
	this->kol_ceh = GetCorrectNumber(100);
	cout << "kol ceh inwork=" << endl;
	this->kol_ceh_inwork = GetCorrectNumber(this->kol_ceh);
	cout << "effect=" << endl;
	this->effect = GetCorrectNumber(10.0);
}

KS::KS(std::ifstream& fin)
{
	fin >> this->id >> this->Name >> this->kol_ceh >> this->kol_ceh_inwork >> this->effect;
}

int KS::set_id() const
{
	int id_znach = id;
	return id_znach;
}