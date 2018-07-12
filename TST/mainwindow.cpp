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
    ui(new Ui::MainWindow),
	pProcThread(nullptr)
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatePictureOfGraph(QString graph)
{
	QString s = QTime::currentTime().toString();
	
	s.replace(":", "_");
	QString outputDir = QDir::currentPath() +"/saved_files/";
	QString fileName = graph + s + ".png";

	//QFile file(outputDir + "/" + fileName);
	QPixmap screen_shot = ui->centralWidget->grab();
	screen_shot.save(outputDir + fileName, "PNG");

	//ui->customPlot->savePng(outputDir + "/" + fileName, 0, 0, 1.0, -1);
	
//	QPixmap screen_shot = ui->centralWidget->grab();
//	screen_shot.save(s+".png","PNG");



}

void MainWindow::GenerateGraph()
{

		Generator Calin(ui->PointsNumberMax_LineEdit_int->text().toInt(), ui->InferiorLimit_LineEdit->text().toDouble(), ui->SuperiorLimit_LineEdit->text().toDouble(), ui->Threshold_LineEdit->text().toInt());
		Sorin.Set_graphPointsContainter(Calin.GenerateNumbers());

		Writer.ReadGraphics(this->xCoord, this->yCoord, &Sorin);
	
}

void MainWindow::PlotGraph()
{
	ui->customPlot->addGraph();
	ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
	ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
	ui->customPlot->addGraph();
	ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));

	minimumValue = ui->InferiorLimit_LineEdit->text().toDouble();
	maximumValue = ui->SuperiorLimit_LineEdit->text().toDouble();

	ui->customPlot->xAxis->setRange(0, ui->PointsNumberMax_LineEdit_int->text().toInt());
	ui->customPlot->yAxis->setRange(minimumValue, maximumValue);

	ui->customPlot->graph(0)->setData(this->xCoord, this->yCoord);
	ui->customPlot->replot();
}

void MainWindow::on_btn_generate_clicked()
{
	int cycleCnt = 0;
	bool Validator = true;
	if (ui->InferiorLimit_LineEdit->text().isEmpty())Validator = false;
	else if (ui->SuperiorLimit_LineEdit->text().isEmpty())  Validator = false;
	else if (ui->InferiorLimit_LineEdit->text().toDouble() > ui->SuperiorLimit_LineEdit->text().toDouble()) Validator = false;
	else if (ui->PointsNumberMax_LineEdit_int->text().isEmpty()) Validator = false;
	else if (ui->Threshold_LineEdit->text().isEmpty()) Validator = false;
	else if (ui->Threshold_LineEdit->text()>ui->SuperiorLimit_LineEdit->text())Validator=false;
	if(Validator==true)
		if (!ui->checkBox_Threads->isChecked() || ui->NumberOfGraphics_LineEdit->text().isEmpty())
		{
			GenerateGraph();
			PlotGraph();
		}
		else
		{
		
			while (ui->checkBox_Threads->isChecked() && (++cycleCnt <= ui->NumberOfGraphics_LineEdit->text().toInt()))
			{
				pProcThread = new std::thread(&MainWindow::GenerateGraph, this);
				pProcThread->join();
				delete pProcThread;

				PlotGraph();

				on_pushButton_2_clicked();

				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
	else
	{
		ui->customPlot_2->graph(0)->data()->clear();
		ui->customPlot_2->replot();
		ui->customPlot->graph(0)->data()->clear();
		ui->customPlot->replot();
	}
}


void MainWindow::on_pushButton_2_clicked()
{

	ProcessingUnit Izabela;
	if (ui->Trim_rd_button->isChecked())
	{
		bool Validator = true;
		if (ui->MinimumLimitTrim_LineEdit->text().isEmpty())Validator = false;
		else if (ui->MaximumLimitTrim_LineEdit->text().isEmpty())  Validator = false;
		if (Validator == true)
		{
			Graph Trimed;
			QVector<double> xCoordTrimed, yCoordTrimed;			
			Izabela.Trim(&Sorin, &Trimed, ui->MinimumLimitTrim_LineEdit->text().toInt(), ui->MaximumLimitTrim_LineEdit->text().toInt());
			Writer.ReadGraphics(xCoordTrimed, yCoordTrimed, &Trimed);
			ui->customPlot_2->xAxis->setRange(0, xCoord.size());
			ui->customPlot_2->yAxis->setRange(minimumValue,maximumValue);
			ui->customPlot_2->graph(0)->setData(xCoordTrimed, yCoordTrimed);
			ui->customPlot_2->replot();

		}
		else
		{
			ui->customPlot_2->graph(0)->data()->clear();
			
		}
	}
  
	else if (ui->radioButton->isChecked())
	{
		if (!Sorin.Get_graphPointsContainer_by_reference().empty())
		{
			QString ValoareArie = QString::number(Izabela.CalculateArea(&Sorin), 'g', 6);
			ui->AreaValue_LineEdit->setText(ValoareArie);
			Writer.ReadGraphics(xCoord, yCoord, &Sorin);

			ui->customPlot_2->addGraph();
			ui->customPlot_2->graph(0)->setPen(QPen(Qt::blue));
			ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
			ui->customPlot_2->addGraph();
			ui->customPlot_2->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));

			ui->customPlot_2->xAxis->setRange(0, xCoord.size());
			ui->customPlot_2->yAxis->setRange(minimumValue, maximumValue);

			ui->customPlot_2->graph(0)->setData(xCoord, yCoord);
			ui->customPlot_2->replot();
			ui->customPlot_2->graph(0)->setBrush(QBrush(Qt::NoBrush));
		}
	}
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
	Scanner Writer;
	ProcessingUnit Izabela;
	Graph Attenuated;
	Izabela.Attenuate(&Sorin, &Attenuated, value);
	Writer.ReadGraphics(xCoord, yCoord, &Attenuated);

	ui->customPlot_2->xAxis->setRange(0, xCoord.size());
	ui->customPlot_2->yAxis->setRange(minimumValue, maximumValue);
	ui->customPlot_2->graph(0)->setData(xCoord, yCoord);
	ui->customPlot_2->replot();
}
void MainWindow::on_actionSave_triggered()
{	
	CreatePictureOfGraph("ScreenShot");
	QString s = QTime::currentTime().toString();
	s.replace(":", "_");
	std::string CurrentPath = QDir::currentPath().toUtf8().constData();
	std::string date = s.toUtf8().constData();
	Writer.Write(Sorin, CurrentPath+"/saved_files/generatedGraph"+ date+".dat");
	

}

void MainWindow::on_actionNew_triggered()
{
	ui->customPlot->graph(0)->data()->clear();
	ui->customPlot->replot();

	ui->customPlot_2->graph(0)->data()->clear();
	ui->customPlot_2->replot();

	ui->SuperiorLimit_LineEdit->clear();
	ui->PointsNumberMax_LineEdit_int->clear();
	ui->InferiorLimit_LineEdit->clear();
	ui->Threshold_LineEdit->clear();

	ui->MinimumLimitTrim_LineEdit->clear();
	ui->MaximumLimitTrim_LineEdit->clear();
	//
	ui->NumberOfGraphics_LineEdit->clear();
	ui->AreaValue_LineEdit->clear();

	ui->Trim_rd_button->setChecked(false);
	ui->radioButton->setChecked(false);

	Sorin.Get_graphPointsContainer_by_reference().clear();


}

void MainWindow::on_actionClose_triggered()
{
	QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{

	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath()+"/saved_files", "Data(*.dat)");
	std::string file = filename.toUtf8().constData();
	if (!file.empty()) {
		Scanner Writer;

		Writer.Read(&Sorin, file);
		Writer.ReadGraphics_2(this->xCoord, this->yCoord,file);
		Sorin.Get_graphPointsContainer_by_reference().resize(xCoord.size());

		ui->customPlot->addGraph();
		ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
		ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
		ui->customPlot->addGraph();
		ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));

		ui->customPlot->xAxis->setRange(0, xCoord.size());

		for (int i = 0; i < yCoord.size(); i++)
		{
			yCoord[i] > maximumValue ? maximumValue = yCoord[i] : 0;
			yCoord[i] < minimumValue ? minimumValue = yCoord[i] : 0;
		}

		ui->customPlot->yAxis->setRange(minimumValue, maximumValue);
		
		ui->customPlot->graph(0)->setData(this->xCoord, this->yCoord);
		ui->customPlot->replot();
		
		ui->customPlot_2->graph(0)->data()->clear();
		ui->customPlot_2->replot();
	}

}

