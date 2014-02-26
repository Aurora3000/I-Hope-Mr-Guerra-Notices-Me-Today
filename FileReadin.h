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
    string getNext(char*);
    bool nlCheck(char*);
    bool endCheck(char*);
    int getLen();
    int numClasses;
private:
    string getData(char*);
    string LastName = "";
    string FirstName = "";
    string Grade = "";
    vector<string> ClassGrade;
	int pos=0;
	int finalPos = 0;
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
    }
    finalPos = pos;
}

string FileReadin::getData(char* x)
{
    string y = "";
	for(int i=pos;i<300;i++)
    {
		pos=i;
		if(x[i]!='$' && x[i]!='\n' && x[i]!='^')
			y+=x[i];
        else
        {
            pos=i+1;
            break;
        }
	}
	return y;
}

bool FileReadin::nlCheck(char* x)
{
    if (x[pos - 1] == '\n')
        return true;
    else
        return false;
}

bool FileReadin::endCheck(char* x)
{
    if (x[pos - 1] == '^')
        return true;
    else
        return false;
}

string FileReadin::getNext(char* x){return getData(x);}
int FileReadin::getLen(){return finalPos;}
string FileReadin::getClassName(int x){return classes.at(x);}
string FileReadin::getClassGrade(int x){return ClassGrade.at(x);}
string FileReadin::getLastName(){return LastName;}
string FileReadin::getFirstName(){return FirstName;}
string FileReadin::getGrade(){return Grade.c_str();}

#endif
