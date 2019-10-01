#include "MainWindow.h"
#include "PiDeviceSide.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QRegExp>



void compareTimerClock(QTime time, QTime clocktime, int ret[2])
{
	ret[0] = time.hour() - clocktime.hour();
	ret[1] = time.minute() - clocktime.minute();
}

QString getIntFromString(QString str)
{
	int pos = 0;
	QString num;
	QRegExp rx("(\\d+)");
	
	while ((pos = rx.indexIn(str, pos)) != -1) {
		num = rx.cap(1);
		pos += rx.matchedLength();
	}
	return num;
}

QString getCharsFromString(QString str)
{
	int pos = 0;
	QString chars;
	QRegExp rx("^(\\D+)");
	
	while ((pos = rx.indexIn(str, pos)) != -1) {
		chars = rx.cap(1);
		pos += rx.matchedLength();
	}
	return chars;
}



//	Object

MainWindow::MainWindow(QWidget *parent) : 
	QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	QTimer *timer = new QTimer(this);
	
	connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
	timer->start(1000);
}


MainWindow::~MainWindow()
{
	for (int i = 0; i < 16; i++)
	{
		deactivatePin(pinArr[i]);
	}
    delete ui;
}


int MainWindow::getMinutes(QTime time)
{
	return (60 * time.hour() + time.minute());
}


void MainWindow::DisableTime()
{
	QPushButton *btn = (QPushButton*)sender();
	QString nmbr = getIntFromString(btn->objectName());
	
	if (btn->isChecked())
	{
		ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + nmbr)->setEnabled(false);
		ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + nmbr)->setEnabled(false);
		deactivatePin(pinArr[nmbr.toInt()]);
	}
	else if (!btn->isChecked())
	{
		ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + nmbr)->setEnabled(true);
		ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + nmbr)->setEnabled(true);
		compStartStop(
			getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + nmbr)->time()), 
			getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + nmbr)->time()), 
			getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeEdit")->time()), 
			nmbr.toInt());
	}
}


void MainWindow::RunButtonClicked()
{
	QPushButton *btn = (QPushButton*)sender();
	QString nmbr = getIntFromString(btn->objectName());
	int idx = nmbr.toInt();
	
	
	if (!(switched[idx] = btn->isChecked()) && !(onTimer[idx]))
	{
		deactivatePin(pinArr[idx]);
	}
	else if ( switched[idx] &&  !(onTimer[idx]))
	{
		activatePin(pinArr[idx]);
	}
}


void MainWindow::StartChanged()
{
	QTimeEdit* start = (QTimeEdit*)sender();
	QString istr;
	int idx;
	int strt;
	int tme;
	int stp;
	
	if (start->isEnabled())
	{
		istr = getIntFromString(start->objectName());
		idx = istr.toInt();
		strt = getMinutes(start->time());
		tme = getMinutes(ui->timeEdit->time());
		stp = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + istr)->time());
	
	
		compStartStop(strt, stp, tme, idx);
	}
}


void MainWindow::StopChanged()
{
	QTimeEdit* stop = (QTimeEdit*)sender();
	QString istr;
	int idx;
	int strt;
	int tme;
	int stp;
	
	if (stop->isEnabled())
	{
		istr = getIntFromString(stop->objectName());
		idx = istr.toInt();
	
		stp = getMinutes(stop->time());
		tme = getMinutes(ui->timeEdit->time());
		strt = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + istr)->time());
	
	
		compStartStop(strt, stp, tme, idx);
	}
}


void MainWindow::showTime()
{
	int mnt = (ui->timeEdit->time()).minute();
	int idx;
	QString index;
	
	QTime time = QTime::currentTime();
	
	ui->timeEdit->setTime(time);
	
	if (mnt - time.minute() != 0)
	{
		for (idx = 0; idx < 16; idx++)
		{
			index = QString::number(idx);
			if ( (ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + index)->isEnabled()) && (ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + index)->isEnabled()) )
			{
				compStartStop(
					getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + index)->time()), 
					getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + index)->time()), 
					getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeEdit")->time()), 
					idx);
			}
		}
	}
}


void MainWindow::compStartStop(int start, int stop, int time, int index)
{
	if ( ( stop-start>0 && stop-time>0 && time-start>=0 ) || 
		( start-stop>0 && (time-start>=0 || stop-time>0) ) )
	{
		onTimer[index] = true;
	}
	else
	{
		onTimer[index] = false;
	}
	
	if (!switched[index])
	{
		if (onTimer[index])
		{
			activatePin(pinArr[index]);
		}
		else
		{
			deactivatePin(pinArr[index]);
		}
	}
}