#include "Scanner.h"


void Scanner::Write(Graph pInGraph, std::string nameOfFile)
{
	int vectSize;
	std::ofstream fout(nameOfFile, std::ios::out | std::ios::binary);
	vectSize = pInGraph.Get_graphPointsContainer_by_reference().size() * sizeof(std::pair<double, double>);
	char *pVectChar = reinterpret_cast<char *>(pInGraph.Get_graphPointsContainer_by_reference().data());
	fout.write(pVectChar, vectSize);
	fout.close();
}

void Scanner::Read(Graph * pOutGraph,  std::string nameOfFile)
{
	std::ifstream fin(nameOfFile, std::ios::in | std::ios::binary);
	int vctSize;
	fin.seekg(0, std::ifstream::end);
	vctSize = fin.tellg();
	pOutGraph->Get_graphPointsContainer_by_reference().clear();
	pOutGraph->Get_graphPointsContainer_by_reference().reserve(vctSize / sizeof(std::pair<double, double>));
	fin.seekg(0, std::ifstream::beg);
	char *pReadBuffer = new char[vctSize];
	fin.read(pReadBuffer, vctSize);
	std::pair<double, double> *pReintVect = reinterpret_cast<std::pair<double, double> *>(pReadBuffer);
	fin.close();
	for (int i = 0; i < pOutGraph->Get_graphPointsContainer_by_reference().capacity(); ++i)
	{
		pOutGraph->Get_graphPointsContainer_by_reference().push_back(pReintVect[i]);
	}
}

void Scanner::ReadGraphics_2(QVector<double>& xCoord, QVector<double>& yCoord, std::string nameOfFile)
{
	xCoord.clear();
	yCoord.clear();
	Graph pOutGraph;
	std::ifstream fin(nameOfFile, std::ios::in | std::ios::binary);
	int vctSize;
	fin.seekg(0, std::ifstream::end);
	vctSize = fin.tellg();
	pOutGraph.Get_graphPointsContainer_by_reference().reserve(vctSize / sizeof(std::pair<double, double>));
	fin.seekg(0, std::ifstream::beg);
	char *pReadBuffer = new char[vctSize];
	fin.read(pReadBuffer, vctSize);
	std::pair<double, double> *pReintVect = reinterpret_cast<std::pair<double, double> *>(pReadBuffer);
	fin.close();
	for (int i = 0; i < pOutGraph.Get_graphPointsContainer_by_reference().capacity(); ++i)
	{
		pOutGraph.Get_graphPointsContainer_by_reference().push_back(pReintVect[i]);
		xCoord.append(pOutGraph.Get_graphPointsContainer_by_reference()[i].first);
		yCoord.append(pOutGraph.Get_graphPointsContainer_by_reference()[i].second);
	}
}
void Scanner::ReadGraphics(QVector<double>& xCoord, QVector<double>& yCoord, Graph *graph)
{
	xCoord.clear();
	yCoord.clear();

	for (int i = 0; i < graph->Get_graphPointsContainer_by_reference().size(); ++i)
	{
		xCoord.append(graph->Get_graphPointsContainer_by_reference()[i].first);
		yCoord.append(graph->Get_graphPointsContainer_by_reference()[i].second);
	}
}
Scanner::Scanner()
{
}


Scanner::~Scanner()
{
}
