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
	void CreateGraph(std::string nameOfFile);
	void DisplayOnScreen();
	std::vector<std::pair<double, double>>& Get_graphPointsContainer_by_reference();
	~Graph();
};