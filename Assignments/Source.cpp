#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <istream>
#include <iterator>
#include <stdio.h>
#include <vector>
#include <iostream> 
#include <iterator> 
#include <map> 
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <functional>
using namespace std;
int ci = 0;

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
	file << ci << "\t" << __TIMESTAMP__ << "\t\t" << y << "\t\t\t" << x << "\t\t\t" << h << "\n"; ci++;
}


class htmltoexcel {
public:
	int x = 0;
	ofstream check;
	string input, line;
	fstream myfile;
	vector<vector<string>> myvector;
	vector<string> passed;
	vector<string> failed;
	vector<string> data;
	htmltoexcel(string fn);
private:
	string parse(char* string); 
	void intial(string fileName); 
	void chj(string line);
	string removespace(string line);
	void pass();
	void fail();
	void others();
};

/*--------------CONSTRUCTOR - START----------------------------*/
htmltoexcel::htmltoexcel(string fn)
{
	string filename = fn;
	intial(fn);
	pass();
	fail();
	others();
}
/*--------------CONSTRUCTOR- END-------------------------------*/

/*--------------INTIAL - START---------------------------------*/
void htmltoexcel::intial(string fileName)
{
	myfile.open(fileName.c_str(), ios::in | ios::app);
	logfile(__LINE__, "intial()", "Opening Results.html.");
	if (!myfile)
	{
		cout << "file cannot open!";
		logfile(__LINE__, "intial()", "Filecannot open");
	}

	while (line != "</html>")
	{
		logfile(__LINE__, "intial()", "Reading .html and Removing whitespaces in line");	
		line = removespace(line);
		logfile(__LINE__, "intial()", line);
		logfile(__LINE__, "intial()", "calling chj function()");
		chj(line);
		logfile(__LINE__, "intial()", "Line parsed, goto Next line");
		getline(myfile, line);

		if (data.size() == 6) {
			myvector.push_back(data);
			data.clear();
			logfile(__LINE__, "intial()", "one Row in table parsed");
		}
	}
}
/*--------------INTIAL - END-----------------------------------*/

/*--------------REMOVE SPACES - START--------------------------*/
string htmltoexcel::removespace(string line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	return line;
}
/*--------------REMOVE SPACES - END----------------------------*/

/*--------------CHECK TAG - START------------------------------*/
void htmltoexcel::chj(string line)
{
	char* char_arr;
	int c = 0;
	logfile(__LINE__, "chj()", "Checking for <td> tag between <tr></tr> tag");
	if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
	{
		char_arr = &line[0];
		data.push_back(parse(char_arr));
		logfile(__LINE__, "chj()", "Comment between <td></td> is retrieved");
	}
}
/*--------------CHECK TAG - END--------------------------------*/

/*--------------PARSE - START----------------------------------*/
string htmltoexcel::parse(char* string)
{
	int index = 0, in = 0;
	logfile(__LINE__, "parse()", "Removing <td></td> from line and extracting Comment");
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '<')
		{
			in = 1;
			continue;
		}
		else if (string[i] == '>')
		{
			in = 0;
			continue;
		}
		if (in == 0) {
			string[index] = string[i];
			index++;
		}
	}
	string[index] = '\0';
	logfile(__LINE__, "parse()", string);
	return string;
}
/*--------------PARSE - END------------------------------------*/

/*--------------PASSED.csv START-------------------------------*/
void htmltoexcel::pass()
{
	ofstream passed_file;
	passed_file.open("passed.csv", ios::out);
    logfile(__LINE__, "pass()", "Creating Passed.csv");
	for (int j = 0; j < myvector[0].size(); j++) {
		passed_file << myvector[0][j] << ",";
	}
	passed_file << "\n";

    //-------------------------------SORT()--------------------------------------------------
				map<string, vector<string>, greater<string>> mymap;  
				string key;
				vector<string> m;
				// Inserting the elements one by one 
				for (int i = 1; i < myvector.size(); i++) {
					key = myvector[i][0];
					for (int j = 0; j < myvector[i].size(); j++) {
					vector<string> m = myvector[i];
					}
					mymap.insert(make_pair(key, m));
				}
				
				map<string,vector<string>> :: iterator it; 

				/*for (it=mymap.begin() ; it!=mymap.end() ; it++) 
					cout << (*it).second[0] << ", " 
					<< (*it).second[1] << ", " 
					<< (*it).second[2] << ", " 
					<< (*it).second[3] << ", " 
					<< (*it).second[4] << ", " 
					<< (*it).second[5] << endl; */
					for(auto it = myvector.begin();
						it!=myvector.end(); ++it)
						cout<<" "<<*it;
	//-------------------------------SORT()--------------------------------------------------


    logfile(__LINE__, "pass()", "Status with PASSED value is checked and written to file");
	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "PASSED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				passed_file << myvector[i][j] << ",";
				
			}
			passed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : passed.csv\n";
	//sort();
	passed_file.close();
	logfile(__LINE__, "pass()", "Closing Passed.csv");
}
/*--------------PASSED.csv END---------------------------------*/

/*--------------FAILED.csv START-------------------------------*/
void htmltoexcel::fail()
{
	ofstream failed_file;
	failed_file.open("failed.csv", ios::out);
    logfile(__LINE__, "fail()", "Creating failed.csv");
	for (int j = 0; j < myvector[0].size(); j++) {
		failed_file << myvector[0][j] << ",";
	}
	failed_file << "\n";
    logfile(__LINE__, "pass()", "Status with FAILED value is checked and written to file");
	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "FAILED") {
			for (int j = 0; j < myvector[i].size(); j++) {
				failed_file << myvector[i][j] << ",";
			}
			failed_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : failed.csv\n";
	//sort();
	failed_file.close();
	logfile(__LINE__, "fail()", "Closing failed.csv");
}
/*--------------FAILED.csv END---------------------------------*/

/*--------------OTHERS.csv START-------------------------------*/
void htmltoexcel::others()
{
	ofstream others_file;
	others_file.open("Others.csv", ios::out);
	logfile(__LINE__, "others()", "Creating others.csv");
	for (int j = 0; j < myvector[0].size(); j++) {
		others_file << myvector[0][j] << ",";
	}
	others_file << "\n";
    logfile(__LINE__, "others()", "Status with Aborted or Others value is checked and written to file");
	for (int i = 1; i < myvector.size(); i++) {

		if (myvector[i][1] == "OTHERS") {
			for (int j = 0; j < myvector[i].size(); j++) {
				others_file << myvector[i][j] << ",";
			}
			others_file << "\n";
		}
	}
	cout << "--------------" << endl;
	cout << "\n OUTPUT : Others.csv\n";
	//sort();
	others_file.close();
	logfile(__LINE__, "others()", "Closing others.csv");
}
/*--------------OTHERS.csv END---------------------------------*/

/*--------------MAIN - START-----------------------------------*/
int main()
{
	string fileName = "Results.html";
	file.open(s, ios::out | ios::app);
	htmltoexcel abc(fileName);
	system("Pause");
	return 0;
}
/*--------------MAIN -END--------------------------------------*/
