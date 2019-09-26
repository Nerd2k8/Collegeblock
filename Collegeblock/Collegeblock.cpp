#include "MainWindow.h"
#include "PiDeviceSide.h"



int main(int argc, char *argv[])
{
	initGPIOs();
	
	QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}