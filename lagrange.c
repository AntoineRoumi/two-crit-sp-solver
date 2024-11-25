#include "lagrange.h"

#include <stdlib.h>
#include <string.h>

#include "dijkstra.h"

float L(Graph graph, Solution solution, float lambda, int time_limit) {
    // This function calculates the value of L for the given solution and lambda 
    // It assumes that the solution is a valid solution
    // If the solution is not valid, the result will be meaningless

    float sum = 0;
    Edge *current_edge;
    int origin = 0;
    int dest = 0;
    int t = graph.vertex_count - 1;

    for (int i = 0; i < graph.vertex_count; ++i) {
        dest = solution[origin];
        current_edge = &graph.edges[origin * graph.vertex_count + dest]; 
        sum += current_edge->cost + lambda * current_edge->time;

        if (dest == t) {
            break;
        }

        origin = dest;
    }

    sum -= lambda * time_limit;

    return sum;
}

float w(Graph graph, Solution *solutions, int num_solutions, float lambda, int time_limit) {
    // Calculates the value of w(lambda), i.e. min(L(lambda, x)) 
    // with x being one of the currently found solutions

    float min = L(graph, solutions[0], lambda, time_limit);
    float currentL;

    for (int i = 1; i < num_solutions; ++i) {
        currentL = L(graph, solutions[i], lambda, time_limit); 
        if (currentL < min) {
            min = currentL;
        }
    }

    return min;
}

#include <stdio.h>

float max_w(Graph graph, Solution *solutions, int num_solutions, int time_limit, int iterations, float *lambda_k) {
    // Calculates the maximum value of w(lambda)
    // Puts the value of lambda giving this result in lambda_k

    float start = 0.0f;

    // Values of three lambdas that we use to search for the optimal lambda 
    // At the end of this function, first_l is before the optimal lambda,
    // while third_l is after the optimal lambda, 
    // and second_l will be considered as the optimal lambda
    float first_l = start;
    float second_l;
    float third_l;

    // Respectively the values of w(first_l), w(second_l) and w(third_l) 
    float first_w;
    float second_w;
    float third_w;

    // Search process
    for (int iter = 0; iter < iterations; ++iter) {
        // We increase the precision of search after each iteration
        float step = powf(10.f, -iter); 

        // We don't need to assign first_l because it keeps its value from previous iteration
        second_l = first_l + step;
        third_l = second_l + step;

        first_w = w(graph, solutions, num_solutions, first_l, time_limit);
        second_w = w(graph, solutions, num_solutions, second_l, time_limit);
        third_w = w(graph, solutions, num_solutions, third_l, time_limit);

        // As min(w(lambda)) is concave, we look for a point where the function is not increasing anymore
        while (first_w <= second_w && second_w <= third_w) {
            first_l = second_l;
            first_w = second_w;
            second_l = third_l;
            second_w = third_w;
            third_l += step;
            third_w = w(graph, solutions, num_solutions, third_l, time_limit);
        }

        // We know that the maximum w(lambda) is first_l and third_l, so we'll
        // start the next search iteration at first_l
    }

    *lambda_k = second_l;

    return second_w;
}

void cheapest_path_search(Graph graph, Solution solution) {
    // Calculates the cheapest path from 0 to (graph.vertex_count - 1) using Dijkstra

    int cost_graph[graph.vertex_count * graph.vertex_count];

    Edge *edge;
    for (int row = 0; row < graph.vertex_count; ++row) {
        for (int col = 0; col < graph.vertex_count; ++col) {
            edge = &graph.edges[row * graph.vertex_count + col];
            cost_graph[row * graph.vertex_count + col] = edge->cost;
        }
    }

    dijkstra(cost_graph, graph.vertex_count, solution);
}

void shortest_path_search(Graph graph, Solution solution) {
    // Calculates the shortest path from 0 to (graph.vertex_count - 1) using Dijkstra

    int time_graph[graph.vertex_count * graph.vertex_count];

    Edge *edge;
    for (int row = 0; row < graph.vertex_count; ++row) {
        for (int col = 0; col < graph.vertex_count; ++col) {
            edge = &graph.edges[row * graph.vertex_count + col];
            time_graph[row * graph.vertex_count + col] = edge->time;
        }
    }

    dijkstra(time_graph, graph.vertex_count, solution);
}

void solve_lagrangian(Graph graph, Solution *initial_solutions, int initial_num_solutions, int time_limit, int *optimal_solution) {
    float w_k_star;
    float lambda_k;
    float w_lambda_k;

    Solution *solutions = malloc(initial_num_solutions * sizeof(int*));
    for (int i = 0; i < initial_num_solutions; ++i) {
        solutions[i] = initial_solutions[i];
    }
    int num_solutions = initial_num_solutions;

    float *new_edges = malloc(graph.vertex_count * graph.vertex_count * sizeof(float));
    Edge *edge;

    while (1) {
        w_k_star = max_w(graph, solutions, num_solutions, time_limit, 3, &lambda_k);

        // Create a new graph based on graph with a single cost on each edge 
        // For each edge e in the original graph, the cost is equal to e.cost + lambda_k * e.time
        // That way, we can solve a single criteria shortest path problem using Dijkstra
        for (int row = 0; row < graph.vertex_count; ++row) {
            for (int col = 0; col < graph.vertex_count; ++col) {
                edge = get_edge(graph, row, col);
                if (edge->time == -1) {
                    new_edges[row * graph.vertex_count + col] = -1;
                } else {
                    new_edges[row * graph.vertex_count + col] = edge->cost + lambda_k * edge->time;
                }
            }
        }

        // Find a solution that satisfies w(lambda_k)
        Solution x_k;
        init_solution(graph, &x_k);
        f_dijkstra(new_edges, graph.vertex_count, x_k);

        // If the solution exceeds the time limit, 
        // it means that we can no longer improve the cost without exceeding the time limit
        // so we return the last valid solution
        if (total_time(graph, x_k) > time_limit) {
            free(x_k);
            memcpy(optimal_solution, solutions[num_solutions - 1], graph.vertex_count * sizeof(int));
            break;
        }

        // If there's no improvement of w(lambda_k) compared to the previous iteration,
        // we can stop the searching loop and return x_k as the optimal solution
        w_lambda_k = L(graph, x_k, lambda_k, time_limit);
        if (w_lambda_k == w_k_star) {
            memcpy(optimal_solution, x_k, graph.vertex_count * sizeof(int));
            break;
        }

        // We then add the newly found solution to the set of found solutions for next iterations
        ++num_solutions;
        solutions = realloc(solutions, num_solutions * sizeof(int*));
        solutions[num_solutions - 1] = x_k;
    }

    // Free the temporary ponderated graph 
    free(new_edges);

    // Free the solutions, except the initial solutions as they are not heap allocated
    for (int i = initial_num_solutions; i < num_solutions; ++i) {
        free(solutions[i]);
    }
}

int** solve(Graph graph, int *num_optimal_solutions) {
    // Solves the two-criteria shortest path problem on graph, 
    // using Lagrangian relaxation and epsilon constraint method
    //
    // Returns an array of all the solutions 
    // Outputs num_optimal_solutions the number of optimal solutions found

    // The two initial solutions are respectively the cheapest solution and the shortest solution  
    Solution cheapest_solution;
    init_solution(graph, &cheapest_solution);
    cheapest_path_search(graph, cheapest_solution);
    int cheapest_solution_time = total_time(graph, cheapest_solution);
    
    Solution shortest_solution;
    init_solution(graph, &shortest_solution);
    shortest_path_search(graph, shortest_solution);
    int shortest_solution_time = total_time(graph, shortest_solution);
    Solution initial_solutions[] = { cheapest_solution, shortest_solution };
    int num_initial_solutions = 2;

    // We know that no optimal solution will exceed the duration of the cheapest solution,
    // because it would be dominated by the latter,
    // so the duration of each solution is <= to cheapest_solution_time
    int time_limit = cheapest_solution_time;
    Solution *optimal_solutions = NULL; 
    int num_solutions = 0;
    Solution current_solution;
    init_solution(graph, &current_solution);
    int current_solution_time;

    // At each iteration we calculate the optimate solution for the given time limit 
    // We can then safely decrease to time limit to the time of the found solution - 1,
    // because no optimal solution is in between.
    // We put each optimal solution found in the optimal_solutions array.
    // We stop the search when the time limit is shorter than the minimal possible duration.
    while (time_limit >= shortest_solution_time) {
        solve_lagrangian(graph, initial_solutions, num_initial_solutions, time_limit, current_solution);
        current_solution_time = total_time(graph, current_solution);
        ++num_solutions;
        optimal_solutions = realloc(optimal_solutions, num_solutions * sizeof(int*));
        optimal_solutions[num_solutions - 1] = malloc(graph.vertex_count * sizeof(int));
        memcpy(optimal_solutions[num_solutions - 1], current_solution, graph.vertex_count * sizeof(int));
        time_limit = current_solution_time - 1;
    }

    free(cheapest_solution);
    free(shortest_solution);
    free(current_solution);

    *num_optimal_solutions = num_solutions;

    return optimal_solutions;
}
