#include "graph.h"

#include <stdlib.h>

Graph init_graph(int vertex_count) {
    Graph graph;

    graph.vertex_count = vertex_count;
    graph.edges = malloc(vertex_count * vertex_count * sizeof(Edge));
    
    Edge *edge;
    for (int row = 0; row < graph.vertex_count; ++row) {
        for (int col = 0; col < graph.vertex_count; ++col) {
            edge = &graph.edges[row * graph.vertex_count + col];
            edge->time = -1;
            edge->cost = -1;
        }
    }

    return graph;
}

void free_graph(Graph graph) {
    free(graph.edges);
}

void add_edge(Graph graph, int origin, int dest, int cost, int time) {
    Edge *edge = &graph.edges[origin * graph.vertex_count + dest];
    edge->cost = cost;
    edge->time = time;
}

void remove_edge(Graph graph, int origin, int dest) {
    Edge *edge = &graph.edges[origin * graph.vertex_count + dest];
    edge->cost = -1;
    edge->time = -1;
}

Edge* get_edge(Graph graph, int origin, int destination) {
    return &graph.edges[origin * graph.vertex_count + destination];
}
