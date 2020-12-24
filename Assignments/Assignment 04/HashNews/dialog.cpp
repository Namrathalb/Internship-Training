/*===========================HEADERS================================*/
#include "dialog.h"
#include "ui_dialog.h"
#include "logfile.h"
/*=========================CONSTRUCTOR===============================*/
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    di(new Ui::Dialog)
{
    di->setupUi(this);
    TheCurrentVerticalScroll = 0;
    writelog(__LINE__, "MainWindow()", "\tOpening New Dialog");
    setAttribute(Qt::WA_DeleteOnClose);
}
/*=========================DESTRUCTOR================================*/
Dialog::~Dialog()
{
    ThePageHeight = -1;
    TheCurrentVerticalScroll = 0;
    delete di;
}
/*=========================FUNCTION================================*/
void Dialog::read(QString link)
{
    ThePageHeight = 2000;
    QUrl str = QUrl(link);
    di->viewnews->load(str); //open article link in new window
    writelog(__LINE__, "read(QString link)", "Loading: Full Article", link);
}
void Dialog::on_Scroll_clicked()
{
     writelog(__LINE__, "on_scroll_clicked()", "Scroll: User Reading Article");
     ScrollPage();
}
void Dialog::ScrollPage()
{
       writelog(__LINE__, "ScrollPage()", "\tScroll: Article Begin"); //scroll page for the article links
       while (TheCurrentVerticalScroll <= ThePageHeight)
       {
           QEventLoop loop;
           di->viewnews->page()->runJavaScript(QString("window.scrollTo(0, %1);").arg(TheCurrentVerticalScroll));
           TheCurrentVerticalScroll += 1.5;
           QTimer t;
           t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
           t.start(30);
           loop.exec();
           qApp->processEvents();
       }
        writelog(__LINE__, "ScrollPage()", "\tScroll: Article End");
}
/*=========================FUNCTION===============================*/
