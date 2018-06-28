#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(std::string NameOfFile)
{
	std::ifstream fin(NameOfFile);
	while (!fin.eof()) {
		std::pair<double, double> aux;
		fin >> aux.first;
		fin >> aux.second;
		m_Points.push_back(aux);
	}
}

void Graph::DisplayOnScreen()
{
	for (int i = 0; i < m_Points.size(); i++)
	{
		std::cout << m_Points.at(i).first << " " << m_Points.at(i).second << std::endl;
	}
}

Graph::~Graph()
{
}