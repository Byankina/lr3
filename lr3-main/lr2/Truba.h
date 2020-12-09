#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Truba
{	
	friend std::fstream& operator << (std::fstream& fout, const Truba& t);
	friend std::ostream& operator << (std::ostream& out, const Truba& t);
	int id;
public:
	int idin;
	int idout;
	int get_id() const;
	int get_idin() const;
	int get_idout() const;
	double get_dlina() const;
	double get_diameter() const;
	bool get_remont() const;
	double l;
	double d;
	bool remont;
    void Edit_pipe();
	Truba();
	Truba(std::fstream& fin);
	void Truba_in_out(int idout, int idin);
	static int MaxID;


};

