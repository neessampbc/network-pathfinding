#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "graph.h"

/*
 * File: CreateGraphAndTest.cc
 * Author: Neessam Moustafa
 * Purpose: Builds a directed weighted graph and answers adjacency queries.
 * Creation Date: 2026-05-13
 */

using namespace std;

int graphTestDriver(int argc, char **argv) {
    (void)argc;

    try {
        Graph graph;
        graph.loadFromFile(argv[1]);

        ifstream query_file(argv[2]);
        if (!query_file) {
            throw runtime_error("Unable to open adjacency query file.");
        }

        cout << fixed << setprecision(1);

        int from = 0;
        int to = 0;
        while (query_file >> from >> to) {
            double weight = 0.0;
            if (graph.getEdgeWeight(from, to, weight)) {
                cout << from << " " << to << ": connected " << weight << "\n";
            } else {
                cout << from << " " << to << ": not_connected\n";
            }
        }
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
