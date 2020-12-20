#pragma once
#include <iostream>
#include<string>
#include <fstream>
class KS
{
	friend std::fstream& operator << (std::fstream& fout, const KS& k);
	friend std::ostream& operator << (std::ostream& out, const KS& k);
	int id;
	int kol_ceh;
	int kol_ceh_inwork;
	double effect;
public:
	int get_id() const;
	int get_kol_ceh() const;
	int get_kol_ceh_inwork() const;
	double get_effect() const;
	static int MaxID;
	std::string Name;

	void Edit_KS();
	KS();
	KS(std::fstream& fin);
};

