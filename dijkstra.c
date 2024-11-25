#include "dijkstra.h"

float f_min_distance(float *dist, int *sptSet, int vertex_count) {
    // Function used by the dijkstra algorithm

    float min = FLT_MAX;
    int min_index;

    for (int v = 0; v < vertex_count; ++v) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

float f_dijkstra(float *graph, int vertex_count, int *solution) {
    // Implementation of the Dijkstra algorithm
    // 
    // graph is an array of float that has the same structure as the edges member of struct Graph 
    // 
    // Returns the distance between the source (node 0) and the destination (node vertex_count - 1)

    float minDistances[vertex_count];
    int predecessors[vertex_count];
    int processedVertices[vertex_count];

    for (int i = 0; i < vertex_count; ++i) {
        minDistances[i] = FLT_MAX;
        predecessors[i] = 0;
        processedVertices[i] = 0;
    }

    minDistances[0] = 0;

    for (int count = 0; count < vertex_count - 1; ++count) {
        int u = f_min_distance(minDistances, processedVertices, vertex_count);

        processedVertices[u] = 1;

        for (int v = 0; v < vertex_count; ++v) {
            if (!processedVertices[v]
                && graph[u * vertex_count + v] >= 0.0
                && minDistances[u] != FLT_MAX
                && minDistances[u] + graph[u * vertex_count + v] < minDistances[v]
            ) {
                minDistances[v] = minDistances[u] + graph[u * vertex_count + v];
                predecessors[v] = u;
            }
        }
    }

    int predecessor = vertex_count;
    int node = vertex_count - 1;
    while (predecessor != 0) {
        predecessor = predecessors[node];
        solution[predecessor] = node;
        node = predecessor;
    }

    return minDistances[vertex_count - 1];
}

int min_distance(int *dist, int *sptSet, int vertex_count) {
    // Function used by the dijkstra algorithm

    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < vertex_count; ++v) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

int dijkstra(int *graph, int vertex_count, int *solution) {
    // Implementation of the Dijkstra algorithm
    // 
    // graph is an array of float that has the same structure as the edges member of struct Graph 
    // 
    // Returns the distance between the source (node 0) and the destination (node vertex_count - 1)

    int minDistances[vertex_count];
    int predecessors[vertex_count];
    int processedVertices[vertex_count];

    for (int i = 0; i < vertex_count; ++i) {
        minDistances[i] = INT_MAX;
        predecessors[i] = 0;
        processedVertices[i] = 0;
    }

    minDistances[0] = 0;

    for (int count = 0; count < vertex_count - 1; ++count) {
        int u = min_distance(minDistances, processedVertices, vertex_count);

        processedVertices[u] = 1;

        for (int v = 0; v < vertex_count; ++v) {
            if (!processedVertices[v]
                && graph[u * vertex_count + v] >= 0.0
                && minDistances[u] != INT_MAX
                && minDistances[u] + graph[u * vertex_count + v] < minDistances[v]
            ) {
                minDistances[v] = minDistances[u] + graph[u * vertex_count + v];
                predecessors[v] = u;
            }
        }
    }

    int predecessor = vertex_count;
    int node = vertex_count - 1;
    while (predecessor != 0) {
        predecessor = predecessors[node];
        solution[predecessor] = node;
        node = predecessor;
    }

    return minDistances[vertex_count - 1];
}

