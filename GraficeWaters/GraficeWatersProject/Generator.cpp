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
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(inferiorLimit, superiorLimit); // define the range
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

void Generator::WriteRandomNumberToFile()
{
	double YCoord;
	double InferiorLimit=this->lowestLimitToGenerate;
	double SuperiorLimit=this->highestLimitToGenerate;
	std::ofstream fout("GeneratedNumbers.txt");
	for (int XCoord = 0; XCoord < this->numberOfGeneratedPoints; XCoord++) {
		YCoord = ThresHold(InferiorLimit,SuperiorLimit,this->thresHoldLimitAtNumberGeneration,this->lowestLimitToGenerate,this->highestLimitToGenerate);
		fout << XCoord << " " << YCoord <<std::endl;
	}
	fout.close();
}

Generator::~Generator()
{
}
