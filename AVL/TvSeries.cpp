#include "TvSeries.h"

TvSeries::TvSeries()
{
    string tconst = "";
    string name = "";
    string startYear = "";
    string endYear = "";
    string genres = "";
}

TvSeries::TvSeries(string tconst, string name, string starYear, string endYear, string genres)
{
    this->tconst = tconst;
    this->name = name;
    this->startYear = startYear;
    this->endYear = endYear;
    this->genres = genres;
}

void TvSeries::Print()
{
    if (tconst == "")
    {
        cout << "Show not available" << endl;
        return;
    }
    cout << "tConst = " << tconst << endl;
    cout << "Name = " << name << endl;
    cout << "Start Year = ";
    if (endYear != "\\N")
    {
        cout << (stoi(endYear) - 10) + (rand() % (stoi(endYear) - 1990 + 1)) << endl;
        cout << "End Year = " << endYear << endl;
    }
    else
        cout << 1990 + (std::rand() % (2018 - 1990 + 1)) << endl;
    cout << "End Year = Not Available" << endl;
    if (genres != "\\N")
    {
        cout << "Genres = ";
        for (unsigned int i = 0; i < genres.size(); i++)
        {
            if (genres[i] != '\"' && genres[i] != ',')
                cout << genres[i];
            if (genres[i] == ',')
                cout << ", ";
        }
        cout << "." << endl;
    }
    else
        cout << "Not Available";
    cout << "-----------------------------------------" << endl;
}
