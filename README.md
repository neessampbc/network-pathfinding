# Network Pathfinding

CLI-based C++ project for weighted directed graph analysis.  
It supports fast adjacency queries and shortest-path routing using Dijkstra's algorithm with a heap-backed priority queue.

## Highlights

- Directed, weighted graph representation using an adjacency list
- Adjacency query utility for edge existence and edge weight lookup
- Single-source shortest paths with Dijkstra's algorithm
- Path reconstruction from source to each destination vertex
- Deterministic output ordering from vertex `1` to `N`

## Tech Stack

- Language: `C++17`
- Data structures: adjacency list, binary heap priority queue
- Build system: `Makefile`

## Build

```bash
make all
```

Clean build outputs:

```bash
make clean
```

## Usage

### 1) Adjacency Queries

```bash
./CreateGraphAndTest <GRAPH_FILE> <ADJACENCY_QUERYFILE>
```

Example:

```bash
./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt
```

Output format:

- `<u> <v>: connected <weight>`
- `<u> <v>: not_connected`

### 2) Shortest Paths

```bash
./FindPaths <GRAPH_FILE> <STARTING_VERTEX>
```

Example:

```bash
./FindPaths Graph2.txt 1
```

Output format:

- Reachable: `<target>: <path vertices> cost: <total_cost>`
- Unreachable: `<target>: not_possible`

## Input Format

Graph files use:

- First line: total number of vertices `N` (vertices are `1..N`)
- Remaining lines:
  - `<vertex> <neighbor_1> <weight_1> <neighbor_2> <weight_2> ...`
  - A line with only `<vertex>` means no outgoing edges

## Example (Shortest Paths)

From source vertex `1`:

```text
1: 1 cost: 0.0
2: 1 2 cost: 2.0
3: 1 4 3 cost: 3.0
4: 1 4 cost: 1.0
5: 1 4 5 cost: 3.0
6: 1 4 7 6 cost: 6.0
7: 1 4 7 cost: 5.0
```
