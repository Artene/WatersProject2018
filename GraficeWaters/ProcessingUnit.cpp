#include "ProcessingUnit.h"



ProcessingUnit::ProcessingUnit()
{
}

ProcessingUnit::ProcessingUnit(Graph Graph, std::string NameOfFile)
{
	this->m_Graph = Graph;
	this->m_NameOfFile = NameOfFile;
}

ProcessingUnit::~ProcessingUnit()
{
}
