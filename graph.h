#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <cctype>
#include <cmath>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/*
 * File: graph.h
 * Author: Neessam Moustafa
 * Purpose: Defines a directed weighted graph with adjacency-list storage,
 *          adjacency lookup, and Dijkstra shortest path routines.
 * Creation Date: 2026-05-13
 */

class Graph {
 public:
  struct Edge {
    int destination;
    double weight;
  };

  // Parameters: file_name - input graph file path.
  // Precondition: file_name refers to a readable file with valid graph format.
  // Postcondition: current graph data is replaced by graph parsed from file.
  void loadFromFile(const std::string &file_name) {
    std::ifstream input(file_name);
    if (!input) {
      throw std::runtime_error("Unable to open graph file: " + file_name);
    }

    std::string line;
    int vertex_count = 0;
    while (std::getline(input, line)) {
      if (isBlank(line)) {
        continue;
      }
      std::istringstream first_line(line);
      if (!(first_line >> vertex_count) || vertex_count <= 0) {
        throw std::runtime_error("Invalid vertex count in graph file.");
      }
      break;
    }

    if (vertex_count <= 0) {
      throw std::runtime_error("Graph file missing vertex count.");
    }

    adjacency_.assign(vertex_count + 1, {});

    while (std::getline(input, line)) {
      if (isBlank(line)) {
        continue;
      }

      std::istringstream line_stream(line);
      int source = 0;
      if (!(line_stream >> source)) {
        throw std::runtime_error("Invalid source vertex line in graph file.");
      }
      validateVertex(source);

      int destination = 0;
      double weight = 0.0;
      while (line_stream >> destination) {
        if (!(line_stream >> weight)) {
          throw std::runtime_error("Edge weight missing for destination vertex.");
        }
        validateVertex(destination);
        adjacency_[source].push_back({destination, weight});
      }
    }
  }

  // Parameters: from - source vertex, to - destination vertex.
  // Precondition: graph has been loaded and vertices are in [1, numberOfVertices()].
  // Postcondition: returns true when directed edge (from -> to) exists; stores weight.
  bool getEdgeWeight(int from, int to, double &weight_out) const {
    validateVertex(from);
    validateVertex(to);

    for (const Edge &edge : adjacency_[from]) {
      if (edge.destination == to) {
        weight_out = edge.weight;
        return true;
      }
    }
    return false;
  }

  // Precondition: none.
  // Postcondition: returns number of vertices currently stored.
  int numberOfVertices() const {
    return static_cast<int>(adjacency_.size()) - 1;
  }

  // Parameters: start_vertex - source vertex, distances - output shortest costs,
  //             previous - output predecessor chain for shortest paths.
  // Precondition: start_vertex is in [1, numberOfVertices()].
  // Postcondition: distances[v] is shortest cost from start_vertex to v, or INF.
  void dijkstra(int start_vertex,
                std::vector<double> &distances,
                std::vector<int> &previous) const {
    validateVertex(start_vertex);

    const int n = numberOfVertices();
    const double kInf = std::numeric_limits<double>::infinity();
    distances.assign(n + 1, kInf);
    previous.assign(n + 1, -1);

    struct HeapNode {
      int vertex;
      double distance;

      bool operator<(const HeapNode &rhs) const {
        if (distance != rhs.distance) {
          return distance < rhs.distance;
        }
        return vertex < rhs.vertex;
      }
    };

    BinaryHeap<HeapNode> frontier;
    distances[start_vertex] = 0.0;
    previous[start_vertex] = start_vertex;
    frontier.insert({start_vertex, 0.0});

    /*
     * Standard lazy Dijkstra:
     * multiple entries for a vertex may exist in heap; stale ones are skipped.
     */
    while (!frontier.isEmpty()) {
      HeapNode current;
      frontier.deleteMin(current);

      if (current.distance > distances[current.vertex]) {
        continue;
      }

      for (const Edge &edge : adjacency_[current.vertex]) {
        const double candidate = current.distance + edge.weight;
        if (candidate < distances[edge.destination]) {
          distances[edge.destination] = candidate;
          previous[edge.destination] = current.vertex;
          frontier.insert({edge.destination, candidate});
        }
      }
    }
  }

 private:
  std::vector<std::vector<Edge>> adjacency_;

  bool isBlank(const std::string &line) const {
    for (char c : line) {
      if (!std::isspace(static_cast<unsigned char>(c))) {
        return false;
      }
    }
    return true;
  }

  void validateVertex(int vertex) const {
    if (vertex <= 0 || vertex >= static_cast<int>(adjacency_.size())) {
      throw std::runtime_error("Vertex index out of range.");
    }
  }
};

#endif
