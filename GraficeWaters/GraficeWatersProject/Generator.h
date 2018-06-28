#pragma once
#include <fstream>
#include <random>
class Generator
{
private:
	int m_NumberOfGeneratedNumbers;
	double m_MinimumLimit;
	double m_MaximumLimit;
	double m_ThresHoldSize;

public:
	Generator();
	Generator(int,double,double,double);
	double Randomize(double,double);
	double ThresHold(double&, double&,int,double,double);
	void WriteRandomNumberToFile();
	~Generator();
};

