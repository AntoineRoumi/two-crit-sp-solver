dijkstra.o: dijkstra.c 
	gcc -c dijkstra.c

graph.o: graph.c 
	gcc -c graph.c

solution.o: solution.c 
	gcc -c solution.c

lagrange.o: lagrange.c 
	gcc -c lagrange.c

main.o: main.c 
	gcc -c main.c

optm: dijkstra.o graph.o solution.o lagrange.o main.o 
	gcc -o optm dijkstra.o graph.o solution.o lagrange.o main.o -lm
