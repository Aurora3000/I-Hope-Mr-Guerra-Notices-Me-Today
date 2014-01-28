#ifndef FILEREADIN_H_INCLUDED
#define FILEREADIN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <array>
using namespace std;

class FileReadin
{
public:
    FileReadin(char*, int);
    string getLastName();
    string getFirstName();
    string getGrade();
    string getData(char*);
    int getClassName(int);
    int getClassGrade(int);
    int numClasses;
private:
    string LastName = "";
    string FirstName = "";
    string Grade = "";
    vector<int> ClassGrade;
	int pos=0;
	int gradePos = 0;
	vector<string> classes;
};

FileReadin::FileReadin(char* x, int temp)
{
    numClasses = temp;
    classes.assign(numClasses, "");
    ClassGrade.assign(numClasses, 0);
	LastName = getData(x);
	FirstName = getData(x);
    Grade = getData(x);
    for(int c = 0; c < numClasses; c++)
    {
        classes.at(c) = getData(x);
        ClassGrade.at(c) = atoi(getData(x).c_str());
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

string FileReadin::getLastName(){return LastName;}
string FileReadin::getFirstName(){return FirstName;}
string FileReadin::getGrade(){return Grade.c_str();}

#endif
