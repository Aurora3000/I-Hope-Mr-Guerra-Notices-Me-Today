#ifndef A_H_INCLUDED
#define A_H_INCLUDED

#include <cstdlib>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class A
{
public:
    A(int);
    void add(string);
    void addG(string, string);
    void rem();
    void edit(string);
    void editG(string, string);
    string getFGrade();
    string get(int);
    string getG(int);
    string totGra();
    vector<int> getT();
    vector<int> getP();
    int getSize();
    int lbPos = 0;
private:
    int dataLength = 0;
    vector<string> assignments;
    vector<int> gTot, gPoss;
};

A::A(int len)
{
    dataLength = len;
}

void A::addG(string poss, string tot)
{
    int t = atoi(tot.c_str());
    int p = atoi(poss.c_str());
    gTot.emplace_back(t);
    gPoss.emplace_back(p);
}

void A::add(string a)
{
    assignments.emplace_back(a);
}

void A::rem()
{
    string temp = assignments.at(lbPos);
    vector<string>::iterator aPos = find(assignments.begin(), assignments.end(), temp);
    assignments.erase(aPos);
    vector<int>::iterator gPos = find(gTot.begin(), gTot.end(), gTot.at(lbPos));
    gTot.erase(gPos);
    gPos = find(gPoss.begin(), gPoss.end(), gPoss.at(lbPos));
    gPoss.erase(gPos);
}

void A::edit(string a)
{
    assignments.at(lbPos) = a;
}

void A::editG(string a, string b)
{
    int t = atoi(b.c_str());
    int p = atoi(a.c_str());
    gTot.at(lbPos) = t;
    gPoss.at(lbPos) = p;
}

string A::getG(int x)
{
    string tempS = "Points: " + to_string(gTot[x]) + "/" + to_string(gPoss[x]);
    return tempS;
}

string A::totGra()
{
    int totTot = 0;
    int totPoss = 0;
    int p = 0;
    for (unsigned int x = 0; x < gTot.size(); x++)
    {
        totTot += gTot.at(x);
        totPoss += gPoss.at(x);
    }
    if (totPoss!=0)
        p = ceil((double)totTot/(double)totPoss*100.0);
    return "Total: " + to_string(totTot) + "/" + to_string(totPoss) + " = " + to_string(p) + "%";
}

string A::getFGrade()
{
    int totTot = 0;
    int totPoss = 0;
    for (unsigned int x = 0; x < gTot.size(); x++)
    {
        totTot += gTot.at(x);
        totPoss += gPoss.at(x);
    }
    int p = ceil((double)totTot/(double)totPoss*100.0);
    return to_string(p);
}

int A::getSize(){return assignments.size();}
string A::get(int x){return assignments.at(x);}
vector<int> A::getT(){return gTot;}
vector<int> A::getP(){return gPoss;}

#endif
