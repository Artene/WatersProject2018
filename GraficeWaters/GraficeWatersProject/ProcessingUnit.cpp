#include "ProcessingUnit.h"



ProcessingUnit::ProcessingUnit()
{
}

ProcessingUnit::ProcessingUnit(Graph Graph, std::string NameOfFile)
{
	this->m_Graph = Graph;
	this->m_NameOfFile = NameOfFile;
}

void ProcessingUnit:: Sum()
{
	std::vector<std::pair<double,double>> aux;
	for (int i = 0; i < this->m_Graph.Getm_Points().size(); i++)
	{
	
		std::pair<double, double> aux2;
		aux2.first = i;
		aux2.second= this->m_Graph.Getm_Points().at(i).second + 100;
		aux.push_back(aux2);
	}
	this->WriteToFile();

}

void ProcessingUnit::WriteToFile()
{
	std::ofstream fout(this->m_NameOfFile);
	for (int i= 0; i < this->m_Graph.Getm_Points().size(); i++) {
		fout << this->m_Graph.Getm_Points().at(i).first << " "<<this->m_Graph.Getm_Points().at(i).second << std::endl;
	}
	fout.close();
}

ProcessingUnit::~ProcessingUnit()
{
}
