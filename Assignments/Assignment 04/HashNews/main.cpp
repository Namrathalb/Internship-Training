/*======================================HEADERS=========================================*/
#include "mainwindow.h"
#include "logfile.h"
#include <QApplication>
/*======================================MAIN=========================================*/
int main(int argc, char *argv[])
{
    intialise();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
/*======================================MAIN=========================================*/
