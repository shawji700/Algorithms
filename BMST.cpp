#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

struct Edge
{
    int u, v, weight;
};

class DSU
{
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int bottleneckMST(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    vector<Edge> edges;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (adjMatrix[i][j] > 0)
            {
                edges.push_back({i, j, adjMatrix[i][j]});
            }
        }
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    DSU dsu(n);
    int bottleneck = INT_MAX;

    for (const auto &edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.unionSets(edge.u, edge.v);
            bottleneck = edge.weight;
        }
    }

    return bottleneck;
}

int main()
{

    cout << "Number of test cases:\n";
    int T;
    cin >> T;
    while (T--)
    {
        int v;

        cout << "Enter the number of rows X columns: ";
        cin >> v;

        vector<vector<int>> matrix(v, vector<int>(v, 0));

        cout << "Enter the matrix elements (space-separated):\n";
        for (int i = 0; i < v; ++i)
        {
            for (int j = 0; j < v; ++j)
            {
                cin >> matrix[i][j];
            }
        }

        int bottleneck = bottleneckMST(matrix);
        cout << "The bottleneck weight of the Minimum Spanning Tree is: " << bottleneck << endl;
    }
    // input example
    // 0 2 3 0
    // 2 0 1 4
    // 3 1 0 5
    // 0 4 5 0

    return 0;
}
