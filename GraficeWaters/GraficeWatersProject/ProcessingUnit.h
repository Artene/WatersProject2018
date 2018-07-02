#pragma once
#include "Graph.h"
class ProcessingUnit
{
private:
	Graph instanceOfGeneratedGraph;
public:
	ProcessingUnit();
	ProcessingUnit(Graph inputGraph);
	void Trim(double pointA,double pointB);
	void Attenuate(); // atenuarea grafului
	double MaximumSignalValueOfGraph();//valoarea maxima din vectoru de puncte
	double MinimumSignalValueOfGraph();//valoarea minima din vectoru de puncte
	double CalculateArea();
	void Sum();
	void WriteToFile(std::string nameOfFile);
	~ProcessingUnit();
};

