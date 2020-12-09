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

KS::KS(std::fstream& fin)
{
	fin >> this->id >> this->Name >> this->kol_ceh >> this->kol_ceh_inwork >> this->effect;
}

int KS::get_id() const
{
	int id_znach = id;
	return id_znach;
}