#define numberOfPointsToGenerate 180
#define startingLowestLimitToGenerate 0
#define startingHighestLimitToGenerate 180
#define startingTreshHoldSize 20
#define firstTrimPoint 10
#define secondTrimPoint 40

#include "Generator.h"
#include "Graph.h"
#include "ProcessingUnit.h"
/*OBS:
   -Librariile care apartin de C++ (cele care au denumirea inclusa intre <>) si sunt incluse in Graph.h,
   iar Graph.h este inclus la randul lui intr-o fila (idiferent de extensia filei, ex:cpp, h),
   ACELE LIBRARI NU SE MAI INCLUD INCA ODATA!

   -Am facut niste comenzi de preprocesare ca sa scapama de "numerele magice", acele comenzi sunt cele scrisa cu #define
   si vor fi INTOTDEAUNA plasate deasupra oricarei linii de cod
*/

void main()
{
	Generator Calin(numberOfPointsToGenerate, startingLowestLimitToGenerate, startingHighestLimitToGenerate, startingTreshHoldSize);
	Calin.WriteRandomNumberToFile();
	Graph Sorin("GeneratedNumbers.txt");
	Sorin.Get_graphPointsContainer_by_reference();
	//Sorin.DisplayOnScreen();
	ProcessingUnit Izabela(Sorin);
	std::cout<<Izabela.CalculateArea();
	//Izabela.Trim(firstTrimPoint, secondTrimPoint);
	Izabela.Attenuate();
	Izabela.Sum();
	//std::cout << std::endl;
	//std::cout << Izabela.MaximumSignalValueOfGraph() << " " << Izabela.MinimumSignalValueOfGraph();


}