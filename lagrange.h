#ifndef LAGRANGE_H_
#define LAGRANGE_H_

#include "graph.h"
#include "solution.h"

float L(Graph graph, Solution solution, float lambda, int time_limit);
float w(Graph graph, Solution *solutions, int num_solutions, float lambda, int time_limit);
float max_w(Graph graph, Solution *solutions, int num_solutions, int time_limit, int iterations, float *lambdak);
void cheapest_path_search(Graph graph, Solution solution);
void shortest_path_search(Graph graph, Solution solution);
void solve_lagrangian(Graph graph, Solution *initial_solutions, int initial_num_solutions, int time_limit, int *optimal_solution);
int** solve(Graph graph, int *num_optimal_solutions);

#endif // !LAGRANGE_H_
