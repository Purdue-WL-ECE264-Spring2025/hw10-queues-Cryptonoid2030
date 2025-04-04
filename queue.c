#include "queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define VISITED_TABLE_SIZE 10007  // Prime number for the hash table size

// Simple hash function
unsigned int hash(uint64_t serialized_state) {
    return serialized_state % VISITED_TABLE_SIZE;
}

// Define the hash table structure
struct visited_table {
    bool table[VISITED_TABLE_SIZE];
};

// Initialize visited table
void init_visited(struct visited_table *visited) {
    for (int i = 0; i < VISITED_TABLE_SIZE; i++) {
        visited->table[i] = false;
    }
}

// Check if a state has been visited
bool is_visited(struct visited_table *visited, uint64_t serialized_state) {
    unsigned int index = hash(serialized_state);
    return visited->table[index];
}

// Mark a state as visited
void mark_visited(struct visited_table *visited, uint64_t serialized_state) {
    unsigned int index = hash(serialized_state);
    visited->table[index] = true;
}

// void deserialShow(struct game_state data, struct game_state next)
// {
//     printf("serialized data: %llu next: %llu\n", serialize(data), serialize(next));
//     for (int row = 0; row < 4; row++) {
//         for (int col = 0; col < 4; col++) {
//             printf("%3d ", data.tiles[row][col]);
//         }
//         printf("     |     ");
//         for (int col = 0; col < 4; col++) {
//             printf("%3d ", next.tiles[row][col]);
//         }
//         printf("\n");
//     }
//     printf("----------------------------------------------------------------------\n");
// }

void enqueue(struct queue *q, struct game_state state) {
    insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
    return deserialize(remove_from_head(&q->data));
}

int number_of_moves(struct game_state start) {
    struct queue q = { .data = { .head = NULL } };
    struct visited_table visited;
    init_visited(&visited); // Initialize visited table
    enqueue(&q, start);
    
    while (q.data.head) {
        struct game_state cur = dequeue(&q);

        // Check if we've already visited this state
        if (is_visited(&visited, serialize(cur))) {
            continue;  // Skip this state
        }
        
        // Mark the current state as visited
        mark_visited(&visited, serialize(cur));

        printf("Dequeued state: num_steps = %d\n", cur.num_steps);

        // Check if the current state is the target state
        
        if (serialize(cur) == serialize((struct game_state){.tiles = {
                {1, 2, 3, 4}, 
                {5, 6, 7, 8}, 
                {9, 10, 11, 12}, 
                {13, 14, 15, 0}}, // Target state
            .empty_row = 3, .empty_col = 3, .num_steps = cur.num_steps
        })) 
        {
            return cur.num_steps;
        }

        // Generate neighbors and enqueue valid moves
        struct game_state next;
        next = cur;
        move_up(&next); 
        if (next.num_steps > cur.num_steps) {
            enqueue(&q, next);
        }

        next = cur;
        move_down(&next); 
        if (next.num_steps > cur.num_steps) {
            enqueue(&q, next);
        }  

        next = cur;
        move_left(&next); 
        if (next.num_steps > cur.num_steps) {
            enqueue(&q, next);
        }

        next = cur; 
        move_right(&next); 
        if (next.num_steps > cur.num_steps) {
            enqueue(&q, next);
        }

        deserialShow(cur, (struct game_state){.tiles = {
          {1, 2, 3, 4}, 
          {5, 6, 7, 8}, 
          {9, 10, 11, 12}, 
          {13, 14, 15, 0}}, // Target state
      .empty_row = 3, .empty_col = 3, .num_steps = 0
  });
    }
    
    return -1; // No solution found
}
