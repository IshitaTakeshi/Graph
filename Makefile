
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Werror -g

SRC=graph.c search.c queue.c
OBJS=$(SRC:.c=.o)

TARGET=test

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

bfs: $(OBJS)
	${CC} ${CFLAGS} $^ bfs_test.c -o $(TARGET)

dfs: $(OBJS)
	${CC} ${CFLAGS} $^ dfs_test.c -o $(TARGET)

all: bfs

run:
	./$(TARGET)

clean:
	-@$(RM) $(TARGET) $(OBJS)
