#pragma once
#include <fstream>
#include <random>
class Generator
{
private:
	int numberOfGeneratedPoints;
	double lowestLimitToGenerate;
	double highestLimitToGenerate;
	double thresHoldLimitAtNumberGeneration;

public:
	Generator();
	Generator(int inputNumberOfGeneratedPoints, double inputLowestLimitToGenerate, double inputHighestLimitToGenerate, double inputThresHoldLimitAtNumberGeneration);
	double Randomize(double inferiorLimit, double superiorLimit);
	double ThresHold(double &previousInferiorLimitOfRandom, double &previousSuperiorLimitOfRandom, int inputThresHoldLimit, double inputLowestLimit, double inputHighestLimit);
	void WriteRandomNumberToFile();
	~Generator();
};

