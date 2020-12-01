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
public:
	int set_id() const;
	int set_dlina() const;
	int set_diameter() const;
	double l;
	double d;
	bool remont;
    void Edit_pipe();
	Truba();
	Truba(std::fstream& fin);

	static int MaxID;

};

