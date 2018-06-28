#include "Generator.h"



Generator::Generator()
{
}

Generator::Generator(int NumberOfGeneratedNumbers,double MinimumLimit, double MaximumLimit,double ThresHoldSize)
{
	this->m_NumberOfGeneratedNumbers = NumberOfGeneratedNumbers;
	this->m_MinimumLimit = MinimumLimit;
	this->m_MaximumLimit = MaximumLimit;
	this->m_ThresHoldSize=ThresHoldSize;
}



double Generator::Randomize(double InferiorLimit, double SuperiorLimit)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(InferiorLimit, SuperiorLimit); // define the range
	return distr(eng);
	
}

double Generator::ThresHold(double &PreviousInferiorLimitOfRandom, double &PreviousSuperiorLimitOfRandom, int ThresHoldSize, double MinimumLimit, double MaximumLimit)
{
	double RandomNumber;
		
		if (PreviousInferiorLimitOfRandom < MinimumLimit)
		{
			PreviousInferiorLimitOfRandom = MinimumLimit;
			PreviousSuperiorLimitOfRandom = MinimumLimit+ThresHoldSize;
			RandomNumber = Randomize(PreviousInferiorLimitOfRandom, PreviousSuperiorLimitOfRandom);
		}
		else if (PreviousSuperiorLimitOfRandom>MaximumLimit)
		{
			PreviousInferiorLimitOfRandom = MaximumLimit-ThresHoldSize;
			PreviousSuperiorLimitOfRandom = MaximumLimit;
			RandomNumber = Randomize(PreviousInferiorLimitOfRandom, PreviousSuperiorLimitOfRandom);
		}
		else
		{
			RandomNumber = Randomize(PreviousInferiorLimitOfRandom, PreviousSuperiorLimitOfRandom);
			PreviousInferiorLimitOfRandom = RandomNumber - ThresHoldSize/2;
			PreviousSuperiorLimitOfRandom = RandomNumber + ThresHoldSize/2;
		}
		return RandomNumber;
}

void Generator::WriteRandomNumberToFile()
{
	double YCoord;
	double InferiorLimit=this->m_MinimumLimit;
	double SuperiorLimit=this->m_MaximumLimit;
	std::ofstream fout("GeneratedNumbers.txt");
	for (int XCoord = 0; XCoord < this->m_NumberOfGeneratedNumbers; XCoord++) {
		YCoord = ThresHold(InferiorLimit,SuperiorLimit,this->m_ThresHoldSize,this->m_MinimumLimit,this->m_MaximumLimit);
		fout << XCoord << " " << YCoord <<std::endl;
	}
	fout.close();
}

Generator::~Generator()
{
}
