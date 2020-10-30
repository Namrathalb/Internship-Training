#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
//#include <filesystem>
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
	//void sort();
};

/*--------------CONSTRUCTOR - START----------------------------*/
htmltoexcel::htmltoexcel(string fn)
{
	string filename = fn;
	intial(fn);
	pass();
	fail();
	others();
	//sort();
}
/*--------------CONSTRUCTOR- END-------------------------------*/

/*void htmltoexcel::sort() 
{
   // vector<vector<string>> date;
	vector<string> v;
    ifstream in("passed.csv");
    if(!in)
        cout << "File not found" << endl;

    string line, sector;
    while(getline(in, line)) 
    {       
	   for(int i=1;i<myvector.size();i++)
            v.push_back(myvector[i][0]);  
    //  date.push_back(myvector); 
    }

    auto sortproc = [](const vector<string> &a, const vector<string> &b)
    {
        return a[0] > b[0];
    };

    std::sort(v.begin(), v.end(), sortproc);
    cout << "sorted:\n";
    for(auto &col : v)
    {
        //for(auto &e : col)
            cout << col << "\n";
    }
}*/

/*--------------INTIAL - START---------------------------------*/
void htmltoexcel::intial(string fileName)
{
	myfile.open(fileName.c_str(), ios::in | ios::app);
	if (!myfile)
	{
		cout << "file cannot open!";
	}

	while (line != "</html>")
	{
		line = removespace(line);
		chj(line);
		getline(myfile, line);

		if (data.size() == 6) {
			myvector.push_back(data);
			data.clear();
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
	if ((line.find("<tr>") > line.length()) && (line.find("</tr>") > line.length()) && (line.find("<td>") < line.length()))
	{
		char_arr = &line[0];
		data.push_back(parse(char_arr));
	}
}
/*--------------CHECK TAG - END--------------------------------*/

/*--------------PARSE - START----------------------------------*/
string htmltoexcel::parse(char* string)
{
	int index = 0, in = 0;
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
	return string;
}
/*--------------PARSE - END------------------------------------*/
bool sortcol( const vector<string>& v1, 
   const vector<string>& v2 ) { 
return v1[1] < v2[1]; 
}
/*--------------PASSED.csv START-------------------------------*/
void htmltoexcel::pass()
{
	ofstream passed_file;
	passed_file.open("passed.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		passed_file << myvector[0][j] << ",";
	}
	passed_file << "\n";

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

    for (it=mymap.begin() ; it!=mymap.end() ; it++) 
        cout << (*it).second[0] << ", " 
		<< (*it).second[1] << ", " 
		<< (*it).second[2] << ", " 
		<< (*it).second[3] << ", " 
		<< (*it).second[4] << ", " 
		<< (*it).second[5] << endl; 

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
}
/*--------------PASSED.csv END---------------------------------*/

/*--------------FAILED.csv START-------------------------------*/
void htmltoexcel::fail()
{
	ofstream failed_file;
	failed_file.open("failed.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		failed_file << myvector[0][j] << ",";
	}
	failed_file << "\n";

	vector<pair<string, vector<string>>> vec;
	for (int i = 1; i < myvector.size(); i++) {
		string key = myvector[i][0];
		vector<string> value = myvector[i];
        vec.push_back(make_pair(key, value));
	}

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
}
/*--------------FAILED.csv END---------------------------------*/

/*--------------OTHERS.csv START-------------------------------*/
void htmltoexcel::others()
{
	ofstream others_file;
	others_file.open("Others.csv", ios::out);

	for (int j = 0; j < myvector[0].size(); j++) {
		others_file << myvector[0][j] << ",";
	}
	others_file << "\n";

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
}
/*--------------OTHERS.csv END---------------------------------*/

/*--------------MAIN - START-----------------------------------*/
int main()
{
	string fileName = "Results.html";
	htmltoexcel abc(fileName);
	system("Pause");
	return 0;
}
/*--------------MAIN -END--------------------------------------*/
