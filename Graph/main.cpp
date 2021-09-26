#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;


class Graph
{
private:
    //how to template so it isn't a graph on int
    map<int, vector<pair<int, int>>> graph;
    vector<int> verticies;
    int numVerticies = 0;

public:
    void insertEdge(int from, int to, int weight) {

        if (numVerticies == 0) {

            graph[from] = {};
            verticies.push_back(from);
            numVerticies++;

        }
        else {

            if (graph.find(from) == graph.end()) {

                verticies.push_back(from);
                numVerticies++;

            }

            graph[from].push_back(make_pair(to, weight));

        }

        if (graph.find(to) == graph.end()) {

            graph[to] = {};
            verticies.push_back(to);
            numVerticies++;

        }

    }

    bool isEdge(int from, int to) {

        //do I need this check? will it add complexity?
        if (graph.find(from) != graph.end()) {

            int numAdjacent = graph[from].size();

            for (int i = 0; i < numAdjacent; i++) {

                if (graph[from][i].first == to) {

                    return true;

                }

            }

        }

        return false;

    }

    int getWeight(int from, int to) {

        //do I need this check? will it add complexity?
        if (graph.find(from) != graph.end()) {

            int numAdjacent = graph[from].size();

            for (int i = 0; i < numAdjacent; i++) {

                if (graph[from][i].first == to) {

                    return graph[from][i].second;
                }

            }

        }

        return 0;

    }

    vector<int> getAdjacent(int vertex) {

        vector<int> adjacent;

        //do I need this check? will it add complexity?
        if (graph.find(vertex) != graph.end()) {

            int numAdjacent = graph[vertex].size();

            for (int i = 0; i < numAdjacent; i++) {

                adjacent.push_back(graph[vertex][i].first);

            }

        }

        return adjacent;

    }

    void printGraph() {

        sort(verticies.begin(), verticies.end());
        int source = verticies[0];

        vector<int> adjacentVerticies = getAdjacent(source);
        for (int i = 0; i < adjacentVerticies.size(); i++) {

            cout << adjacentVerticies[i] << endl;

        }

        vector<int> visited;
        queue<int> q;

        //push or emplace?
        q.push(source);
        visited.push_back(source);

        while (!q.empty()) {

            int currentVertex = q.front();
            cout << currentVertex << " ";
            vector<int> adjacentVerticies = getAdjacent(currentVertex);
            q.pop();

            //how would I implement a comparison instead? would it be better?
            sort(adjacentVerticies.begin(), adjacentVerticies.end());

            for (int i = 0; i < adjacentVerticies.size(); i++) {

                auto it = find(visited.begin(), visited.end(), adjacentVerticies[i]);

                if (it != visited.end()) {

                    visited.push_back(adjacentVerticies[i]);
                    q.push(adjacentVerticies[i]);
                    cout << adjacentVerticies[i] << " ";

                }

            }

            cout << "\n" << endl;

        }



    }
};

int main()
{

    int noOfLines, operation, vertex, to, fro, weight, source, j;
    vector<int> arr;
    int arrSize;
    Graph g;
    cin >> noOfLines;
    for (int i = 0; i < noOfLines; i++)
    {
        cin >> operation;
        switch (operation)
        {
        case 1:
            cin >> fro;
            cin >> to;
            cin >> weight;
            g.insertEdge(fro, to, weight);
            break;
        case 2:
            cin >> fro;
            cin >> to;
            cout << g.isEdge(fro, to) << "\n";
            break;
        case 3:
            cin >> fro;
            cin >> to;
            cout << g.getWeight(fro, to) << "\n";
            break;
        case 4:
            cin >> vertex;
            arr = g.getAdjacent(vertex);
            arrSize = arr.size();
            j = 0;
            while (j < arrSize)
            {
                cout << arr[j] << " ";
                j++;
            }
            cout << "\n";
            break;
        case 5:
            g.printGraph();
            cout << "\n";
            break;
        }
    }
}