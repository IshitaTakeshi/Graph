#include <stdlib.h>
#include <stdio.h>

int in_index, out_index;
int memory_size;
int queue_size = 0;
void **queue;

/*
 * This method must be called before using a queue.
 * size_ : the size of a queue
 */
void init_queue(int size_) {
    //Allocate memory and initialize indices
    queue_size = size_;
    memory_size = queue_size+1;
    queue = (void **)malloc(size_*sizeof(void *));
    in_index = out_index = 0;
}

/*
 * Returns the number of items in a queue.
 */
int get_n_items() {
    return in_index-out_index;
}

int queue_is_empty() {
    return get_n_items() == 0;
}

int queue_is_full() {
    return get_n_items() == queue_size;
}

/*
 * Enqueueing.
 * item : a pointer to the item inserted to a queue
 */
void enqueue(void *item) {
    if(queue_is_full()) {
        printf("Fatal error: The queue is full.\n");
        exit(-1);
    }

    queue[in_index] = item;
    in_index = (in_index+1) % memory_size;
}

/*
 * Dequeueing.
 */
void *dequeue() {
    if(queue_is_empty()) {
        printf("Fatal error: The queue is empty.\n");
        exit(-1);
    }

    void *item;
    item = queue[out_index];
    out_index = (out_index+1) % memory_size;
    return item;
}

/*
 * This method must be called after using the queue to free the memory area.
 */
void free_queue() {
    free(queue);
}
