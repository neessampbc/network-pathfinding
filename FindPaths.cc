#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <vector>
#include <string>

#include "graph.h"

/*
 * File: FindPaths.cc
 * Author: Neessam Moustafa
 * Purpose: Runs Dijkstra's algorithm from a starting vertex and prints paths.
 * Creation Date: 2026-05-13
 */

using namespace std;

static vector<int> buildPath(int target, const vector<int> &previous, int start) {
    vector<int> reversed_path;
    int current = target;

    while (current != start) {
        reversed_path.push_back(current);
        current = previous[current];
        if (current == -1) {
            return {};
        }
    }
    reversed_path.push_back(start);

    vector<int> path;
    for (int i = static_cast<int>(reversed_path.size()) - 1; i >= 0; --i) {
        path.push_back(reversed_path[i]);
    }
    return path;
}

int pathfindDriver(int argc, char **argv) {
    (void)argc;

    try {
        Graph graph;
        graph.loadFromFile(argv[1]);

        const int start_vertex = stoi(argv[2]);

        vector<double> distances;
        vector<int> previous;
        graph.dijkstra(start_vertex, distances, previous);

        cout << fixed << setprecision(1);

        const int n = graph.numberOfVertices();
        for (int target = 1; target <= n; ++target) {
            cout << target << ": ";

            if (distances[target] == numeric_limits<double>::infinity()) {
                cout << "not_possible\n";
                continue;
            }

            const vector<int> path = buildPath(target, previous, start_vertex);
            if (path.empty()) {
                cout << "not_possible\n";
                continue;
            }

            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) {
                    cout << " ";
                }
                cout << path[i];
            }
            cout << " cost: " << distances[target] << "\n";
        }
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
