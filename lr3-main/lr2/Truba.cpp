#include "Truba.h"
#include"Utils.h"
#include<fstream>

using namespace std;


fstream& operator<<(fstream& fout, const Truba& p)
{
	fout << p.id<< endl << p.d << endl << p.l << endl << p.remont<<endl<<p.idout<<endl<<p.idin;
	return fout;
}

//fstream& operator>>(fstream& fin, Truba& t)
//{
//	fin >> t.id >> t.d >> t.l >> t.remont>>t.idout>>t.idin;
//	return fin;
//}
//istream& operator >> (istream& in, Truba& new_truba)
//{
//	cout << "diametr=" << endl;
//	new_truba.d = GetCorrectNumber(2000.0);
//	cout << "dlina=" << endl;
//	new_truba.l = GetCorrectNumber(1000.0);
//	new_truba.remont = false;
//	new_truba.idout = 0;
//	new_truba.idin = 0;
//	return in;
//}
ostream& operator << (ostream& out, const Truba& t)
{
	out << "TRUBA   ID: " << t.id;
	out << "  Diameter= "<< t.d << "     Dlina= "<< t.l<< (t.remont ? "   V remonte  " : "   Ne v remonte  ");
	return out;
}

void Truba::Edit_pipe()
{
	this->remont = !remont;
}

int Truba::MaxID = 0;

Truba::Truba()
{
	this->id = ++MaxID;
	cout << "diametr=" << endl;
	this->d= GetCorrectNumber(2000.0);
	cout << "dlina=" << endl;
	this->l = GetCorrectNumber(1000.0);
	this->remont = false;
	this->idout = 0;
	this->idin = 0;
}

Truba::Truba(std::fstream& fin)
{
	fin >> this->id >> this->d >> this->l >> this->remont>>this->idout>>this->idin;
}

void Truba::Truba_in_out(int out, int in)
{
	this->idout=out;
	this->idin=in;
}


int Truba::get_id() const
{
	int id_znach = id;
	return id_znach;
}
int Truba::get_diameter() const
{
	double d_znach = d;
	return d_znach;
}
int Truba::get_dlina() const
{
	double l_znach = l;
	return l_znach;
}
int Truba::get_idin() const
{
	int idin_znach = idin;
	return idin_znach;
}
int Truba::get_idout() const
{
	int idout_znach = idout;
	return idout_znach;
}

