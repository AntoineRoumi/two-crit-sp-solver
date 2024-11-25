#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "graph.h"

// A solution is an array of ints,
// the value of the i-th element indicating the successor of i in the solution path
// If the value is -1, it means that vertex i is not in the solution (except for last element, the destination)
typedef int *Solution;

void init_solution(Graph graph, Solution *solution);
int total_cost(Graph graph, Solution solution);
int total_time(Graph graph, Solution solution);
void printSolution(Graph graph, Solution solution);
int select_edge(Graph graph, Solution solution, int origin, int destination);
int is_selected(Graph graph, Solution solution, int origin, int destination);
int is_solution_valid(Graph graph, Solution solution);
void free_solutions(Solution solutions[], int num_solutions);

#endif 
