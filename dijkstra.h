#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <limits.h>
#include <float.h>
#include <math.h>

float f_min_distance(float *dist, int *sptSet, int vertex_count);

float f_dijkstra(float *graph, int vertex_count, int *solution);

int min_distance(int *dist, int *sptSet, int vertex_count); 

int dijkstra(int *graph, int vertex_count, int *solution);

#endif /* !DIJKSTRA_H_ */
