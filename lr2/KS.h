#pragma once
#include <iostream>
#include<string>
#include <fstream>
class KS
{	friend std::istream& operator >> (std::istream& in, KS& new_ks);
	friend std::ostream& operator << (std::ostream& out, const KS& k);
	friend std::fstream& operator << (std::fstream& out, const KS& k);
	friend std::fstream& operator >> (std::fstream& in, KS& k);
	int id;
	int kol_ceh;
	int kol_ceh_inwork;
	double effect;
public:
	int get_id() const;
	static int MaxID;
	std::string Name;
	int get_kol_ceh() const;
	int get_kol_ceh_inwork() const;
	double get_effect() const;
	void Edit_KS();
	KS();
	KS(std::ifstream& fin);
};

