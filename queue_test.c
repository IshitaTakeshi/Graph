#include <stdio.h>
#include "queue.h"

int size = 4;
char items[] = {'A', 'B', 'C', 'D'};

int test_enqueue_and_deque() {
    int i;

    init_queue(size);

    for(i=0; i<size; i++) {
        enqueue(&items[i]);
        printf("inserted %c\n", items[i]);
    }

    //all items should be gotten in the insertion order
    char *item;
    int success = 1;
    for(i=0; i<size; i++) {
        item = (char *)dequeue();
        success &= (items[i] == *item);
        printf("got %c, should be gotten %c\n", *item, items[i]);
    }

    free_queue();

    return success;
}

int test_is_full() {
    int success = 1;
    int i, is_full;

    init_queue(size);

    //The queue should not be full when immidiately after initialization
    is_full = queue_is_full();
    success &= !is_full;
    printf("is_full:%d\n", is_full);

    for(i=0; i<size; i++) {
        enqueue(&items[i]);
        printf("inserted %c\n", items[i]);
    }

    //The queue should be full when all items inserted.
    is_full = queue_is_full();
    success &= is_full;
    printf("is_full:%d\n", is_full);

    free_queue();
    return success;
}

int test_is_empty() {
    int success = 1;
    int i, is_empty;

    init_queue(size);

    //The queue should be empty when immidiately after initialization
    is_empty = queue_is_empty();
    success &= is_empty;
    printf("is_empty:%d\n", is_empty);

    for(i=0; i<size; i++) {
        enqueue(&items[i]);
        printf("inserted %c\n", items[i]);
    }

    //The queue should not be empty when all items inserted.
    is_empty = queue_is_empty();
    success &= !is_empty;
    printf("is_empty:%d\n", is_empty);

    free_queue();
    return success;
}

int test_get_n_items() {
    int success = 1;
    int i;
    int s;

    init_queue(size);
    for(i=0; i<size; i++) {
        enqueue(&items[i]);
        s = get_n_items();
        printf("get_n_items(): %d  the real size: %d\n", s, i+1);
        success &= (get_n_items() == i+1);
    }

    free_queue();
    return success;
}

void should_exit_when_too_many_items_inserted() {
    int success = 1;
    int i;
    int s;

    init_queue(size);
    //insert items more than the size of the queue
    for(i=0; i<size+1; i++) {
        enqueue(&items[0]);
    }

    free_queue();
}

void should_exit_when_dequeue_called_if_empty() {
    int i;
    init_queue(size);

    for(i=0; i<size; i++) {
        enqueue(&items[i]);
    }

    //pop items more than kept in the queue
    for(i=0; i<size+1; i++) {
        dequeue();
    }
    free_queue();
}

int main(void) {
    if(test_get_n_items()) {
        printf("get_n_items works correctly.\n\n");
    } else {
        printf("get_n_items doesn't work correctly.\n\n");
    }

    if(test_is_empty()) {
        printf("is_empty works correctly.\n\n");
    } else {
        printf("is_empty doesn't work correctly.\n\n");
    }

    if(test_is_full()) {
        printf("is_full works correctly.\n\n");
    } else {
        printf("is_full doesn't work correctly.\n\n");
    }

    if(test_enqueue_and_deque()) {
        printf("enqueue and dequeue works correctly. \n\n");
    } else {
        printf("enqueue and dequeue doesn't work correctly.\n\n");
    }

    //should_exit_when_too_many_items_inserted();
    //should_exit_when_dequeue_called_if_empty();
    return 0;
}
