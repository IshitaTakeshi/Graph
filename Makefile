
CC=gcc
CFLAGS=-std=c99 -pedantic -g -Wall -Werror

SRC=graph.c search.c queue.c error.c
OBJS=$(SRC:.c=.o)

TARGET=test

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

bfs: $(OBJS)
	${CC} ${CFLAGS} $^ bfs_test.c -o $(TARGET)

dfs: $(OBJS)
	${CC} ${CFLAGS} $^ dfs_test.c -o $(TARGET)

dijkstra: $(OBJS)
	${CC} ${CFLAGS} $^ dijkstra_test.c -o $(TARGET)

all: dijkstra

run:
	./$(TARGET)

clean:
	-@$(RM) $(TARGET) $(OBJS)
