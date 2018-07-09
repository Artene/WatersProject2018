#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
	QVector<double> xCoord, yCoord;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void CreatePictureOfGraph(int &nrPoze,QString graph);
	int nrPoze = 0;


private slots:
  
    void on_btn_generate_clicked();
    void on_pushButton_2_clicked();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
