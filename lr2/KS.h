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
public:
	int set_id() const;
	static int MaxID;
	std::string Name;
	int kol_ceh;
	int kol_ceh_inwork;
	double effect;
	void Edit_KS();
	KS();
	KS(std::ifstream& fin);
};

