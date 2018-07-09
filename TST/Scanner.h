#pragma once
#include<qvector.h>
#include "Graph.h"

class Scanner
{
public:
	void Write(Graph pInGraph,std::string nameOfFile);// asta in fisier
	void Read(Graph * pOutGraph, std::string nameOfFile); // citit din fisier + restore
	void ReadGraphics(QVector<double>& xCoord, QVector<double>& yCoord, std::string nameOfFile);
	Scanner();
	~Scanner();
};

