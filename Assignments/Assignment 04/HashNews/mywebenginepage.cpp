/*======================================HEADERS=========================================*/
#include "mywebenginepage.h"
/*=============================acceptNavigationRequest Overiding=================================*/
bool MyWebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked && isMainFrame == true)
    {
        emit linkClicked(url);  // retrieve the url here for articles
        return false;
    }
    return true;
}
/*======================================CreateWindow Overiding==================================*/
QWebEnginePage *MyWebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
     QWebEnginePage *page = new QWebEnginePage(); //url clicked by user on google news for redirecting article link
     connect(page, &QWebEnginePage::urlChanged, this, [this] (const QUrl &url) { emit newPageUrlChanged(url);});
     return page;
}
/*======================================OVERRIDING=========================================*/
