#pragma once
#include "Graph.h"
class ProcessingUnit
{
private:
	double m_area;
public:
	ProcessingUnit();
	void Trim(Graph * pInGraph,Graph* pOutGraph,double pointA,double pointB);//sa fie date valide
	void Attenuate( Graph *pInGraph,Graph* pOutGraph, double Percentage);
	double CalculateArea(Graph * pInGraph);
	void WriteToFile(Graph* pInGraph,std::string nameOfFile);
	~ProcessingUnit();
private:
	double MaximumSignalValueOfGraph( Graph* pInGraph);
	double MinimumSignalValueOfGraph( Graph* pInGraph);
};

