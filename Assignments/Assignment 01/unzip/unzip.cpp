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


/*#ifndef DEBUG
#error Only Debug builds are supported
#endif*/

using namespace std;
int c = 0;
char character = 'A';

typedef vector <string> stringvec;
typedef map <string, string> stringmap;
typedef unordered_set <string> stringset;
stringset::iterator itr;
string src, dst, fname, vno;

string checkatp(string vno);
string checkote(string vno);
string checkdmi(string vno);
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

string checkatp(string vno)
{
    if (vno == "4.9.0" || "4.9.1" || "4.9.3" || "4.9.4" || "4.10.0" )
       return "P8cMR8_OTE_Tester_" + vno;
   else if (vno == "5.0.94" || "5.0.95" || "5.0.96" || "5.0.97" || "5.0.98")
       return "P8e_OTE_Tester_" + vno;
}

string checkote(string vno)
{
    if (vno == "5.12.1")
        return "2020-09-15-v" + vno;
    else if (vno == "5.12.0")
        return "2020-09-04-v" + vno;
    else if (vno == "5.11.20")
        return "2020-08-18-v" + vno;
    else if (vno == "5.11.19")
        return "2020-07-01-v" + vno;
    else if (vno == "5.11.18")
        return "2020-06-18-v" + vno;
    else if (vno == "5.11.17")
        return "2020-05-20-v" + vno;
    else if (vno == "5.11.16")
        return "2020-05-06-v" + vno;
    else if (vno == "5.11.15")
        return "2020-04-22-v" + vno;
    else if (vno == "5.11.14")
        return "2020-02-14-v" + vno;
    else if (vno == "5.11.13")
        return "2020-01-30-v" + vno;
    else if (vno == "5.11.12")
        return "2020-01-15-v" + vno;
}

string checkdmi(string vno)
{
    return "DMIApp_" + vno;
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
    string xyz = dst + "\\" + fname;
    string pqr = "DMIApp";
    pqr.append(&character);
    cout << "\n" << pqr << "\n";
    character++;
    //Renaming the unzip folder to New name and performing same when next file is extracted as subsequent DMIAppA, DMIAppB

    int result = rename(xyz.c_str(), pqr.c_str());
    if (result == 0)
        cout << "\n File Rename Success\n";
    else
        cout << "\n File Rename Failure\n";
}

void rem(string dst, string fname)
{
    string xyz = dst + "\\" + fname + "\\" + "AnyDesk.exe";
    cout << "\n To copy .exe Source path is : " << xyz << "\n";
    string w = "move " + xyz + " " + dst;
    cout << "\n" << w << "\n";
    // perform File moving operation by copying .exe file to OTE_tester Folder

    if (system(w.c_str()))
        cout << "\n Moving File was Failed\n";
    else
        cout << "\n Moving File was Success\n";

    string m = "Rmdir " + dst + "\\" + fname;
    cout << "\n" << m << "\n";
    // performing Remove directory for the empty folder once the .exe is copied

    if (system(m.c_str()))
        cout << "\n Remove Directory Failure\n";
    else
        cout << "\n Remove Directory Success\n";
    cout << "\n ---------------------Ending OTE---------------------\n";
}

void rep(string dst, string fname)
{
    string xyz = dst + "\\" + fname;
    string pqr = "OTE_Tester";
    //Perform File name for the unzip folder

    int result = rename(xyz.c_str(), pqr.c_str());
    if (result == 0)
        cout << "\n File Rename Success\n" << "\n" << "New Unzipped Folder name : " << pqr << "\n";
    else
        cout << "\n File Rename Failed\n";
    cout << "\n ---------------------Ending ATP---------------------\n";
}

void ATP()
{
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "ATP Running" << "\n" << endl; c++;
    cout << "\n ---------------------Starting ATP---------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << src << "\n" << endl; c++;
    // take source file path 

    cout << "\n Files in the directory : \n";
    stringset currentFiles;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING read_directory() FUNCTION" << "\n" << endl; c++;
    read_directory(src, currentFiles);
    //Read and Display files in the source

    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING displayfiles() FUNCTION" << "\n" << endl; c++;
    displayFiles(currentFiles);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING system(pause) FUNCTION" << "\n" << endl; c++;
    system("pause");
    // wait for few seconds and press any key to continue

    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space
    fname = checkatp(vno);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << fname << "\n" << endl; c++;

    string res = src + "\\" + fname + ".zip";
    cout << "\n Final Source File path is : " << res << "\n";
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << res << "\n" << endl; c++;
    // add .zip to file name and append it to source file path

    cout << "\n Enter the Destination location: ";
    cin >> dst;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << dst << "\n" << endl; c++;
    //take the destination path

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING FUNCTION Unzip(src, dst)" << "\n" << endl; c++;
    const char* p = res.c_str();
    const char* q = dst.c_str();
    Unzip(p, q);
    //convert the source and destination file path to const char * and send it as parameters to Unzip Funtion.
    rep(dst, fname);
};

void OTE()
{
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "OTE Running" << "\n" << endl; c++;
    cout << "\n ---------------------Starting OTE---------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << src << "\n" << endl; c++;
    //take source file path 

    cout << "\n Files in the directory :- \n";
    stringset currentFiles;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING read_directory() FUNCTION" << "\n" << endl; c++;
    read_directory(src, currentFiles);
    //Read and Display files in the source

    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING displayfiles() FUNCTION" << "\n" << endl; c++;
    displayFiles(currentFiles);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING system(pause) FUNCTION" << "\n" << endl; c++;
    system("pause");
    //wait for few seconds and press any key to continue

    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space
    
    fname = checkote(vno);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << fname << "\n" << endl; c++;

    string res = src + "\\" + fname + ".zip";
    cout << "Final Source File path is : " << res << "\n";
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << res << "\n" << endl; c++;
    //add .zip to file name and append it to source file path

    cout << "\nEnter the Destination location: ";
    cin >> dst;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << dst << "\n" << endl; c++;
    //take the destination path

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING FUNCTION Unzip(src, dst)" << "\n" << endl; c++;
    const char* p = res.c_str();
    const char* q = dst.c_str();
    Unzip(p, q);
    //convert the source and destination file path to const char * and send it as parameters to Unzip Funtion.
    rem(dst, fname);
}

void DMIT()
{
    // file.open(s, ios::out | ios::app);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "DMI Running" << "\n" << endl; c++;
    cout << "\n ------------------Starting DMI------------------\n";
    cout << "\n Enter the Source File Directory : ";
    cin >> src;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << src << "\n" << endl; c++;
    // take source file path

    cout << "\n Files in the directory :- \n";
    stringset currentFiles;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING read_directory() FUNCTION" << "\n" << endl; c++;
    read_directory(src, currentFiles);
    //Read and Display files in the source

    for (itr = currentFiles.begin(); itr != currentFiles.end(); itr++)
    {
        string str = *itr;
        std::size_t index = str.find(".");
        if (index > str.length())
            currentFiles.erase(itr--);
    }

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING displayfiles() FUNCTION" << "\n" << endl; c++;
    displayFiles(currentFiles);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING system(pause) FUNCTION" << "\n" << endl; c++;
    system("pause");
    // wait for few seconds and press any key to continue

    cout << "\n\n Enter Version number :\t";
    cin >> vno; //Enter the version without any extension and space
    fname = checkdmi(vno);
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << fname << "\n" << endl; c++;

    string res = src + "\\" + fname + ".zip";
    cout << "\n Final Source File path is : " << res << "\n";
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << res << "\n" << endl; c++;
    // add .zip to file name and append it to source file path

    cout << "\n Enter the Destination location: ";
    cin >> dst;
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << dst << "\n" << endl; c++;
    //take the destination path

    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING FUNCTION Unzip(src, dst)" << "\n" << endl; c++;
    const char* p = res.c_str();
    const char* q = dst.c_str();
    Unzip(p, q);
    //convert the source and destination file path to const char * and send it as parameters to Unzip Funtion.
    ren(dst, fname);
    Unzip(p, q);
    ren(dst, fname);
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
                FolderItems* fi = (FolderItems*)malloc(sizeof(FolderItems*));
               // if (pFromFolder == nullptr) throw exception("read access violation");
                pFromFolder->Items(&fi);
                VariantInit(&vOpt);
                vOpt.vt = VT_I4;
                vOpt.lVal = FOF_NO_UI;  //4; // Do not display a progress dialog box  
                VARIANT newV;           // Creating a new Variant with pointer to FolderItems to be copied
                VariantInit(&newV);
                newV.vt = VT_DISPATCH;
                newV.pdispVal = fi;
               // if (pToFolder == NULL)
                hResult = pToFolder->CopyHere(newV, vOpt);
                //if (pFromFolder != NULL)
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
    file << "Sl.No" << "\t" << "TIMESTAMP" << "\t" << "LINE NUMBER" << "\t" << "FUNCTION NAME" << "\t" << "USER INPUT VALUE" << "\n" << endl;
    while (k == 1)
    {
        cout << "\n-------------------- MAIN MENU --------------------\n";
        cout << "\n 1) ATP\n 2) OTE\n 3) DMI\n 4) EXIT\n";
        cout << "\n Enter your choice: \t";
        cin >> a;
        file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << a << "\n" << endl; c++;

        if (a == 1)
        {
            file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING ATP()" << "\n" << endl; c++;
            ATP();
        }

        else if (a == 2)
        {
            file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING OTE()" << "\n" << endl; c++;
            OTE();
        }

        else if (a == 3)
        {
            file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "CALLING DMI()" << "\n" << endl; c++;
            DMIT();
        }

        else
        {
            file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "Break() is called" << "\n" << endl; c++;
            cout << system("dir");
            break;
        }

        cout << "\n Do you wish to continue??\n";
        cout << "\n 1) Continue\n 2) Exit\n\n";
        cin >> k;

        file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << "Continue the 1.Process or 2.End" << "\n" << endl; c++;
        file << c << "\t" << __TIMESTAMP__ << __LINE__ << "\t" << __func__ << "\t" << k << "\n" << endl; c++;
    }
    file << c << "\t" << __TIMESTAMP__ << "\t" << __LINE__ << "\t" << __func__ << "\t" << " Exited()" << "\n" << endl; c++;
    file.close();
    return 0;
}