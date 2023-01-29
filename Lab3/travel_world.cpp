#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);

    int m, n;
    inFile >> n >> m;
    int graph[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = INT_MAX;
        }
    }
    int s, e, c;
    for (int i = 0; i < m; i++)
    {
        inFile >> s >> e >> c;
        graph[s][e] = c;
        graph[e][s] = c;
    }
    inFile.close();
    vector<int> unvisted;
    vector<int> path;
    for (int i = 1; i < n; i++)
    {
        unvisted.push_back(i);
    }
    int current = 0;
    while (unvisted.empty() == false)
    {
        int min = INT_MAX;
        int minNode = INT_MAX;
        int minNodeIndex = INT_MAX;
        int i = 0;
        for (auto n : unvisted)
        {
            if (graph[current][n] < min)
            {
                min = graph[current][n];
                minNode = n;
                minNodeIndex = i;
            }
            i++;
        }
        if (minNode == INT_MAX)
        {
            break;
        }
        current = minNode;
        unvisted.erase(unvisted.begin() + minNodeIndex);
        path.push_back(current);
    }
    ofstream outFile;
    outFile.open(argv[2]);
    if (path.size() != n - 1)
    {
        outFile << "No" << endl;
    }
    else
    {
        long weights = 0;
        if (graph[0][path.back()] == INT_MAX)
        {
            outFile << "No" << endl;
        }
        else
        {
            outFile << "Yes" << endl;
            outFile << "Path: "
                 << "0 ";
            for (int i = 0; i < path.size(); i++)
            {
                outFile << path[i] << " ";
                if (i == 0)
                {
                    weights += graph[0][path[i]];
                }
                else
                {
                    weights += graph[path[i-1]][path[i]];
                }
            }
            weights += graph[path.back()][0];
            outFile << 0 << endl;
            outFile << "Cost: " << weights << endl;
        }
    }
    outFile.close();

    return 0;
}
