```cpp
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;

public:
    Graph(int n) {
        this->n = n;
        adj.resize(n);
    }

    void addRoute(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void showRoutes() {
        cout << "Disaster Area Map\n";
        for (int i = 0; i < n; i++) {
            cout << "Location " << i << ": ";
            for (int v : adj[i])
                cout << v << " ";
            cout << endl;
        }
    }
};

int main() {
    Graph g(6);

    g.addRoute(0, 1);
    g.addRoute(0, 2);
    g.addRoute(1, 3);
    g.addRoute(2, 3);
    g.addRoute(2, 4);
    g.addRoute(3, 5);
    g.addRoute(4, 5);

    cout << "Multi-Drone Search and Rescue\n";
    g.showRoutes();

    return 0;
}
```
