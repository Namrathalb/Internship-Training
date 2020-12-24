/*===================HEADERS | CLASS DECLARATION==========================*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWebEngineProfile>
#include <QTimer>
#include "dialog.h"
#include "logfile.h"
#include "mywebenginepage.h"
#include "CpuUsage.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void linkClicked(const QUrl &url);
public:
    explicit MainWindow(QWidget *parent = 0);
    void ScrollPage();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
public slots:
    void on_Search_clicked();
    void on_Exit_clicked();
    void on_Zoom_clicked();
    void on_Refresh_clicked();
    void on_Cancel_clicked();
    void on_Scroll_clicked();
    void navigate(QUrl url);
private slots:
    void performance();
private:
    Ui::MainWindow *ui;
    Dialog *d;
    MyWebEnginePage *mypage;
    QTimer *t;
    CpuUsage *cpx;
    int TheCurrentVerticalScroll;
    int ThePageHeight;
	// Constants
    const QString windowTitle = "Hash Tag News"; // Application window title
	const QString windowIcon = ":/loadimg/icon.png"; // Application icon
	const QString pushButtonSearchDefault = "Search";
};
#endif // MAINWINDOW_H
/*===================HEADERS | CLASS DECLARATION============================*/
