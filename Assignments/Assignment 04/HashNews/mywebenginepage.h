/*===================HEADERS | CLASS DECLARATION==========================*/
#ifndef MYWEBENGINEPAGE_H
#define MYWEBENGINEPAGE_H
#include <QObject>
#include <QWebEngineView>
#include <QUrl>
#include <QDebug>
class MyWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    MyWebEnginePage(QObject* parent = 0) : QWebEnginePage(parent){}
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
    QWebEnginePage *createWindow(QWebEnginePage::WebWindowType type);
signals:
    void linkClicked(QUrl url);
    void newPageUrlChanged(QUrl link);
};
#endif // MYWEBENGINEPAGE_H
/*===================HEADERS | CLASS DECLARATION==========================*/
