#include "Generator.h"

Generator::Generator()
{
}

Generator::Generator(int inputNumberOfGeneratedPoints, double inputLowestLimitToGenerate, double inputHighestLimitToGenerate, double inputThresHoldLimitAtNumberGeneration)
{
	this->numberOfGeneratedPoints = inputNumberOfGeneratedPoints;
	this->lowestLimitToGenerate = inputLowestLimitToGenerate;
	this->highestLimitToGenerate = inputHighestLimitToGenerate;
	this->thresHoldLimitAtNumberGeneration = inputThresHoldLimitAtNumberGeneration;
}

double Generator::Randomize(double inferiorLimit, double superiorLimit)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(inferiorLimit, superiorLimit);
	return distr(eng);
}

double Generator::ThresHold(double &previousInferiorLimitOfRandom, double &previousSuperiorLimitOfRandom, int inputThresHoldLimit, double inputLowestLimit, double inputHighestLimit)
{
	double randomNumber;
		
	if (previousInferiorLimitOfRandom < inputLowestLimit)
	{
		previousInferiorLimitOfRandom = inputLowestLimit;
		previousSuperiorLimitOfRandom = inputLowestLimit + inputThresHoldLimit;
		randomNumber = Randomize(previousInferiorLimitOfRandom, previousSuperiorLimitOfRandom);
	}
	else {
		if (previousSuperiorLimitOfRandom > inputHighestLimit)
		{
			previousInferiorLimitOfRandom = inputHighestLimit - inputThresHoldLimit;
			previousSuperiorLimitOfRandom = inputHighestLimit;
			randomNumber = Randomize(previousInferiorLimitOfRandom, previousSuperiorLimitOfRandom);
		}
		else
		{
			randomNumber = Randomize(previousInferiorLimitOfRandom, previousSuperiorLimitOfRandom);
			previousInferiorLimitOfRandom = randomNumber - inputThresHoldLimit / 2;
			previousSuperiorLimitOfRandom = randomNumber + inputThresHoldLimit / 2;
		}
	}
	return randomNumber;
}

Graph Generator::GenerateNumbers()
{
	Graph generatorVector;
	std::pair<double, double> aux;
	double InferiorLimit=this->lowestLimitToGenerate;
	double SuperiorLimit=this->highestLimitToGenerate;
	for (int iterator=0; iterator < this->numberOfGeneratedPoints; iterator++) {
		aux.first = iterator;
		aux.second= ThresHold(InferiorLimit, SuperiorLimit, this->thresHoldLimitAtNumberGeneration, this->lowestLimitToGenerate, this->highestLimitToGenerate);
		generatorVector.Get_graphPointsContainer_by_reference().push_back(aux);
		/*generatorVector->Get_graphPointsContainer_by_reference()[iterator].second=ThresHold(InferiorLimit,SuperiorLimit,this->thresHoldLimitAtNumberGeneration,this->lowestLimitToGenerate,this->highestLimitToGenerate);
		  generatorVector->Get_graphPointsContainer_by_reference()[iterator].first = iterator;
		*/
	}
	return generatorVector;
}

Generator::~Generator()
{
}
