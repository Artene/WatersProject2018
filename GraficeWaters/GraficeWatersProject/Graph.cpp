#include "Graph.h"

Graph::Graph()
{
}

void Graph::CreateGraph(std::string nameOfFile)
{
	std::ifstream fin(nameOfFile);
	while (!fin.eof()) {
		std::pair<double, double> aux;
		fin >> aux.first;
		fin >> aux.second;
		this->graphPointsContainer.push_back(aux);
	}
	this->graphPointsContainer.pop_back();
}

void Graph::DisplayOnScreen()
{
	for (int i = 0; i < this->graphPointsContainer.size(); i++)
	{
		std::cout << this->graphPointsContainer[i].first << " " << this->graphPointsContainer[i].second << std::endl;
	}
}

std::vector<std::pair<double, double>>& Graph::Get_graphPointsContainer_by_reference() 
{
	return this->graphPointsContainer;
}

Graph::~Graph()
{
}