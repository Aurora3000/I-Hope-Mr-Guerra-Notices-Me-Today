#ifndef SAVEFILE_H_INCLUDED
#define SAVEFILE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "A.h"
using namespace std;

class SaveFile
{
public:
    SaveFile(string, string, string, int, vector<string>&, vector<string>&, vector<A>&);
    string makeData();
    bool checkFileName(char*);
    string makeFileName(char*);
private:
    string LastName = "";
    string FirstName = "";
    string Grade = "";
    string numClasses = "";
    vector<string> grades, classes, names;
    vector<A> asmnt;
    void asmntSizeCheck(string&, unsigned int);
};
SaveFile::SaveFile(string fName, string lName, string grade, int temp, vector<string>& Classes, vector<string>& Grades, vector<A>& asmnts)
{
    FirstName = fName;
    LastName = lName;
    Grade = grade;
    numClasses = to_string(temp);
    classes = Classes;
    grades = Grades;
    asmnt = asmnts;
}

string SaveFile::makeData()
{
    string data = LastName + "$" + FirstName + "$" + Grade + "$" + numClasses + "$";
    for (unsigned int x = 0; x < classes.size(); x++)
    {
        data += classes.at(x) + "$" + grades.at(x);
        if (x == classes.size()-1)
            data += "\n";
        else
            data += "$";
    }
    for (unsigned int x = 0; x < asmnt.size(); x++)
    {
        vector<int> gT = asmnt.at(x).getT();
        vector<int> gP = asmnt.at(x).getP();
        if (asmnt.at(x).getSize()==0)
            asmntSizeCheck(data, x);
        for (int xx = 0; xx < asmnt.at(x).getSize(); xx++)
        {
            if (asmnt.at(x).getSize() == 0 && x == asmnt.size()-1)
            {
                data += "^";
                break;
            }
            else if (asmnt.at(x).getSize() == 0)
            {
                data += "\n";
                break;
            }
            data += asmnt.at(x).get(xx) + "$" + to_string(gT.at(xx)) + "$" + to_string(gP.at(xx));
            if (xx == asmnt.at(x).getSize()-1 && x == asmnt.size()-1)
                data += "^";
            else if (xx == asmnt.at(x).getSize()-1)
                data += "\n";
            else
                data += "$";
        }
    }
    return data;
}

bool SaveFile::checkFileName(char* szFile)
{
    if (szFile[strlen(szFile)-4]=='.')
        return true;
    else
        return false;
}

string SaveFile::makeFileName(char* szFile)
{
    string sTemp = "";
    for (unsigned int x = 0; x < strlen(szFile); x++)
    {
        if (szFile[x] != '\0')
            sTemp += szFile[x];
        else
            break;
    }
    sTemp += ".aur";
    return sTemp;
}

void SaveFile::asmntSizeCheck(string& data, unsigned int pos)
{
    if (pos == asmnt.size()-1)
        data += "placeholder$0$0^";
    else
        data += "placeholder$0$0\n";
}

#endif
