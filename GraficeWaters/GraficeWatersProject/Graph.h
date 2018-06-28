#pragma once
//#include<list>
#include<iostream>
#include <exception>
#include <vector>
#include <utility>
#include <fstream>

class Graph
{
private:
	//int m_NumberOfPoints;
	std::vector<std::pair<double, double>> m_Points;

public:
	Graph();
	Graph(std::string);
	//Graph(const Graph&);//copy constructor
	void DisplayOnScreen();
	//void Setm_NumberOfGeneratedNumbers(int);
	//int Getm_NumberOfGeneratedNumbers();
	void Setm_Points(std::vector<std::pair<double, double>>);
	std::vector<std::pair<double, double>> Getm_Points();
	~Graph();
};

