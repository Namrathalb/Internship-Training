/*===================HEADERS | FUNCTION DECLARATION==========================*/
#ifndef LOGFILE_H
#define LOGFILE_H
#define _CRT_SECURE_NO_WARNINGS
#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QFile>
#include <string>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <stdio.h>
using namespace std;
void intialise();
void writelog(int y, QString x, QString h);
void writelog(int y, QString x, QString h, QString w);
void writelog(string a, double p, long int q, double r, long long int s, string z);
void closefile();
#endif // LOGFILE_H
/*===================HEADERS | FUNCTION DECLARATION==========================*/
