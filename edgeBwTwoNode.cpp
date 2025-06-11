#include <iostream>
#include <vector>

using namespace std;

bool dfs(const vector<vector<int>> &graph, int u, int v, vector<bool> &visited)
{
    if (u == v)
        return true;

    visited[u] = true;

    for (int i = 0; i < graph.size(); ++i)
    {
        if (graph[u][i] == 1 && !visited[i])
        {
            if (dfs(graph, i, v, visited))
            {
                return true;
            }
        }
    }
    return false;
}

bool isPathExist(const vector<vector<int>> &graph, int u, int v)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    return dfs(graph, u, v, visited);
}

int main()
{
    cout << "Number of test cases:\n";
    int T;
    cin >> T;
    while (T--)
    {
        int vetices;

        cout << "Enter the number of vetices: ";
        cin >> vetices;

        vector<vector<int>> matrix(vetices, vector<int>(vetices, 0));

        cout << "Enter the matrix elements (space-separated):\n";
        for (int i = 0; i < vetices; ++i)
        {
            for (int j = 0; j < vetices; ++j)
            {
                cin >> matrix[i][j];
            }
        }

        int u, v;
        cout << "Enter u and v (space-separated)";
        cin >> u >> v;
        if (isPathExist(matrix, u, v))
        {
            cout << "Path exists from " << u << " to " << v << endl;
        }
        else
        {
            cout << "No path exists from " << u << " to " << v << endl;
        }
    }
    // input example
    // 0 1 0 0
    // 0 0 1 0
    // 0 0 0 1
    // 1 0 0 0
    return 0;
}
