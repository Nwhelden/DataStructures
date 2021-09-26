#define MAXNUMVERTICES 100
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
#include <utility>
using namespace std;

class Graph
{
private:
    int theGraph[MAXNUMVERTICES][MAXNUMVERTICES] = { 0 };
    set<int> vertices;

public:
    void insertEdge(int from, int to, int weight);
    void insertVertex(int x);
    vector<int> getAdjacent(int vertex);
    int primSource();
    void primMST();
    // Feel free to add more methods to the API
};

void Graph::insertEdge(int from, int to, int weight)
{
    this->theGraph[to][from] = weight;
    this->theGraph[from][to] = weight;
}

void Graph::insertVertex(int x)
{
    this->vertices.insert(x);
}

vector<int> Graph::getAdjacent(int vertex) {

    vector<int> adjVerticies;

    for (int i = 0; i < MAXNUMVERTICES; i++) {

        if (theGraph[vertex][i] != 0) {

            adjVerticies.push_back(i);

        }

    }

    return adjVerticies;

}

int Graph::primSource() {

    int smallestWeight = 1000;
    int source = 0;

    //goes through the entire adjacency matrix and finds the smallest edge
    //source will the vertex with the smallest label connected to the smallest edge
    for (int i = 0; i < MAXNUMVERTICES; i++) {

        for (int j = 0; j < MAXNUMVERTICES; j++) {

            int weight = theGraph[i][j];

            //if weight is smaller than the current smallest, change 
            if ((smallestWeight > weight) && (weight != 0)) {

                smallestWeight = weight;
                source = i;

            }

            //if we find two verticies that have an edge of the same weight, we want the smallest vertex label
            else if ((smallestWeight == weight) && (weight != 0)) {

                if (source > i) {

                    source = i;

                }

            }

        }

    }

    return source;

}

void Graph::primMST()
{

    vector<pair<int, int>> MST;
    unordered_set<int> visited; //S
    set<int> remaining = vertices; //V - S
    int source = primSource();

    visited.insert(source);
    remaining.erase(source);

    //each iteration of the while loop adds a new vector to visited
    while (!remaining.empty()) {

        int tempWeight = 1000;
        int tempVertex = -1;
        int x;

        //j = source
        for (int j : visited) {

            vector<int> adjVerticies = getAdjacent(j);

            for (int i = 0; i < adjVerticies.size(); i++) {

                if (theGraph[j][adjVerticies[i]] <= tempWeight && remaining.count(adjVerticies[i]) == 1) {

                    if () {


                    }

                    x = j;
                    tempWeight = theGraph[j][adjVerticies[i]];
                    tempVertex = adjVerticies[i];

                }

            }

        }

        MST.push_back(make_pair(x, tempVertex));
        remaining.erase(tempVertex);
        visited.insert(tempVertex);

    }

    for (auto iter = MST.begin(); iter != MST.end(); iter++) {

        cout << iter->first << " " << iter->second << endl;

    }
}

/*
        //temporary map that stores all the possible edges in an iteration
        //left int: the weights of the edges to a vertex connected to source
        //left int in pair: the source vertex the edge is from
        //right vector in pair: the verticies that share an edge with the weight (in the case more than one edge shares the same weight)
        map<int, map<int, vector<int>>> weights;

        //trying to find a valid edge for the minimum spanning tree that has the smallest possible weight, 
        //then add the vertex that shares the edge with source to computed
        //outer loop goes through every vertex that has been visited
        for (auto iter1 = visited.begin(); iter1 != visited.end(); iter1++) {

            source = *iter1;
            vector<int> adjVerticies = getAdjacent(source);

            for (int i = 0; i < adjVerticies.size(); i++) {

                int vertexTo = adjVerticies[i];
                int weight = theGraph[source][vertexTo];

                //possible verticies we can add only include those that have not already been visited
                if (visited.find(vertexTo) == visited.end()) {

                    weights[weight][source].push_back(vertexTo);

                }

            }

        }

        //because of how the map is structured, the first key is the smallest weight, the first subkey is the source vertex we are
        //visiting, and the first entry in vector mapped to that subkey is the vertex we add 
        //(vertex we add has the smallest label of those possible)
        vector<int> possibleVerticies = weights.begin()->second.begin()->second;
        sort(possibleVerticies.begin(), possibleVerticies.end());
        int vertexFrom = weights.begin()->second.begin()->first;
        int vertexTo = possibleVerticies[0];

        //prints source/vertexFrom we are visitng, then the vertex we are connecting to and adds that to the visited set
        //removes vertex we are connecting to from the V-S (remaining) set to prevent an infinite loop
        cout << vertexFrom << " " << vertexTo << endl;
        visited.insert(vertexTo);
        remaining.erase(vertexTo);
        */

int main()
{
    Graph* myGraph = new Graph();
    int numEdges, inVert, outVert, wt;
    std::cin >> numEdges;
    for (int i = 0; i < numEdges; i++)
    {
        std::cin >> inVert;
        std::cin >> outVert;
        std::cin >> wt;
        myGraph->insertEdge(inVert, outVert, wt);
        myGraph->insertVertex(inVert);
        myGraph->insertVertex(outVert);
    }
    myGraph->primMST();
}





/*
//inner loop goes through 
for (auto iter2 = remaining.begin(); iter2 != remaining.end(); iter2++) {

    int weight = theGraph[source][*iter2];

    //
    if (computed.find(*iter2) == computed.end()) {

        //smallestWeight > weight
        if (weight != 0) {

            weights[weight] = *iter2;
            //smallestWeight = weight;
            //sourceTo = i;

            cout << "added" << endl;

        }

    }

}
*/

/*
if (vertexFrom > vertexTo) {

    int temp = vertexFrom;
    vertexFrom = vertexTo;
    vertexTo = temp;

    visited.insert(vertexFrom);
    remaining.erase(vertexFrom);

}
else {

    visited.insert(vertexTo);
    remaining.erase(vertexTo);

}
*/