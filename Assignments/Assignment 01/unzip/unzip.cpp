#include <iostream>
#include <Windows.h>
#include <WinDef.h>
#include <Shellapi.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <Shlwapi.h>
#include <Shldisp.h>
#include <oaidl.h>
#include <objbase.h>
#include <ctime>
#include <stdio.h>
#include <combaseapi.h>
#include <comutil.h>
#include <shlobj.h>
#include <filesystem>
#include <direct.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <unordered_set>
#include <map>
#include "atlbase.h"
#include "atlstr.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "User32.lib")

#pragma warning(suppress : 43)
#pragma warning(suppress : 65) 

using namespace std;
typedef vector <string> stringvec;
typedef map <string, string> stringmap;
typedef unordered_set <string> stringset;
stringset::iterator itr;
string src, dst, fname, vno, exe;
int c = 0, x;
char character = 'A';

string check(string vno, stringset s);
void read_directory(const string& name, stringset& s);
void displayFiles(stringset s);
void ren(string dst, string fname);
void rem(string dst, string fname);
void rep(string dst, string fname);
void ATP();
void OTE();
void DMIT();
void Unzip(const char* a, const char* b);

inline string getCurrentDateTime() //REURN STHE CURRENT DATE AND TIME TO LOG FILE NAME
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);
    std::string str(buffer);
    return str;
}

string s = "log_" + getCurrentDateTime() + ".txt"; //Log File is created
ofstream file;

template <typename T>
 void logfile(int y, string x, T const& h) {
     file << c << "\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t" << x << "\t\t\t" << h << "\n" << endl; c++; 
}

 string filename(stringset j) // checks the filename with the version number
 {
     string d;
     for (itr = j.begin(); itr != j.end(); ++itr)
     {
         d = *itr;
         if (d.find(".exe") < d.length())
         {
             return d;
         }
     }
 }

string check(string vno, stringset s) // checks the filename with the version number
 {    
    string d;
     for (itr = s.begin(); itr != s.end(); ++itr)
     {
          d = *itr;
          if (d.find(vno) < d.length())
          {
              return d;
          }
     } 
     return "File Not Found";
 }

void read_directory(const string& name, stringset& s) //Reads the file name in a source directory to a set
{
    string pattern(name);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            s.insert(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
}

void displayFiles(stringset s) // Displays the file names stored in the set
{
    cout << "\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << "\n";
    for (const string& i : s)
    {
        std::size_t index = i.find(".");
        if (index < i.length() && i != "." && i != "..")
            cout << endl << i;
    }
    cout << "\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << "\n";
}

void ren(string dst, string fname)
{
    int len = fname.length();
    fname[len-3] = '\0';
    string xyz = dst + "\\" + fname;
    string pqr = "DMIApp";
    pqr.append(&character);
    cout << "\n" << pqr << "\n";
    character++; //Renaming the unzip folder to New name and performing same when next file is extracted as subsequent DMIAppA, DMIAppB
    int result = rename(xyz.c_str(), pqr.c_str());
    if (result == 0)
    {
        logfile(__LINE__, "ren", "File Rename Sucess");
        cout << "\n File Rename Success\n";
    }
    else
    {
        logfile(__LINE__, "ren", "File Rename Failure");
        cout << "\n File Rename Failure\n";
    }
}

void rem(string dst, string fname)
{
    stringset cf;  
    int len = fname.length();
    fname[len-4] = '\0';
    fname = fname.substr(0, len - 4);
    string mn = dst + "\\" + fname;
    read_directory(mn, cf);
    for (itr = cf.begin(); itr != cf.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            cf.erase(itr--);
    }
    displayFiles(cf);
    exe = filename(cf);
    if (exe == "File Not Found")
    {
        cout << "\n FILE NOT FOUND \n";
        logfile(__LINE__, "rem", "File NOT FOUND");
        system("pause");
        exit(0);
    }
    else
    {
        string xyz = dst + "\\" + fname + "\\"+ exe;
        cout << "\n To copy .exe Source path is : " << xyz << "\n";
        string w = "move " + xyz + " " + dst;
        cout << "\n" << w << "\n";    // perform File moving operation by copying .exe file to OTE_tester Folder
        if (system(w.c_str()))
        {
            logfile(__LINE__, "OTE", "Moving Failed");
            cout << "\n Moving File was Failed\n";
        }
        else
        {
            cout << "\n Moving File was Success\n";
            logfile(__LINE__, "OTE", "Moving Success");
        }
        string m = "Rmdir " + dst + "\\" + fname;
        cout << "\n" << m << "\n";    // performing Remove directory for the empty folder once the .exe is copied
        if (system(m.c_str()))
        {
            cout << "\n Remove Directory Failure\n";
            logfile(__LINE__, "OTE", "Removing Directory Failure");
        }
        else
        {
            cout << "\n Remove Directory Success\n";
            logfile(__LINE__, "OTE", "Removing Directory Success");
        }
    }
}

void rep(string dst, string fname)
{
    int len = fname.length();
    fname[len-3] = '\0';
    string xyz = dst + "\\" + fname;
    string pqr = "OTE_Tester"; //Perform File name for the unzip folder
    int result = rename(xyz.c_str(), pqr.c_str());
    if (result == 0)
    {
        logfile(__LINE__, "rep", "File Renamed to OTE_Tester");
        cout << "\n File Rename Success\n" << "\n" << "New Unzipped Folder name : " << pqr << "\n";
    }
    else
    {
        logfile(__LINE__, "rep", "File Renamed Failed");
        cout << "\n File Rename Failed\n";
    }
}

void ATP()
{
    logfile(__LINE__, "OTE", "ATP Running");    
    cout << "\n ---------------------Starting ATP---------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;
    logfile(__LINE__, "ATP", src); //take source file path 
    cout << "\n Files in the directory :- \n";
    stringset currentFiles;
    logfile(__LINE__, "ATP", "CALLING read_directory() FUNCTION");
    read_directory(src, currentFiles); ////Read files in the source

    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }
    logfile(__LINE__, "ATP", "CALLING displayfiles() FUNCTION");
    displayFiles(currentFiles); //Display files in the source
    logfile(__LINE__, "ATP", "CALLING system(pause) FUNCTION");
    system("pause");  //wait for few seconds and press any key to continue

    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space
    fname = check(vno, currentFiles);
    if (fname == "File Not Found")
    {
        logfile(__LINE__, "ATP", "File not found");
        cout << "\n FILE NOT FOUND \n";
        system("pause");
        exit(0);
    }
    else
    {
        logfile(__LINE__, "ATP", fname);
        string res = src + "\\" + fname;
        cout << "\n Final Source File path is : " << res << "\n";
        logfile(__LINE__, "ATP", res); //add .zip to file name and append it to source file path
        cout << "\nEnter the Destination location: ";
        cin >> dst;
        logfile(__LINE__, "ATP", dst); //take the destination path
        logfile(__LINE__, "ATP", "CALLING FUNCTION Unzip(src, dst)");

        const char* p = res.c_str();//convert the source and destination file path to const char *
        const char* q = dst.c_str();
        Unzip(p, q);    // and send it as parameters to Unzip Funtion.
        rep(dst, fname);
    }
    logfile(__LINE__, "DMI", "Ending ATP");
    cout << "\n ---------------------Ending ATP---------------------\n";
}

void OTE()
{
    logfile(__LINE__, "OTE", "OTE Running");
    cout << "\n ---------------------Starting OTE---------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;
    logfile(__LINE__, "OTE", src); //take source file path 
    cout << "\n Files in the directory :- \n";
    stringset currentFiles;
    logfile(__LINE__, "OTE", "CALLING read_directory() FUNCTION");
    read_directory(src, currentFiles); ////Read files in the source

    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }
    logfile(__LINE__, "OTE", "CALLING displayfiles() FUNCTION");
    displayFiles(currentFiles); //Display files in the source
    logfile(__LINE__, "OTE", "CALLING system(pause) FUNCTION");
    system("pause");  //wait for few seconds and press any key to continue

    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space    
    fname = check(vno, currentFiles);
    if (fname == "File Not Found")
    {
        logfile(__LINE__, "OTE", "File not found");
        cout << "\n FILE NOT FOUND \n";
        system("pause");
        exit(0);
    }
    else
    {
        logfile(__LINE__, "OTE", fname);
        string res = src + "\\" + fname;
        cout << "Final Source File path is : " << res << "\n";
        logfile(__LINE__, "OTE", res); //add .zip to file name and append it to source file path
        cout << "\nEnter the Destination location: ";
        cin >> dst;
        logfile(__LINE__, "OTE", dst); //take the destination path
        logfile(__LINE__, "OTE", "CALLING FUNCTION Unzip(src, dst)");
        const char* p = res.c_str(); //convert the source and destination file path to const char *
        const char* q = dst.c_str();
        Unzip(p, q); //and send it as parameters to Unzip Funtion.
        rem(dst, fname);
    }
    logfile(__LINE__, "DMI", "Ending OTE");
    cout << "\n ---------------------Ending OTE---------------------\n";
}

void DMIT()
{
    logfile(__LINE__, "DMI", "DMI Running");
    cout << "\n ------------------Starting DMI------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;  // take source file path
    logfile(__LINE__, "DMI", src);
    cout << "\n Files in the directory :- \n";
    stringset currentFiles;
    logfile(__LINE__, "DMI","CALLING read_directory() FUNCTION" );
    read_directory(src, currentFiles); //Read files in the source
   
    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }

    logfile(__LINE__, "DMI", "CALLING displayfiles() FUNCTION");
    displayFiles(currentFiles); //Display files in the source
    logfile(__LINE__, "DMI", "CALLING system(pause) FUNCTION");
    system("pause"); //wait for few seconds and press any key to continue
    
    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space
    fname = check(vno, currentFiles);
    if (fname == "File Not Found")
    {
        logfile(__LINE__, "OTE", "File not found");
        cout << "\n FILE NOT FOUND \n";
        system("pause");
        exit(0);
    }
    else
    {
        logfile(__LINE__, "DMI", fname);
        string res = src + "\\" + fname;
        cout << "\n Final Source File path is : " << res << "\n";
        logfile(__LINE__, "DMI", res); //add .zip to file name and append it to source file path
        cout << "\n Enter the Destination location: ";
        cin >> dst;
        logfile(__LINE__, "DMI", dst); //take the destination path
        logfile(__LINE__, "DMI", "CALLING FUNCTION Unzip(src, dst)");

        const char* p = res.c_str();//convert the source and destination file path to const char * 
        const char* q = dst.c_str();
        Unzip(p, q); //and send it as parameters to Unzip Funtion.   
        ren(dst, fname); //callig rename function
        Unzip(p, q);
        ren(dst, fname);
    }
    logfile(__LINE__, "DMI", "Ending DMI");
    cout << "\n ---------------------Ending DMI---------------------\n";
}

void Unzip(const char* a, const char* b)
{
    try
    {
        BSTR source = _com_util::ConvertStringToBSTR(a); // BSTR source = SysAllocString(L"C:\\Users\\questuser\\eclipse-workspace\\Unzip_util\\src\\exam-2020.zip");
        BSTR dest = _com_util::ConvertStringToBSTR(b);   // BSTR dest = SysAllocString(L"C:\\Users\\questuser\\Desktop");
        HRESULT hResult;
        IShellDispatch* pISD;
        Folder* pToFolder = (Folder*)malloc(sizeof(Folder));
        VARIANT vDir, vFile, vOpt;

        HRESULT w = NULL;
        if ((w == CoInitialize(NULL)) == NULL)
            return;

        hResult = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pISD);

        if (SUCCEEDED(hResult))
        {
            VariantInit(&vDir);
            vDir.vt = VT_BSTR;
            vDir.bstrVal = dest; //L"C:\\test.zip\\\0\0";
            hResult = pISD->NameSpace(vDir, &pToFolder);

            if (SUCCEEDED(hResult))
            {
                Folder* pFromFolder = (Folder*)malloc(sizeof(Folder));
                VariantInit(&vFile);
                vFile.vt = VT_BSTR;
                vFile.bstrVal = source;             //L"C:\\test.txt";
                pISD->NameSpace(vFile, &pFromFolder);
                FolderItems* fi = (FolderItems*)malloc(sizeof(FolderItems*)); // if (pFromFolder == nullptr) throw exception("read access violation");
                pFromFolder->Items(&fi);
                VariantInit(&vOpt);
                vOpt.vt = VT_I4;
                vOpt.lVal = FOF_NO_UI;  //4; // Do not display a progress dialog box  
                VARIANT newV;           // Creating a new Variant with pointer to FolderItems to be copied
                VariantInit(&newV);
                newV.vt = VT_DISPATCH;
                newV.pdispVal = fi;  // if (pToFolder == NULL)
                hResult = pToFolder->CopyHere(newV, vOpt);  //if (pFromFolder != NULL)
                pFromFolder->Release();
                pToFolder->Release();
            }
            pISD->Release();
        }
        CoUninitialize();
    }
    catch (exception e)
    {
        file << __TIMESTAMP__ << '\t' << e.what() << '\n';
    }
}

int main()
{
    int a, k = 1;
    file.open(s, ios::out | ios::app);
    cout << "\nProgram Log File Name : " << s << "\n\n";
    file << "Sl.No" << "\t" << "TIMESTAMP" << "\t\t\t\t" << "LINE NUMBER" << "\t\t" << "FUNCTION NAME" << "\t\t" << "USER INPUT VALUE" << "\n" << endl;
    while (k == 1)
    {
        cout << "\n-------------------- MAIN MENU --------------------\n";
        cout << "\n 1) ATP\n 2) OTE\n 3) DMI\n 4) EXIT\n";
        cout << "\n Enter your choice: \t";
        cin >> a;
        logfile(__LINE__, "main", a);
        if (a == 1)
        {
            logfile(__LINE__, "main", "Calling ATP()");
            ATP();
        }
        else if (a == 2)
        {
            logfile(__LINE__, "main", "Calling OTE()");
            OTE();
        }
        else if (a == 3)
        {
            logfile(__LINE__, "main", "Calling OTE()");
            DMIT();
        }
        else
        {
            logfile(__LINE__, "main", "Break()");
            system("Pause");
            break;
        }
        cout << "\n Do you wish to continue?? \n";
        cout << "\n 1) Continue\n 2) Exit\n\n";
        cin >> k;
        logfile(__LINE__, "main", "Continue the 1.Process or 2.End");
        logfile(__LINE__, "main", k);
    }
    logfile(__LINE__, "main", "Exit()");
    file.close();
    return 0;
}