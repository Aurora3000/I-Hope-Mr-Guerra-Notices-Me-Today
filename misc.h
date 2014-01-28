//Collin Leonheart, Kavan Mally, Mitchell Leng
#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <cstdlib>
using namespace std;

class misc
{
public:
    string makeString(char*);
};

string misc::makeString(char* temp)
{
    string sTemp = "";
    for (int x = 0; x < 30; x++)
    {
        if (temp[x] != '\0')
            sTemp += temp[x];
        else
            break;
    }
    return sTemp;
}

#endif // MISC_H_INCLUDED
