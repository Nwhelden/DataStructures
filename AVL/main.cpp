#include "BST.h"
#include "TvSeries.h"
#include <fstream>

int main() {

    string line;
    string show;
    string tconst, name, sYear, eYear, genres;
    BST tree;
    BST::Node* root = tree.getRoot();
    ifstream file("shows.txt");
    int i = 0;
    int quarter = 146350 / 4;
    int math = 0;
    int percentage = 0;
    if (file.is_open())
    {
        getline(file, line);
        while (getline(file, line, '\t'))
        {
            if (i == math)
            {
                cout << "Loading file " << percentage << "%..." << endl;
                percentage += 25;
                math += quarter;
            }
            tconst = line;
            getline(file, line, '\t');
            name = line;
            getline(file, line, '\t');
            sYear = line;
            getline(file, line, '\t');
            eYear = line;
            getline(file, line);
            genres = line;
            TvSeries test(tconst, name, sYear, eYear, genres);
            root = tree.insert(root, test);
            i++;
        }
    }
    file.close();
    cout << "What show would you like to look for?" << endl;
    getline(cin, show);
    tree.search(root, show)->value.Print();

	return 0;

}