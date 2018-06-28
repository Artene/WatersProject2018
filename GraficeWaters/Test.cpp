#include <iostream>
#include "Generator.h"
#include "Graph.h"

int main()
{
	Generator Calin(180);
	Calin.WriteRandomNumberToFile();
	Graph Sorin("GeneratedNumbers.txt");
	Sorin.DisplayOnScreen();
	while (1);
	return 0;
}