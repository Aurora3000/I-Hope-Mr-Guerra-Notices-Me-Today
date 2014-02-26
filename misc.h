//Collin Leonheart, Kavan Mally, Mitchell Leng
#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <cstdlib>
#include <windows.h>
using namespace std;

class misc
{
public:
    string makeString(char*);
};

string misc::makeString(char* temp)
{
    string sTemp = "";
    for (unsigned int x = 0; x < strlen(temp); x++)
    {
        if (temp[x] != '\0')
            sTemp += temp[x];
        else
            break;
    }
    return sTemp;
}

#endif
