#ifndef QLAYOUTITEM_TIMEDIFF_H
#define QLAYOUTITEM_TIMEDIFF_H

#include <qwidget.h>

namespace QWidget;


class QLayoutItem_Left_TimeDiff : public QWidget
{
	Q_OBJECT
		
public :
	QLayoutItem_Left_TimeDiff(QWidget *parent = 0, const char *name = 0);
	~QLayoutItem_Left_TimeDiff() { }
	
signals:
	void switchActivation();
	void setAlwaysOn();
	
};


#endif