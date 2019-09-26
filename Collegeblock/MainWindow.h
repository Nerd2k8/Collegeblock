#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PiDeviceSide.h"
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QTime>

void compareTimerClock(QTime time, QTime clocktime, int ret[2]);  		//	int-array with hour[0] & minute[1] differences. (time - clocktime)


QString getIntFromString(QString str); 		// match integers 0 to 99
QString getCharsFromString(QString str);



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
	int pinArr[16] = { 0, 2, 3, 21, 22, 23, 24, 25, 1, 4, 5, 6, 26, 27, 28, 29 };
	bool onTimer[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	bool switched[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	
	
	Q_OBJECT
	
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
public slots:
    void ButtonClicked();
	void RunButtonClicked();
	void StartChanged();
	void StopChanged();

private:
    Ui::MainWindow *ui;
	void showTime();
	void compStartTmrs(QTime time);
	void compStopTmrs(QTime time);
	int getMinutes(QTime time);
};

#endif // MAINWINDOW_H
