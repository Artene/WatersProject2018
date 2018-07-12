#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Graph.h"
#include "Scanner.h"
#include <thread>
#include <chrono>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
	QVector<double> xCoord, yCoord;
	Graph Sorin;
	Scanner Writer;
	double minimumValue=0, maximumValue=0;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void CreatePictureOfGraph(QString graph);


private:
	std::thread *pProcThread;

	void GenerateGraph();
	void PlotGraph();

private slots:
  
    void on_btn_generate_clicked();
    void on_pushButton_2_clicked();
    void on_actionSave_triggered();
	void on_horizontalSlider_valueChanged(int);
	void on_actionNew_triggered();
	void on_actionClose_triggered();
	void on_actionOpen_triggered();
private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
