#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <filesystem>
#include <ctime>
#include <istream>
#include <iterator>
using namespace std;
int c = 0;
ofstream file;
class cParser
{
public:
	cParser(string fn); //Construtor
	~cParser(void); //destructor
private:
	void readFile(); //read .html
	void writeDane(); //write into text
	void parse(); //parse
	void abc(string tresc); //'tags
	string tag; //tag html
	int fileLength; //filename length
	string parseResult;
	string fileName; //create a .txt file
	ofstream writetoexcel; //do write into .txt file
	ofstream check;
	//string xyz[143][6];
};


/*---------------CONSTRUCTOR------------------------*/
cParser::cParser(string fn)
{
	fileName = fn;
	cout << fn;
	readFile();
	writetoexcel.open("parseResult.xls", ios::out);
	check.open("parseResult.txt", ios::out);
	check << fn << endl;
	parse();
	cout << "\n";
}
/*----------------CONSTRUCTOR - END--------------------------------*/


/*----------------DESTRUCTOR--------------------------------*/
cParser::~cParser(void)
{
}
/*----------------DESTRUCTOR - END--------------------------------*/


/*----------------READFILE--------------------------------*/
void cParser::readFile() {
	string temp = " ";
	fstream pqr;
	check << temp;
	pqr.open(fileName, ios::in);
	if (pqr.good())
	{
		getline(pqr, temp, '~');
		pqr.close();
	}
	else cout << "No file" << endl;

	tag = temp;
	check << "tag:" << tag;
	fileLength = tag.length();
	check << "length:" << fileLength;
}
/*---------------READFILE - END---------------------------------*/


/*---------------WRITEDANE---------------------------------*/
void cParser::writeDane() {
	cout << tag;
	check << tag;
}
/*---------------WRITEDANE - END---------------------------------*/


/*------------------------DATA BEING WRITTEN TO EXCEL------------------------*/
void cParser::abc(string tresc) {
	cout << endl << endl;
	cout << '\n' << "\r" << tresc << '>' << "\n" << endl;
	cout << endl << endl;

	//check << endl << endl;
	//check << '\n' << "\r" << tresc << '>' << "\n" << endl;
	//check << endl << endl;

	writetoexcel << endl;
	writetoexcel << '\n' << tresc << '>' << "\n" << endl;
	writetoexcel << endl;

}
/*-------------- -DATA BEING WRITTEN TO EXCEL- END----------------------------------*/


/*--------------PARSE----------------------------------*/
void cParser::parse()
{
	int i = 0, j = 0; //parse html tag
	//string xyz[100], pt[10];
	for (i = 0; i < fileLength; i++)
	{
		if (tag[i] == '<' && tag[i + 1] != (char)(32)) //parses the html tag
		{
			for (j = 0; tag[i] != '>'; i++, j++)
			{
				//do nothing
			}
		
			abc(tag.substr(i - j, j));
		}
		else
		{
			cout << tag[i];   // Value of the tag Block like content in the between starting and ending tag 
			writetoexcel << tag[i];
			if (tag[i] == 'P')
			{
				string a;
				int j=i;
				for (; j <= i + 5; j++)
				{
					a += tag[j];
				}
				check << a << endl;
				if (a == "PASSED")
				{
					cout << a;
				}				
			}
			if (tag[i + 1] == '<')
			{
				writetoexcel << endl;
				check << endl;
			}
		}
	}
}

/*--------------PARSE - END----------------------------------*/


int main()
{
	string fileName;
//	file.open(s, ios::out | ios::app);
	//cout << "LOGFILE" << s;
	cout << "\n========================================" << endl;
	cout << "HTML File Analyzer" << endl;
	cout << "========================================" << endl << endl;

	//logfile(__LINE__, "main", "Results.html filepath");
	cout << "Enter a .html file path : ";
	cin >> fileName;
	cout << fileName << endl;
	file.open(fileName.c_str(), ios::out | ios::app);
	//logfile(__LINE__, "main", fileName);
	
	//logfile(__LINE__, "main", "File opened");

	/*while (!file)
	 {
		 file.clear();
		 cout << endl << "Re-enter a valid filename: " << endl;
		 cin >> fileName;
		 file.open(fileName.c_str());
	 }*/

	cout << "========================================";
	cout << "Tags and Headers in the file headers of the file File";
	cout << "========================================";

	cParser obiekt(fileName.c_str());
	cout << "--------------" << endl;
	cout << "OUTPUT IS IN parseResult.xls\n";
	
	system("Pause");
	return 0;
}