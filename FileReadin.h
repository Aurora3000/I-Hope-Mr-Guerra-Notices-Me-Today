//Collin Leonheart, Kavan Mally, Mitchell Leng
#ifndef FILEREADIN_H_INCLUDED
#define FILEREADIN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <array>
using namespace std;

class FileReadin
{
public:
    FileReadin(char*);
    string getLastName();
    string getFirstName();
    string getGrade();
    string getClassName(int);
    string getClassGrade(int);
    string getData(char*);
    int numClasses;
private:
    string LastName = "";
    string FirstName = "";
    string Grade = "";
    vector<string> ClassGrade;
	int pos=0;
	int gradePos = 0;
	vector<string> classes;
	char temp[21];
};

FileReadin::FileReadin(char* x)
{
	LastName = getData(x);
	FirstName = getData(x);
    Grade = getData(x);
    numClasses = atoi(getData(x).c_str());
    classes.assign(numClasses, "");
    ClassGrade.assign(numClasses, "");
    for(int c = 0; c < numClasses; c++)
    {
        classes.at(c) = getData(x);
        ClassGrade.at(c) = getData(x);
        cout << classes.at(c) << " " << ClassGrade.at(c) << endl;
    }
}

string FileReadin::getData(char* x)
{
    string y = "";
	for(int i=pos;i<300;i++)
    {
		pos=i;
		if(x[i]!='$')
			y+=x[i];
        else
        {
            pos=i+1;
            break;
        }
	}
	return y;
}
string FileReadin::getClassName(int x){return classes.at(x);}
string FileReadin::getClassGrade(int x){return ClassGrade.at(x);}
string FileReadin::getLastName(){return LastName;}
string FileReadin::getFirstName(){return FirstName;}
string FileReadin::getGrade(){return Grade.c_str();}

#endif
