/*
 * This is the file in which you'll write the functions required to implement
 * a queue using two stacks.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Anthony Pham
 * Email: phamanth@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue_from_stacks.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your queue and return a pointer to the queue structure.
 */
struct queue_from_stacks* queue_from_stacks_create() {

  struct queue_from_stacks* queue = malloc(sizeof(struct queue_from_stacks));
  if (queue == NULL) {
      fprintf(stderr, "Memory allocation failed in queue_from_stacks_create()\n");
      exit(1);
  }


  queue->inbox = stack_create();
  queue->outbox = stack_create();
  return queue;
}


/*
 * This function should free all of the memory allocated to a queue, including
 * the memory associated with each stack.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if queue is NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* queue) {
  if (queue == NULL) {
      fprintf(stderr, "Error: queue_from_stacks_free() called with NULL queue pointer\n");
      exit(1);
  }
  
  stack_free(queue->inbox);
  stack_free(queue->outbox);
 
  free(queue);
}


/*
 * This function should return 1 if a queue is completely empty or 0 if there
 * is at least one element stored in the queue.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *
 * Return:
 *   Should return 1 if the queue is empty or 0 otherwise.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* queue) {
  if (queue == NULL) {
      fprintf(stderr, "Error: queue_from_stacks_isempty() called with NULL queue pointer\n");
      exit(1);
  }
  
  if (stack_isempty(queue->inbox) && stack_isempty(queue->outbox))
    return 1;
  else
    return 0;
}

/*
 * Should enqueue a new value onto the end of a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value) {
  if (queue == NULL) {
      fprintf(stderr, "Error: queue_from_stacks_enqueue() called with NULL queue pointer\n");
      exit(1);
  }
 
  stack_push(queue->inbox, value);
}



/*
 * Should return a queue's front value without removing that value from the
 * queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue.
 */
int queue_from_stacks_front(struct queue_from_stacks* queue) {
  if (queue == NULL) {
      fprintf(stderr, "Error: queue_from_stacks_front() called with NULL queue pointer\n");
      exit(1);
  }
  if (queue_from_stacks_isempty(queue)) {
      fprintf(stderr, "Error: queue_from_stacks_front() called with empty queue\n");
      exit(1);
  }


  if (stack_isempty(queue->outbox)) {
      while (!stack_isempty(queue->inbox)) {
          int value = stack_pop(queue->inbox);
          stack_push(queue->outbox, value);
      }
  }
 
  return stack_top(queue->outbox);
}



/*
 * Should remove the front element from a queue and return its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue before that value
 *   is dequeued.
 */
int queue_from_stacks_dequeue(struct queue_from_stacks* queue) {
  if (queue == NULL) {
      fprintf(stderr, "Error: queue_from_stacks_dequeue() called with NULL queue pointer\n");
      exit(1);
  }
  if (queue_from_stacks_isempty(queue)) {
      fprintf(stderr, "Error: queue_from_stacks_dequeue() called with empty queue\n");
      exit(1);
  }

  
  if (stack_isempty(queue->outbox)) {
      while (!stack_isempty(queue->inbox)) {
          int value = stack_pop(queue->inbox);
          stack_push(queue->outbox, value);
      }
  }
 
  return stack_pop(queue->outbox);
}
