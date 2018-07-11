#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Graph.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
	QVector<double> xCoord, yCoord;
	Graph Sorin;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void CreatePictureOfGraph(int &nrPoze,QString graph);
	int nrPoze = 0;


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
