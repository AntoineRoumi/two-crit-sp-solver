#include <stdio.h>

#include "lagrange.h"
#include "graph.h"
#include "solution.h"

int main() {
    // Small example
    
    // We initialize the graph with 6 vertices 
    Graph graph = init_graph(6);

    // We add each edge individually
    add_edge(graph, 0, 1, 3, 4);
    add_edge(graph, 0, 2, 3, 8);
    add_edge(graph, 0, 3, 4, 2);
    add_edge(graph, 0, 4, 2, 24);
    add_edge(graph, 1, 3, 10, 2);
    add_edge(graph, 1, 5, 13, 2);
    add_edge(graph, 2, 3, 0, 2);
    add_edge(graph, 2, 5, 5, 6);
    add_edge(graph, 3, 2, 6, 1);
    add_edge(graph, 3, 4, 6, 4);
    add_edge(graph, 3, 5, 9, 12);
    add_edge(graph, 4, 5, 2, 6);

    int **optimal_solutions;
    int num_solutions = 0;

    // We solve the two-criteria shortest path problem
    optimal_solutions = solve(graph, &num_solutions);

    // We print each solution
    for (int i = 0; i < num_solutions; ++i) {
        printf("Solution %i\n", i);
        printSolution(graph, optimal_solutions[i]);
    }

    // We have to free the solution 
    free_solutions(optimal_solutions, num_solutions);
    // And free the graph
    free_graph(graph);

    return 0;
}
