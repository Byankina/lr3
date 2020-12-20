#include "KS.h"
#include "Utils.h"
#include<fstream>
using namespace std;

ostream& operator << (ostream& out, const KS& k)
{
	out << "KS" << "    ID: " << k.id 
	<< "    Name: "<< k.Name<< "    in work "<< k.kol_ceh_inwork 
		<< "/"<< k.kol_ceh << "    Effect= "<< k.effect;
	return out;
}

fstream& operator<<(fstream& fout,const KS& k)
{
	fout << k.id <<endl<< k.Name<<endl << k.kol_ceh <<endl<<k.kol_ceh_inwork<<endl << k.effect;
	return fout;
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

KS::KS(std::fstream& fin)
{
	fin >> this->id >> this->Name >> this->kol_ceh >> this->kol_ceh_inwork >> this->effect;
}

int KS::get_id() const
{
	int id_znach = id;
	return id_znach;
}
int KS::get_kol_ceh() const
{
	int kol_ceh_znach = kol_ceh;
	return kol_ceh_znach;
}
int KS::get_kol_ceh_inwork() const
{
	int kol_ceh_inwork_znach = kol_ceh_inwork;
	return kol_ceh_inwork_znach;
}
double KS::get_effect() const
{
	double effect_znach = effect;
	return effect_znach;
}