#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

void create_edge(int *x, int *y, vector<struct edge> &edges, int n);

class DisjSet
{
    int *rank, *p, n;

public:
    DisjSet(int n)
    {
        rank = new int[n];
        p = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
        }
    }

    int find(int x)
    {
        if (p[x] != x)
        {
            p[x] = find(p[x]);
        }

        return p[x];
    }

    void Union(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);

        if (xset != yset)
        {
            if (rank[xset] < rank[yset])
            {
                p[xset] = yset;
            }
            else if (rank[xset] > rank[yset])
            {
                p[yset] = xset;
            }
            else
            {
                p[yset] = xset;
                rank[xset]++;
            }
        }
    }
};

struct edge
{
    int s;
    int e;
    int d;
};

bool myfunction(edge i, edge j) { return (i.d < j.d); }

int main(int argc, char **argv)
{
    ifstream inFile;
    inFile.open(argv[1]);

    int n;
    inFile >> n;
    int *node_x = new int[n];
    int *node_y = new int[n];
    for (int i = 0; i < n; i++)
    {
        inFile >> node_x[i] >> node_y[i];
    }
    DisjSet set(n);
    int s, e;
    while (inFile >> s >> e)
    {
        set.Union(s, e);
    }
    vector<struct edge> edges;
    create_edge(node_x, node_y, edges, n);
    sort(edges.begin(), edges.end(), myfunction);
    vector<struct edge> new_edges;
    for (edge i : edges)
        if (set.find(i.s) != set.find(i.e))
        {
            set.Union(i.s, i.e);
            new_edges.push_back(i);
        }
    int min_cost = 0;
    for (edge i : new_edges)
    {
        min_cost += i.d;
    }
    ofstream outFile;
    outFile.open(argv[2]);

    outFile << min_cost << endl;
    for (edge i : new_edges)
    {
        outFile << i.s << " " << i.e << endl;
    }
    outFile.close();
    return 0;
}

void create_edge(int *x, int *y, vector<struct edge> &edges, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            struct edge e;
            e.s = i;
            e.e = j;
            e.d = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            edges.push_back(e);
        }
    }
}