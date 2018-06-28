#include <iostream>
#include "Generator.h"
#include "Graph.h"
#include "ProcessingUnit.h"

int main()
{
	Generator Calin(180,0,180,20);
	Calin.WriteRandomNumberToFile();
	Graph Sorin("GeneratedNumbers.txt");
	Sorin.DisplayOnScreen();
	ProcessingUnit Izabela(Sorin,"ModifiedNumbers.txt");
	Izabela.Sum();
	Izabela.WriteToFile();
	system("pause");
	return 0;
}