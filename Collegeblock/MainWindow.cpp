#include "MainWindow.h"
#include "PiDeviceSide.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QRegExp>



QString getIntFromString(QString str)
{
	int pos = 0;
	QString part;
	QRegExp rx("(\\d+)");
	
	while ((pos = rx.indexIn(str, pos)) != -1) {
		part = rx.cap(1);
		pos += rx.matchedLength();
	}
	return part;
}

QString getCharsFromString(QString str)
{
	int pos = 0;
	QString part;
	QRegExp rx("^(\\D+)");
	
	while ((pos = rx.indexIn(str, pos)) != -1) {
		part = rx.cap(1);
		pos += rx.matchedLength();
	}
	return part;
}

void compareTimerClock(QTime time, QTime clocktime, int ret[2])
{
	ret[0] = time.hour() - clocktime.hour();
	ret[1] = time.minute() - clocktime.minute();
}





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
    delete ui;
}


int MainWindow::getMinutes(QTime time)
{
	return (60 * time.hour() + time.minute());
}


void MainWindow::ButtonClicked()
{
	QPushButton *btn = (QPushButton*)sender();
	QString str = btn->objectName();
	
	QList<QObject*> chillist = btn->parent()->findChildren<QObject*>();
	QString widgName;
	
	if (getCharsFromString(str).compare("buttonOnOff_")) 
	{
	}
	else if (getCharsFromString(str).compare("buttonRun_"))
	{
		foreach(auto obj, chillist)
		{
			widgName = (QString) (obj->metaObject()->className());
		}
	}
}


void MainWindow::RunButtonClicked()
{
	QPushButton *btn = (QPushButton*)sender();
	int idx = getIntFromString(btn->objectName()).toInt();
	
	switched[idx] = !switched[idx];
	
	if ( !switched[idx] && !onTimer[idx] )
		deactivatePin(pinArr[idx]);
	else if ( switched[idx] && !onTimer[idx] )
		activatePin(pinArr[idx]);
}


void MainWindow::StartChanged()
{
	QTimeEdit* start = (QTimeEdit*)sender();
	QString istr = getIntFromString(start->objectName());
	int idx = istr.toInt();
	
	int strt = getMinutes(start->time());
	int tme = getMinutes(ui->timeEdit->time());
	int stp = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_"+istr)->time());
	
	onTimer[idx] = false;
	if (!switched[idx] && ( strt <= tme < stp || (strt > stp && ((strt <= tme) || (tme < stp)))))
	{
		onTimer[idx] = true;
	}
	if (onTimer[idx])
	{
		activatePin(pinArr[idx]);
	}
	else
	{
		deactivatePin(pinArr[idx]);
	}
}


void MainWindow::StopChanged()
{
	QTimeEdit* stop = (QTimeEdit*)sender();
	QString istr = getIntFromString(stop->objectName());
	int idx = istr.toInt();
	QTime tm;
	
	int stp = getMinutes(stop->time());
	int tme = getMinutes(ui->timeEdit->time());
	int strt = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + istr)->time());
	
	onTimer[idx] = false;
	if (!switched[idx] && (strt <= tme < stp || (strt > stp && ((strt <= tme) || (tme < stp)))))
	{
		onTimer[idx] = true;
	}
	if (onTimer[idx])
	{
		activatePin(pinArr[idx]);
	}
	else
	{
		deactivatePin(pinArr[idx]);
	}
	
}


void MainWindow::showTime()
{
	int mnt = (ui->timeEdit->time()).minute();
	
	QTime time = QTime::currentTime();
	
	ui->timeEdit->setTime(time);
	
	if (mnt - time.minute() != 0)
	{
		compStartTmrs(time);
		compStopTmrs(time);
	}
}


void MainWindow::compStartTmrs(QTime time)
{
	int idx;
	QList<QTimeEdit*> timesList = ui->centralWidget->findChildren<QTimeEdit*>("timeStart_");
	
	foreach(QTimeEdit* qte, timesList)
	{
		idx = getIntFromString(qte->objectName()).toInt();
		if (!switched[idx] && (getMinutes(qte->time()) - getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + QString(idx))->time()) != 0) &&
			(getMinutes(time) - getMinutes(qte->time()) == 0) )
		{
			onTimer[idx] = true;
			activatePin(pinArr[idx]);
		}
	}
}


void MainWindow::compStopTmrs(QTime time)
{
	int idx;
	QList<QTimeEdit*> timesList = ui->centralWidget->findChildren<QTimeEdit*>("timeStop_");
	
	foreach(QTimeEdit* qte, timesList)
	{
		idx = getIntFromString(qte->objectName()).toInt();
		if (!switched[idx] && ( getMinutes(qte->time()) - getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + QString(idx))->time() ) != 0 ) &&
			(getMinutes(time) - getMinutes(qte->time()) == 0))
		{
			onTimer[idx] = false;
			deactivatePin(pinArr[idx]);
		}
	}
}





/*
void MainWindow::compareTimers(QTime time)
{
	
	QList<QTimeEdit*> timesList = ui->centralWidget->findChildren<QTimeEdit*>();
	QTimeEdit* negRef;
	QString name;
	QString index;
	int lstIdx;
	int proof;
	int negProof;
	
	
	foreach(QTimeEdit* qte, timesList)
	{
		index = getIntFromString(qte->objectName());
		name = getCharsFromString(qte->objectName());
		proof = getMinutes(qte->time());
		
		if (qte->isEnabled() && getMinutes(time) == proof)
		{
			if (name.compare("timeStart_") == 0)
			{
				negRef = ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + index);
				negProof = getMinutes(negRef->time());
				if (proof != negProof)
				{
					setTimer[index.toInt()] = true;
					activatePin(pinArray[index.toInt()]);
				}
			}
			if (name.compare("timeStop_") == 0)
			{
				negRef = ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + index);
				negProof = getMinutes(negRef->time());
				if (proof != negProof)
				{
					setTimer[index.toInt()] = false;
					if (!setRun[index.toInt()])
					{
						deactivatePin(pinArray[index.toInt()]);
					}
				}
			}
		}
	}
}


void MainWindow::StartChanged()
{
	QString startIdx = getIntFromString(((QTimeEdit*)sender())->objectName());
	
	int tme = getMinutes(ui->timeEdit->time());
	int strt = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStart_" + startIdx)->time());
	int stp = getMinutes(ui->centralWidget->findChild<QTimeEdit*>("timeStop_" + startIdx)->time());
	
	if ( strt <= tme < stp )
	{
		setTimer[startIdx.toInt()] = true;
		activatePin(pinArray[startIdx.toInt()]);
	}
		
		
	
	QTimeEdit* startTime = (QTimeEdit*)sender();
	
	
	ui->debugLine2->setText("Index " + startIdx + " : Startzeit gesetzt");
	
}
*/
	
	
	
	
	
	
	
	
	/*
{
	QList<QTimeEdit*> timesList = ui->centralWidget->findChildren<QTimeEdit*>();
	
	
	foreach(QTimeEdit* qte, timesList)
	{
		
		std::cout << getIntFromString(qte->objectName()).toStdString() << "\n";
	}
}
*/