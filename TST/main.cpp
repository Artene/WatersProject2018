#define numberOfPointsToGenerate 180
#define startingLowestLimitToGenerate 0
#define startingHighestLimitToGenerate 180
#define startingTreshHoldSize 20
#define firstTrimPoint 10
#define secondTrimPoint 40

#include "mainwindow.h"
#include <QApplication>
#include "Generator.h"
#include "Graph.h"
#include "ProcessingUnit.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    
    Graph Trimed;
   

   /* Area=Izabela.CalculateArea(&Sorin);
    Izabela.Trim(&Sorin,&Trimed,firstTrimPoint, secondTrimPoint);
    Izabela.Attenuate(&Sorin,&Attenuated);
    Izabela.WriteToFile(&Sorin, "GraphInitial.txt");
    Izabela.WriteToFile(&Trimed, "GraphTrimed.txt");
   
    std::cout << Area;
	*/
    return a.exec();
}
