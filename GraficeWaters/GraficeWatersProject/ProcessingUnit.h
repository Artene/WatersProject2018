#pragma once
#include "Graph.h"
#include <string> 
class ProcessingUnit
{
private:
	std::string m_NameOfFile;
	Graph m_Graph;
public:
	ProcessingUnit();
	ProcessingUnit(Graph,std::string);
	//void Trim();
	//void Attenuate();
	//void CalculateArea();
	void Sum();
	void WriteToFile();
	~ProcessingUnit();
};

