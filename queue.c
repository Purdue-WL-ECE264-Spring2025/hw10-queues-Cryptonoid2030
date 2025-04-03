#include "queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void enqueue(struct queue *q, struct game_state state) {
    insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
    return deserialize(remove_from_head(&q->data));
}

int number_of_moves(struct game_state start) {
    struct queue q = { .data = { .head = NULL } };
    enqueue(&q, start);
    
    while (q.data.head) {
        struct game_state cur = dequeue(&q);
        if (serialize(cur) == serialize((struct game_state){
            .tiles = {
                {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}
            },
            .empty_row = 3, .empty_col = 3, .num_steps = 0
        })) return cur.num_steps;
        
        struct game_state next;
        next = cur; move_up(&next); if (next.num_steps > cur.num_steps) enqueue(&q, next);
        next = cur; move_down(&next); if (next.num_steps > cur.num_steps) enqueue(&q, next);
        next = cur; move_left(&next); if (next.num_steps > cur.num_steps) enqueue(&q, next);
        next = cur; move_right(&next); if (next.num_steps > cur.num_steps) enqueue(&q, next);
    }
    
    return -1; // No solution found
}
