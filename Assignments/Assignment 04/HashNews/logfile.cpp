/*======================================HEADERS=========================================*/
#include "logfile.h"
int ci=0;
/*===========================RETURNS THE CURRENT DATE & TIME=============================*/
inline QString getCurrentDateTime()  {
   QString cd = QDate::currentDate().toString("yyyy-MM-dd");
   QString ct = QTime::currentTime().toString("hh-mm-ss");
   cd.append("_");
   cd.append(ct);
   return cd;
}
/*=========================LOG FILE NAME=================================================*/
QString s = "log_" + getCurrentDateTime() + ".txt"; //Log File is created
QFile file(s);
/*=========================INTIALIZE====================================================*/
void intialise() {
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out  << "Index" << "\t\t"
         << "TIMESTAMP" << "\t\t\t\t"
         << "Linenumber" << "\t\t"
         << "Function Name" << "\t\t\t\t\t"
         << "User value" << "\n"; ci++;
}
/*==============================OVERLOADING===============================================*/
void writelog(int y, QString x, QString h) {
    QTextStream out(&file);
    out << ci << "\t\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t" << x << "\t\t\t\t" << h << "\n"; ci++;
}
void writelog(int y, QString x, QString h, QString w) {
    QTextStream out(&file);
    out << ci << "\t\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t" << x << "\t\t\t\t" << h << w << "\n"; ci++;
}
void writelog(string a, double p, long q, double r, long long int s, string z)
{
    QTextStream out(&file);
    out << "\n-------------PERFORMANCE REPORT--------------\n";
    out << "\nSTART TIME of HashNews = " << a.c_str() << "\n";
    out << "Average CPU usage (Processor-Time) for HashNews = " << p << "%" << "\n";
    out << "Average Memory usage (Working Set) for HashNews = " << q << "MB" << "\n";
    out << "Average Total CPU usage (Processor-Time) for system  = " << r << "%" << "\n";
    out << "Average Total Memory usage (Working Set) for system = " << s << "MB" << "\n";
    out << "EXIT TIME of HashNews = " << z.c_str() << "\n";
}
void closefile()
{
   file.close();
}
/*==============================OVERLOADING===============================================*/
