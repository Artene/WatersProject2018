#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <utility>
#include <fstream>
#include <string>

class Graph
{
private:
	std::vector<std::pair<double, double>> graphPointsContainer;

public:
	Graph();
	Graph(std::string nameOfFile);
	void DisplayOnScreen();
	std::vector<std::pair<double, double>>& Get_graphPointsContainer_by_reference();
	~Graph();
};
/* Reminders:
 Graph.cpp are niste observatii care trebuie abordate, nu sterge acest comentariu pana nu sunt rezvate complet
*/