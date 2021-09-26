#pragma once
#include <string>
#include <iostream>
using namespace std;

class TvSeries
{

public:
    string tconst;
    string name;
    string startYear;
    string endYear;
    string genres;
    TvSeries();
    TvSeries(string tconst, string name, string starYear, string endYear, string genres);
    void Print();

};

