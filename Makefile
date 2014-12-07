all: bfs

bfs:
	gcc graph.c search.c queue.c bfs_test.c -o test -g -Wall

dfs:
	gcc graph.c search.c queue.c dfs_test.c -o test -g -Wall

clean:
	rm -f test
