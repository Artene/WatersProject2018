#include "Generator.h"



Generator::Generator()
{
}

Generator::Generator(int NumberOfGeneratedNumbers)
{
	this->m_NumberOfGeneratedNumbers = NumberOfGeneratedNumbers;
}


double Generator::Randomize(double InferiorLimit, double SuperiorLimit)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(InferiorLimit, SuperiorLimit); // define the range
	return distr(eng);
	
}

void Generator::TreshHold(double &InferiorLimit, double &SuperiorLimit,int ThresHoldSize)
{
	//Ce e in main vine scris in functia WriteInFile din clasa Generator
	//treshold=10;FirstNumber apartine [5,15] se poate lua si altceva...dar trebuie modificat si la limite
	int FirstNumber = Randomize(5, 15);
	int PreviousInferiorLimit = FirstNumber - ThresHoldSize;
	int PreviousSuperiorLimit = FirstNumber + ThresHoldSize;
	
	//100=NrMaxPuncte
		int RandomNumber = Randomize(PreviousInferiorLimit, PreviousSuperiorLimit);
		if (PreviousInferiorLimit < ThresHoldSize)
		{
			PreviousInferiorLimit = 5;
			PreviousSuperiorLimit = 15;
		}
		else
		{
			PreviousInferiorLimit = RandomNumber - ThresHoldSize;
			PreviousSuperiorLimit = RandomNumber + ThresHoldSize;
		}

}

void Generator::WriteRandomNumberToFile()
{
	int YCoord;
	double InferiorLimit;
	double SuperiorLimit;
	TreshHold(InferiorLimit,SuperiorLimit,5);
	std::ofstream fout("GeneratedNumbers.txt");
	for (int XCoord = 0; XCoord < this->m_NumberOfGeneratedNumbers; XCoord++) {
		YCoord = Randomize(InferiorLimit,SuperiorLimit);
		fout << XCoord << " " << YCoord << std::endl;
	}
	fout.close();
}

Generator::~Generator()
{
}
