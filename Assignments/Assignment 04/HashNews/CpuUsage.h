/*===================HEADERS | CLASS DECLARATION==========================*/
#ifndef PERFMON_H
#define PERFMON_H
#include <Pdh.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <pdhmsg.h>
#include <QTimer>
#include <QDebug>
#include <stdlib.h>
#include <QString>
#include "psapi.h"
#include "logfile.h"
using namespace std;
#pragma comment(lib,"Pdh.lib")
class CpuUsage {
public:
    explicit CpuUsage();
    void intialize();
    void updatelog();
    void cleanup();
    void avg();
private:
    long double hashnewscputotal = 0;
    long long int hashnewsmemtotal = 0;
    double cputotal = 0;
    long long int memtotal = 0;
    bool ok;
    PDH_HQUERY m_query;
    HLOG log = NULL;
    DWORD dwLogType = PDH_LOG_TYPE_CSV;
    PDH_STATUS pdhStatus;
    PDH_HCOUNTER m_cpu;
    PDH_FMT_COUNTERVALUE m_counterVal;
};
#endif // PERFMON_H
/*===================HEADERS | CLASS DECLARATION==========================*/
