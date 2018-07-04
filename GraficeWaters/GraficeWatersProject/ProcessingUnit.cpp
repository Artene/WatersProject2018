#include "ProcessingUnit.h"

ProcessingUnit::ProcessingUnit()
{
	this->m_area = 0;
}

void ProcessingUnit::Trim( Graph * pInGraph, Graph* pOutGraph, double pointA, double pointB)
{
	double MinimumValue = 0; 
	pInGraph->Get_graphPointsContainer_by_reference();
	double MaximumValue = pInGraph->Get_graphPointsContainer_by_reference().size();
	if (pointA >= MinimumValue && pointA <= MaximumValue && pointB >= MinimumValue && pointB <= MaximumValue && pointA <= pointB)
		for (int i = pointA; i <= pointB; i++)
			pOutGraph->Get_graphPointsContainer_by_reference().push_back(std::make_pair(pInGraph->Get_graphPointsContainer_by_reference()[i].first, pInGraph->Get_graphPointsContainer_by_reference()[i].second));
			
}

void ProcessingUnit::Attenuate( Graph * pInGraph, Graph* pOutGraph)
{
	int NormalizationInferiorLimit = 1;
	int NormalizationSuperiorLimit = 10;
	double MaximumValueOfGraph = this->MaximumSignalValueOfGraph(pInGraph);
	double MinimumValueOfGraph = this->MinimumSignalValueOfGraph(pInGraph);
	for (int i = 0; i < pInGraph->Get_graphPointsContainer_by_reference().size(); i++) {
		std::pair<double,double> aux;
		aux.first = i;
		aux.second = 0;
		pOutGraph->Get_graphPointsContainer_by_reference().push_back(aux);
		
		pOutGraph->Get_graphPointsContainer_by_reference()[i].second =
			(NormalizationInferiorLimit +
			(pInGraph->Get_graphPointsContainer_by_reference()[i].second - MinimumValueOfGraph)*
				(NormalizationSuperiorLimit - NormalizationInferiorLimit)) /
				(MaximumValueOfGraph - MinimumValueOfGraph);
		
	}
}

double ProcessingUnit::MaximumSignalValueOfGraph( Graph* pInGraph)

{
	double Maximum = pInGraph->Get_graphPointsContainer_by_reference()[0].second;

	for (int i = 1; i < pInGraph->Get_graphPointsContainer_by_reference().size(); i++) {
		if (Maximum < pInGraph->Get_graphPointsContainer_by_reference()[i].second)
			Maximum = pInGraph->Get_graphPointsContainer_by_reference()[i].second;
	}
	return Maximum;
}

double ProcessingUnit::MinimumSignalValueOfGraph( Graph* pInGraph)
{
	double Minimum = pInGraph->Get_graphPointsContainer_by_reference()[0].second;

	for (int i = 1; i < pInGraph->Get_graphPointsContainer_by_reference().size(); i++) {
		if (Minimum > pInGraph->Get_graphPointsContainer_by_reference()[i].second)
			Minimum = pInGraph->Get_graphPointsContainer_by_reference()[i].second;
	}
	return Minimum;
}

double ProcessingUnit::CalculateArea(Graph * pInGraph)
{
	double FirstBase,SecondBase,Height;
	double SumOfTrapezoidAreas = 0;
	for (int i = 0; i < pInGraph->Get_graphPointsContainer_by_reference().size()-1; i++)
	{
		
		FirstBase = pInGraph->Get_graphPointsContainer_by_reference()[i].second;
		SecondBase = pInGraph->Get_graphPointsContainer_by_reference()[i + 1].second;
		Height = pInGraph->Get_graphPointsContainer_by_reference()[i + 1].first- pInGraph->Get_graphPointsContainer_by_reference()[i].first;
		
		SumOfTrapezoidAreas += (FirstBase + SecondBase)*Height / 2;

	}
	return SumOfTrapezoidAreas;
}

void ProcessingUnit::WriteToFile(Graph* pInGraph,std::string nameOfFile)
{
	std::ofstream fout(nameOfFile);
	for (int i= 0; i < pInGraph->Get_graphPointsContainer_by_reference().size(); i++) {
		fout << pInGraph->Get_graphPointsContainer_by_reference()[i].first << " "<<pInGraph->Get_graphPointsContainer_by_reference()[i].second << std::endl;
	}
	fout.close();
}

ProcessingUnit::~ProcessingUnit()
{
}
