/*===================HEADERS | CLASS DECLARATION==========================*/
#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QTimer>
#include "logfile.h"
namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    void read(QString link);
    void ScrollPage();
    ~Dialog();
private slots:
    void on_Scroll_clicked();
private:
    Ui::Dialog *di;
    int TheCurrentVerticalScroll;
    int ThePageHeight;
};
#endif // DIALOG_H
/*===================HEADERS | CLASS DECLARATION==========================*/
