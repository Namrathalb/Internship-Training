/*=======================================HEADERS=========================================*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
/*======================================CONSTRUCTOR======================================*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowIcon(QIcon(windowIcon));
	this->setWindowTitle(windowTitle);
    ui->Search->setEnabled(true);
    mypage = new MyWebEnginePage;
    cpx = new CpuUsage();
    t = new QTimer(this);
    ui->view->setPage(mypage);
    TheCurrentVerticalScroll = 0;
    connect(mypage, SIGNAL(linkClicked(QUrl)), this, SLOT(navigate(QUrl)));
    connect(mypage, SIGNAL(newPageUrlChanged(QUrl)), this, SLOT(navigate(QUrl)));
    connect(t, &QTimer::timeout, this, &MainWindow::performance);
    cpx->intialize();
    t->start(1000);
    ui->tabWidget->setCurrentIndex(0);
    writelog(__LINE__, "MainWindow()", "\tStarting Application");
}
/*======================================DESTRUCTOR=======================================*/
MainWindow::~MainWindow()
{
    closefile();
    delete d;
    delete mypage;
    delete t;
    delete cpx;
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    writelog(__LINE__, "~MainWindow()", "\tClosing Application");
    cpx->avg();
}
/*====================================SEARCH BUTTON======================================*/
void MainWindow::on_Search_clicked()
{
    QUrl url;
    TheCurrentVerticalScroll =0; // scroll to top
    writelog(__LINE__, "Search_clicked()", "Search-HashTag: #", ui->lineEdit->text());
        if(ui->radioButton->isChecked())
        {
             url =  QUrl("https://www.newindianexpress.com/topic?term="+ui->lineEdit->text()+"&request=MIN&type=title&row_type=A");
             writelog(__LINE__, "Search_clicked()", "News Source: New Inian Express");
             ThePageHeight = 1700; //scroll till end of articlelist by setting height of page
        }
        if(ui->radioButton_2->isChecked())
        {
            url =  QUrl("https://www.thehindu.com/search/?q="+ui->lineEdit->text()+"&order=DESC&sort=publishdate");
            writelog(__LINE__, "Search_clicked()", "News Source: The Hindu");
            ThePageHeight = 1180; //scroll till end of articlelist by setting height of page
        }
        if(ui->radioButton_3->isChecked())
        {
            url = QUrl("https://edition.cnn.com/search?q="+ui->lineEdit->text());
            writelog(__LINE__, "Search_clicked()", "News Source: CNN");
            ThePageHeight = 740; //scroll till end of articlelist by setting height of page
        } 
        if(ui->radioButton_4->isChecked())
        {
            url =  QUrl("https://abcnews.go.com/search?searchtext="+ui->lineEdit->text()+"&sort=date");
            writelog(__LINE__, "Search_clicked()", "News Source: abc News");
            ThePageHeight = 700; //scroll till end of articlelist by setting height of page
        }
        if(ui->radioButton_5->isChecked())
        {
            url = QUrl("https://news.google.com/search?q="+ui->lineEdit->text()+"%20when%3A1d&hl=en-IN&gl=IN&ceid=IN%3Aen");
            writelog(__LINE__, "Search_clicked()", "News Source: Google News");
            ThePageHeight = 5000; //scroll till end of articlelist by setting height of page
        }
    ui->view->load(url); //openlink
    writelog(__LINE__, "Search_clicked()", "News URL: ", url.toString());
    ui->tabWidget->setCurrentIndex(1);
    writelog(__LINE__, "Search_clicked()", "WebResults : News articles List");
}
/*====================================SIGNAL NAVIGATE=======================================*/
void MainWindow::navigate(QUrl url)
{
    qDebug() << Q_FUNC_INFO << "START" << url;
    writelog(__LINE__, "navigate(QUrl url)", "Capturing Article URL: ", url.toString());
    if(url.toString().contains("per_page"))
    {
        ui->view->load(url); //when new indianexpress link loads the next list of articles
    }
    else if(url.toString().contains("news.google.com"))
    {
        d = new Dialog();
        d->read(url.toString());
        d->hide(); //hide the redirected the window on article from google news source
        d->~Dialog(); //destry the object after its redirected to the news
    }
    else //loading the clicked article link
    {
        d = new Dialog();
        d->read(url.toString());
        d->show();
    }
    writelog(__LINE__, "navigate(QUrl url)", "Creating New Dialog Object to Read News");
}
/*======================================EXIT BUTTON=========================================*/
void MainWindow::on_Exit_clicked()
{
    writelog(__LINE__, "Exit_clicked()", "\tExit: Closing UI.");
    this->close();
}
/*====================================REFRESH BUTTON=======================================*/
void MainWindow::on_Refresh_clicked()
{
    writelog(__LINE__, "Refresh_clicked()", "Reloading: Current URL / Web page");
    ui->view->reload();
}
/*======================================SCROLL BUTTON=========================================*/
void MainWindow::on_Scroll_clicked()
{
    if(ui->radioButton_2->isChecked())
    {
        QString code1 = "$('div.mobileadsubentry.hidden-sm.hidden-md.hidden-lg').remove();";
        QString code2 = "$('div.covidMobCube.ss.displaycovidMobCube').remove();";
        writelog(__LINE__, "on_scroll_clicked()", "Removed ads for Hindu"); //removes ads
        mypage->runJavaScript(code1);
        mypage->runJavaScript(code2);      
    }
    writelog(__LINE__, "on_scroll_clicked()", "Scroll: Till the End of Article List");
    ScrollPage();
}
void MainWindow::performance()
{
     cpx->updatelog(); //Recording CPU usage
}
void MainWindow::ScrollPage()
{
       writelog(__LINE__, "ScrollPage()", "\tScroll: Begin"); //scroll in a loop
       while (TheCurrentVerticalScroll <= ThePageHeight)
       {
           QEventLoop loop;
           ui->view->page()->runJavaScript(QString("window.scrollTo(0, %1);").arg(TheCurrentVerticalScroll));
           TheCurrentVerticalScroll += 1.25;
           QTimer t;
           t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
           t.start(30);
           loop.exec();
           qApp->processEvents();
       }  
       writelog(__LINE__, "ScrollPage()", "\tScroll: End");
}
/*======================================ZOOM BUTTON========================================*/
void MainWindow::on_Zoom_clicked()
{
    qreal factor = ui->view->zoomFactor();
    writelog(__LINE__, "Zoom_clicked()", "Zooming Page..");
    factor += 0.1;
    if(factor > 5)
    {
        factor = 5;
    }
    ui->view->setZoomFactor(factor);
}
/*======================================CANCEL BUTTON=========================================*/
void MainWindow::on_Cancel_clicked()
{
  writelog(__LINE__, "Cancel_clicked()", "Calling: Back to Main/First Tab");
  ui->tabWidget->setCurrentIndex(0);
}
