#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Generator.h"
#include "ProcessingUnit.h"
#include "Graph.h"
#include "Scanner.h"

#include <ui_mainwindow.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <qstring.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
    ui->customPlot->addGraph();


    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0, 100);
    ui->customPlot->yAxis->setRange(0, 100);
    ui->customPlot->replot();

    ui->customPlot_2->addGraph();
    ui->customPlot_2->xAxis->setLabel("x");
    ui->customPlot_2->yAxis->setLabel("y");
    ui->customPlot_2->xAxis->setRange(0, 100);
    ui->customPlot_2->yAxis->setRange(0,100);
    ui->customPlot_2->replot();

	ui->InferiorLimit_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	ui->SuperiorLimit_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	ui->PointsNumberMax_LineEdit_int->setValidator(new QIntValidator(0, 1000000, this));
	ui->Threshold_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	ui->MinimumLimitTrim_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	ui->MaximumLimitTrim_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	ui->RangeAttenuate_LineEdit->setValidator(new QIntValidator(0, 1000000, this));
	
	

	
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatePictureOfGraph(int & nrPoze,QString graph)
{
	QString s = QString::number(nrPoze);
	QString outputDir = QDir::currentPath() + "\\poze";
	QString fileName = graph + s + ".png";
	nrPoze++;
	QFile file(outputDir + "/" + fileName);
	if (!file.open(QIODevice::WriteOnly | QFile::WriteOnly))
	{
		QMessageBox::warning(0, "Could not create Project File",
			QObject::tr("\n Could not create Project File on disk"));


	}

	ui->customPlot->savePng(outputDir + "/" + fileName, 0, 0, 1.0, -1);


}

void MainWindow::on_btn_generate_clicked()
{
	bool Validator=true;
	if (ui->InferiorLimit_LineEdit->text().isEmpty())Validator = false;
	else if (ui->SuperiorLimit_LineEdit->text().isEmpty())  Validator = false;
	else if (ui->InferiorLimit_LineEdit->text().toDouble() > ui->SuperiorLimit_LineEdit->text().toDouble()) Validator = false;
	else if (ui->PointsNumberMax_LineEdit_int->text().isEmpty()) Validator = false;
	else if (ui->Threshold_LineEdit->text().isEmpty()) Validator = false;
	if (Validator == true)
	{
		Scanner Writer;
		Generator Calin(ui->PointsNumberMax_LineEdit_int->text().toInt(), ui->InferiorLimit_LineEdit->text().toDouble(), ui->SuperiorLimit_LineEdit->text().toDouble(), ui->Threshold_LineEdit->text().toInt());
		Writer.Write(Calin.GenerateNumbers(), "GeneratedNumbers.dat");
		Writer.ReadGraphics(this->xCoord, this->yCoord, "GeneratedNumbers.dat");

		ui->customPlot->addGraph();
		ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
		ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
		ui->customPlot->addGraph();
		ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));
		ui->customPlot->xAxis->setRange(0, ui->PointsNumberMax_LineEdit_int->text().toInt());
		ui->customPlot->yAxis->setRange(ui->InferiorLimit_LineEdit->text().toInt(), ui->SuperiorLimit_LineEdit->text().toDouble());
		ui->customPlot->graph(0)->setData(this->xCoord, this->yCoord);
		ui->customPlot->replot();
	}
	else
	{
		QVector<double> resetX, resetY;
		ui->customPlot->graph(0)->setData(resetX, resetY);
		ui->customPlot->replot();
	}
	

}




void MainWindow::on_pushButton_2_clicked()
{

	Scanner Writer;
	Graph Sorin;
	Writer.Read(&Sorin, "GeneratedNumbers.dat");
	ProcessingUnit Izabela;
    if(ui->Trim_rd_button->isChecked())
    {
		Graph Trimed;
		Izabela.Trim(&Sorin, &Trimed, ui->MinimumLimitTrim_LineEdit->text().toInt(), ui->MaximumLimitTrim_LineEdit->text().toInt());
		Writer.Write(Trimed, "GraphTrimed.dat");
		Writer.ReadGraphics(xCoord, yCoord, "GraphTrimed.dat");
		
		 ui->customPlot_2->xAxis->setRange(0, ui->PointsNumberMax_LineEdit_int->text().toInt());
		 ui->customPlot_2->yAxis->setRange(ui->InferiorLimit_LineEdit->text().toInt(), ui->SuperiorLimit_LineEdit->text().toDouble());
         ui->customPlot_2->graph(0)->setData(xCoord, yCoord);
         ui->customPlot_2->replot();
    }

    else if(ui->radioButton_2->isChecked())
    {
		Graph Attenuated;
		Izabela.Attenuate(&Sorin, &Attenuated, ui->RangeAttenuate_LineEdit->text().toInt());
		Writer.Write(Attenuated, "GraphAttenuated.dat");
		Writer.ReadGraphics(xCoord, yCoord, "GraphAttenuated.dat");
		
		ui->customPlot_2->xAxis->setRange(0, ui->PointsNumberMax_LineEdit_int->text().toInt());
		ui->customPlot_2->yAxis->setRange(ui->InferiorLimit_LineEdit->text().toInt(), ui->SuperiorLimit_LineEdit->text().toDouble());
        ui->customPlot_2->graph(0)->setData(xCoord, yCoord);
        ui->customPlot_2->replot();

    }
	else if (ui->radioButton->isChecked())
	{
		QString ValoareArie = QString::number(Izabela.CalculateArea(&Sorin),'g',6);
		ui->AreaValue_LineEdit->setText(ValoareArie);
		Writer.ReadGraphics(xCoord, yCoord, "GeneratedNumbers.dat");

        ui->customPlot_2->addGraph();
        ui->customPlot_2->graph(0)->setPen(QPen(Qt::blue)); 
        ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
        ui->customPlot_2->addGraph();
        ui->customPlot_2->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));
        ui->customPlot_2->xAxis->setRange(0, ui->PointsNumberMax_LineEdit_int->text().toInt()-1);
        ui->customPlot_2->yAxis->setRange(ui->InferiorLimit_LineEdit->text().toInt(), ui->SuperiorLimit_LineEdit->text().toDouble());
        ui->customPlot_2->graph(0)->setData(xCoord, yCoord);
        ui->customPlot_2->replot();
        ui->customPlot_2->graph(0)->setBrush(QBrush(Qt::NoBrush)); 

	}
}

void MainWindow::on_actionSave_triggered()
{
	CreatePictureOfGraph(nrPoze, "graphGen");
	CreatePictureOfGraph(nrPoze, "graphProc");
    
}
