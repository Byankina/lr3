#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Truba
{	
	friend std::fstream& operator << (std::fstream& fout, const Truba& t);
	friend std::ostream& operator << (std::ostream& out, const Truba& t);
	friend std::istream& operator >> (std::istream& in, Truba& new_truba);
	friend std::fstream& operator >> (std::fstream& fin, Truba& new_truba);	
	int id;
	double l;
	double d;
	bool remont;
public:
	int get_id() const;
	int get_dlina() const;
	int get_diameter() const;
	bool get_remont() const;
    void Edit_pipe();
	Truba();
	Truba(std::fstream& fin);

	static int MaxID;

};

