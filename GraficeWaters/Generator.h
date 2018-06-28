#pragma once
#include <fstream>
#include <random>
class Generator
{
private:
	int m_NumberOfGeneratedNumbers;

public:
	Generator();
	Generator(int);
	double Randomize(double,double);
	void TreshHold(double&, double&,int);
	void WriteRandomNumberToFile();
	~Generator();
};

