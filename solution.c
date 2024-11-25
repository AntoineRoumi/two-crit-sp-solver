#include "solution.h"

#include <stdio.h>
#include <stdlib.h>

void init_solution(Graph graph, Solution *solution) {
    *solution = malloc(graph.vertex_count * sizeof(int));
    // Initializes
    for (int node = 0; node < graph.vertex_count; ++node) {
        (*solution)[node] = -1;
    }
}

int total_cost(Graph graph, Solution solution){
    // Calculates the total cost of the solution 
    // Assumes that the solution is valid
    // Otherwise returns -1

    int sum = 0;

    int origin = 0;
    int dest = 0;
    int t = graph.vertex_count - 1;

    for (int i = 0; i < graph.vertex_count; ++i) {
        dest = solution[origin];
        sum += graph.edges[origin * graph.vertex_count + dest].cost;
        
        if (dest == t) {
            return sum;
        }

        origin = dest;
    }

    return -1;
}

int total_time(Graph graph, Solution solution) {
    // Calculates the total cost of the solution 
    // Assumes that the solution is valid
    // Otherwise returns -1

    int sum = 0;

    int origin = 0;
    int dest = 0;
    int t = graph.vertex_count - 1;

    for (int i = 0; i < graph.vertex_count; ++i) {
        dest = solution[origin];
        sum += graph.edges[origin * graph.vertex_count + dest].time;

        if (dest == t) {
            return sum;
        }

        origin = dest;
    }

    return -1;
}

void printSolution(Graph graph, Solution solution) {
    Edge *edge;
    int origin = 0;
    int dest = 0;
    int t = graph.vertex_count - 1;

    for (int i = 0; i < graph.vertex_count; ++i) {
        dest = solution[origin];
        edge = get_edge(graph, origin, dest);

        printf("( %d )\n  |\n  | (%d, %d)\n  v\n", origin, edge->cost, edge->time);

        if (dest == t) {
            break;
        }

        origin = dest;
    }
    printf("( %d )\n\nTotal cost: %d\nTotal time: %d\n\n", dest, total_cost(graph, solution), total_time(graph, solution));
}

int select_edge(Graph graph, Solution solution, int origin, int destination) {
    // Adds the edge origin -> destination to the solution

    if (get_edge(graph, origin, destination)->time == -1) {
        return -1; 
    }
    solution[origin] = destination;
    return 0;
}

int is_selected(Graph graph, Solution solution, int origin, int destination) {
    // Checks if the edge origin -> destination is in the solution

    return solution[origin] == destination;
}

int is_solution_valid(Graph graph, Solution solution) {
    // Returns 1 if the path of the solution goes from node 0 to node (graph.vertex_count - 1)
    // Returns 0 if not

    Edge *current_edge;
    int origin = 0;
    int dest = 0;
    int t = graph.vertex_count - 1;
    
    for (int i = 0; i < graph.vertex_count; ++i) {
        dest = solution[origin];
        // If we reached the final destination
        if (dest == t) {
            return 1;
        }
        // If the destination is not a valid node
        if (dest < 0 || dest >= graph.vertex_count) {
            return 0;
        }
        origin = dest;
    }

    // If we haven't reached the final destination after graph.vertex_count steps,
    // it means that there's a loop in the path
    return 0;
}

void free_solutions(Solution solutions[], int num_solutions) {
    // Utility function to free an array of Solution     

    for (int i = 0; i < num_solutions; ++i) {
        free(solutions[i]);
    }
}
