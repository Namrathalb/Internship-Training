/*===========================HEADERS================================*/
#include "CpuUsage.h"
#include "logfile.h"
#define myqDebug() qDebug() << qSetRealNumberPrecision(10)
/*=========================CONSTRUCTOR===============================*/
CpuUsage::CpuUsage() {
}
/*=========================FUNCTION================================*/
void CpuUsage::cleanup() {
       if (log) { PdhCloseLog(log, 0); } //Close the log file.
       if (m_query) { PdhCloseQuery(m_query); } // Close the query object.
}
void CpuUsage::intialize() {
       pdhStatus = PdhOpenQuery(NULL, 0, &m_query); // Open a query object.
       if (pdhStatus != ERROR_SUCCESS) {
           qDebug() <<L"PdhOpenQuery failed with 0x%x\n";
           cleanup();
       }
       // Add one counter that will provide the data.       
       pdhStatus = PdhAddCounter(m_query, L"\\Process(HashNews)\\% Processor Time", 0, &m_cpu); //APP CPU USAGE
       pdhStatus = PdhAddCounter(m_query, L"\\Process(HashNews)\\Working Set - Private", 0, &m_cpu); //APP MEMORY USAGE
       pdhStatus = PdhAddCounter(m_query, L"\\Processor(_TOTAL)\\% Processor Time", 0, &m_cpu);  //TOTAL CPU
       pdhStatus = PdhAddCounter(m_query, L"\\Process(_TOTAL)\\Working Set - Private", 0, &m_cpu);  //TOTAL MEMORY
       if (pdhStatus != ERROR_SUCCESS) {
           std::cout << "PdhAddCounter failed with 0x%x\n" << pdhStatus ;
           cleanup();
       }
       pdhStatus = PdhOpenLog(L"test.csv", PDH_LOG_WRITE_ACCESS | PDH_LOG_CREATE_ALWAYS, &dwLogType, m_query, 0, NULL, &log); // Open the log file for write access.
       if (pdhStatus != ERROR_SUCCESS) {
           qDebug() <<L"PdhOpenLog failed with 0x%x\n";
           cleanup();
       }
}
void CpuUsage::avg() {
   QFile file("test.csv"); // Open csv-file & Read data from file
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return;   
   QTextStream stream(&file); //stream the file as text file
   QList<QStringList> data; //read the line into data

       while (!stream.atEnd()) {
           QString line = stream.readLine();
           data << line.split(",");
       }
       for (int i = 1; i < data.size(); i++) {
           for(int j = 1; j < 5 ; j++) {
                QString t = data.at(i).at(j);
                t.remove(QChar('\"'));
                if(j==1)
                { long double xyz = QString::number(t.toDouble(), 'e', 128).toDouble(); hashnewscputotal = hashnewscputotal + xyz; }
                else if(j==2)
                { hashnewsmemtotal = hashnewsmemtotal + t.toInt(); }
                else if(j==3)
                { long double xyz = QString::number(t.toDouble(), 'e', 128).toDouble(); cputotal = cputotal + xyz; }
                else if(j==4)
                { memtotal = memtotal + t.toLongLong(&ok, 10); }
           }
       }
   QString starttime = data.at(1).at(0);  //start time from firstline
   starttime.remove(QChar('\"'));   
   QString endtime = data.at((data.size()-1)).at(0); //end time from lastline
   endtime.remove(QChar('\"'));
   string start = starttime.toStdString();

   hashnewscputotal = (hashnewscputotal/(data.size()-2)); //Average CPU - HashNews
   hashnewsmemtotal = (hashnewsmemtotal/(data.size()-1)); //Average Memory - HashNews(Total)
   hashnewsmemtotal = hashnewsmemtotal /1048576;//coverting into Mega Bytes
   cputotal = (cputotal/(data.size()-2)); //Average CPU - System(Total)
   memtotal = (memtotal/(data.size()-1)); //Average Memory - Process(Total)
   memtotal = memtotal /1048576;//coverting into Mega Bytes
   string end = endtime.toStdString();

   writelog(start, hashnewscputotal, hashnewsmemtotal, cputotal, memtotal, end); //sending statistics to logfile
   file.close();
}
void CpuUsage::updatelog() {
        pdhStatus = PdhUpdateLog(log, NULL);
        if (ERROR_SUCCESS != pdhStatus) {
            qDebug()  << "PdhUpdateLog failed with 0x%x\n" << pdhStatus;
            cleanup();
        }
}
/*=========================FUNCTION================================*/
