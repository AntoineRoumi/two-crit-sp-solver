#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct Edge {
    int time;
    int cost;
} Edge;

// In Graph.edges, the edge u->v is at location u*Graph.vertex_count + v
typedef struct Graph {
    Edge *edges;
    int vertex_count;
} Graph;

Graph init_graph(int vertex_count);
void free_graph(Graph graph);
void add_edge(Graph graph, int origin, int dest, int cost, int time);
void remove_edge(Graph graph, int origin, int dest);
Edge* get_edge(Graph graph, int origin, int destination);
void init_random_complete_edges(Graph graph, int time_limit, int cost_limit);

#endif // !GRAPH_H_
