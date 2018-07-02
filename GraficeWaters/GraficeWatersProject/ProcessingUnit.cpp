#include "ProcessingUnit.h"



ProcessingUnit::ProcessingUnit()
{
}

ProcessingUnit::ProcessingUnit(Graph inputGraph)
{
	this->instanceOfGeneratedGraph = inputGraph;
	//de inlocuit cu setGraph()
}

void ProcessingUnit::Trim(double pointA, double pointB)
{
	double MinimumValue = 0;
	double MaximumValue = instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size();
	if(pointA>=MinimumValue && pointA<=MaximumValue && pointB>=MinimumValue && pointB<=MaximumValue && pointA<=pointB)
	for (int i = pointA; i <= pointB; i++)
		std::cout << instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].first << " " << instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].second << "\n";
}

void ProcessingUnit::Attenuate()
{  // (a + (x-A)(b-a))/(B-A)
	int NormalizationInferiorLimit = 1;
	int NormalizationSuperiorLimit = 10;
	double MaximumValueOfGraph = this->MaximumSignalValueOfGraph();
	double MinimumValueOfGraph = this->MinimumSignalValueOfGraph();
	for (int i = 0; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size(); i++) {
		this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second =
			(NormalizationInferiorLimit +
			(this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second - MinimumValueOfGraph)*
				(NormalizationSuperiorLimit - NormalizationInferiorLimit)) /
				(MaximumValueOfGraph - MinimumValueOfGraph);
	}
}

double ProcessingUnit::MaximumSignalValueOfGraph()

{
	double Maximum = this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(0).second;

	for (int i = 1; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size(); i++) {
		if (Maximum < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second)
			Maximum = this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second;
	}
	return Maximum;
}

double ProcessingUnit::MinimumSignalValueOfGraph()
{
	double Minimum = this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(0).second;

	for (int i = 1; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size(); i++) {
		if (Minimum > this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second)
			Minimum = this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().at(i).second;
	}
	return Minimum;
}

double ProcessingUnit::CalculateArea()
{
	double FirstBase,SecondBase,Height;
	double SumOfTrapezoidAreas = 0;
	for (int i = 0; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size()-1; i++)
	{
		
		FirstBase = instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].second;
		SecondBase = instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i + 1].second;
		Height = instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i + 1].first- instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].first;
		
		SumOfTrapezoidAreas += (FirstBase + SecondBase)*Height / 2;

	}
	return SumOfTrapezoidAreas;
}

void ProcessingUnit:: Sum()
{
	std::ofstream fout("ModifiedNumbers.txt");
	for (int i = 0; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size(); i++)
	{
		this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].second += 0;
		fout << i << " " << this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].second << " " << "\n";
	}
	//this->WriteToFile();

}

void ProcessingUnit::WriteToFile(std::string nameOfFile)
{
	std::ofstream fout(nameOfFile);
	for (int i= 0; i < this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference().size(); i++) {
		fout << this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].first << " "<<this->instanceOfGeneratedGraph.Get_graphPointsContainer_by_reference()[i].second << std::endl;
	}
	fout.close();
}

ProcessingUnit::~ProcessingUnit()
{
}
