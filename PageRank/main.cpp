#include <iostream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;


class AdjacencyList
{
private:
    //adjacency list representing the graph
    //map: key represents 'from' vertex, vector value of a key represents the adjacent 'to' verticies
    //ex: A -> <B, C, D, ...> (verticies adjacent to A)
    map<string, vector<string>> graph;

    //map keeps track of how many verticies are in the graph, and stores the outdegree and rank of each vertex
    //map entries are ordered on insertion, and duplicates are never stored
    //first element of pair = rank, second element = outdegree 
    map<string, pair<double, int>> verticies;

public:
    void insertEdge(string from, string to) {

        //if 'from' or 'to' vertex are being added for the first time, their keys are added to the verticies map
        //map, so if 'from' and 'to' already exist, a new key is not added (operator[] only creates a new key if it is unique)
        verticies[from];
        verticies[to];

        //if to vertex is being directed to for the first time, add it to the adjacency list
        //handles case if we have a vertex in a graph that has no outward edges, but only has inward edges (we still need to be able 
        //to print it when printing hte entire graph)
        //no edge coming from it; it's only being directed to
        if (graph.find(to) == graph.end()) {

            //??? why include this
            //??? need for conditional
            //?? why set it to empty? is vector not initialized
            //need conditional, or else for each insertion the vector of vertex 'to' is reset as empty (case: 'to' vertex becomes 'from')
            graph[to] = {};

        }

        //inserts 'from' key to the map, and pushes the specified 'to' vertex and corresponding weight to the vector of that key's
        //map, so duplicates are not added 
        graph[from].push_back(to);

        //increments outdegree of 'from,' since it's being directed to a new vertex (new edge being added)
        verticies[from].second++;

    }

    void printPageRank() {

        //prints each vertex and its associated rank
        for (auto it = verticies.begin(); it != verticies.end(); it++) {

            cout << fixed << setprecision(2) << it->first << " " << it->second.first << endl;

        }

    }

    //prints the webpage name and page rank of all pages after p power iterations in ascending alphebetical order 
    void pageRank(int n) {

        double size = verticies.size();

        //initialize all the ranks as 1/|V|
        for (auto it = verticies.begin(); it != verticies.end(); it++) {

            it->second.first = 1 / size;

        }

        //for loop iterates for each power iteration
        //if page rank is 1, just return the initialized ranks of 1/|V|
        for (int i = 1; i < n; i++) {

            //temporary map that stores the updated ranks of the verticies
            //new map made for each power iteration, temporary ranks start out as 0 to allow for calculations of updated ranks
            //updated ranks of a vertex are not based on the vertex's previous rank, only the previous ranks of the veritices pointing
            //to it
            map<string, double> temp;

            //fills temporary map
            //for loop iterates through each vertex in the adjacency list
            for (auto it = graph.begin(); it != graph.end(); it++) {

                //retrieves the verticies adjacent to the current 'from' vertex in the map
                vector<string> adjVerticies = graph[it->first];

                //for each vertex adjacent to the current 'from' vertex, add fromRank / fromOutdegree to their rank
                for (int j = 0; j < adjVerticies.size(); j++) {

                    //rank of a vertex is the total of rank/outdegree for each 'from' vertex directed to it
                    //it->first represents the current 'from' vertex, adjVerticies[i] represents the current 'to' vertex
                    //second element of verticies container is a pair containing first(rank) and second(outdegree)
                    double fromRank = verticies[it->first].first;
                    int fromOutdegree = verticies[it->first].second;
                    temp[adjVerticies[j]] += fromRank / fromOutdegree;

                }

            }

            //once new ranks are calculated, update the container for the current (not temp) ranks
            for (auto it = verticies.begin(); it != verticies.end(); it++) {

                //it->second accesses the pair in verticies, where first is the old rank
                //it->first acceses the key, which maps to the new rank in temp
                it->second.first = temp[it->first];

            }

        }

        printPageRank();

    }

};

int main()
{

    int numLines, powerIterations;
    string from, to;
    cin >> numLines;
    cin >> powerIterations;
    AdjacencyList adjList;

    //fills graph with edges
    for (int i = 0; i < numLines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        adjList.insertEdge(from, to);

    }

    //calculates the ranks of each vertex based on the number of power iterations then prints
    adjList.pageRank(powerIterations);
    
}