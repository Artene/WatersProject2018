#include "Graph.h"


Graph::Graph()
{
}

Graph::Graph(std::string nameOfFile)
{
	std::ifstream fin(nameOfFile);
	while (!fin.eof()) {
		std::pair<double,double> aux;
		fin >> aux.first;
		fin >> aux.second;
		this->graphPointsContainer.push_back(aux);
	}
	this->graphPointsContainer.pop_back();
	/* TO DO:
	=> this->graphPointsContainer.pop_back() arata foarte taranesc, daca avem timp si chef in viitor,
	sa modificam astfel incat sa nu mai avem nevoie de formularea asta, dar sa functioneze la fel
	*/
}

void Graph::DisplayOnScreen()
{
	for (int i = 0; i < this->graphPointsContainer.size(); i++)
	{
		std::cout << this->graphPointsContainer[i].first << " " << this->graphPointsContainer[i].second << std::endl;
		/*
		Hai sa nu lucram ca si in java, please! Totusi, am pastra varianta veche aici:
		-std::cout << this->m_Points.at(i).first << " " << this->m_Points.at(i).second << std::endl;
		*/
	}
}

std::vector<std::pair<double, double>>& Graph::Get_graphPointsContainer_by_reference()
{
	return this->graphPointsContainer;
}

Graph::~Graph()
{
}