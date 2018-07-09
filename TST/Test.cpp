#define numberOfPointsToGenerate 180
#define startingLowestLimitToGenerate 0
#define startingHighestLimitToGenerate 180
#define startingTreshHoldSize 20
#define firstTrimPoint 10
#define secondTrimPoint 40

#include "Generator.h"
#include "Graph.h"
#include "ProcessingUnit.h"

void main()
{
	Generator Calin(numberOfPointsToGenerate, startingLowestLimitToGenerate, startingHighestLimitToGenerate, startingTreshHoldSize);
	Calin.WriteRandomNumberToFile();
	Graph Sorin;
	Sorin.CreateGraph("GeneratedNumbers.txt");
	Graph Trimed;
	Graph Attenuated;
	double Area = 0;
	ProcessingUnit Izabela;
	Area=Izabela.CalculateArea(&Sorin);
	Izabela.Trim(&Sorin,&Trimed,firstTrimPoint, secondTrimPoint);
	Izabela.Attenuate(&Sorin,&Attenuated);
	Izabela.WriteToFile(&Sorin, "GraphInitial.txt");
	Izabela.WriteToFile(&Trimed, "GraphTrimed.txt");
	Izabela.WriteToFile(&Attenuated, "GraphAttenuated.txt");
	std::cout << Area;
}
