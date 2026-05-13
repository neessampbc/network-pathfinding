# GRAPHS PROJECT

To compile type:

`make all`

To clean object files and executables type:

`make clean`

To run the create and test graph routine, type:

`./CreateGraphAndTest <GRAPH_FILE> <ADJACENCY_QUERYFILE>`

where `<GRAPH_FILE>` is the file used to create the graph and
`<ADJACENCY_QUERYFILE>` is the file used to check if vertices are adjacent.

Example:

`./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt`

Expected output format for each query:

`<u> <v>: connected <weight>`

or

`<u> <v>: not_connected`

To run the find paths in graph routine, type:

`./FindPaths <GRAPH_FILE> <STARTING_VERTEX>`

where `<GRAPH_FILE>` is the file used to create the graph and
`<STARTING_VERTEX>` is the starting vertex for shortest paths.

Example:

`./FindPaths Graph2.txt 1`

Expected output format for each target vertex from `1` to `N`:

`<target>: <path vertices separated by spaces> cost: <total_cost>`

or

`<target>: not_possible`

Deliverables:

- `README.md`
- `CreateGraphAndTest.cc`
- `FindPaths.cc`
- `graph.h`
