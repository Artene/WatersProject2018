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
	std::vector<std::pair<double, double>> m_Points;

public:
	Graph();
	Graph(std::string);
	void DisplayOnScreen();
	~Graph();
};