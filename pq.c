/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:Ella Mudry
 * Email: mudrye@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * min heap key has to be less that the keys below it
 * valid heap cannot be a valid binary search tree
 */

struct pq_node {
  int priority;
  void* value;
};

struct pq{
  struct dynarray* heap;
  // int key;
  // void* value;
  // struct pq_node* left;
  // struct pq_node* right;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  // pq->root = NULL;
  pq->heap = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
// void freer(struct pq_node* node){
//   if(node == NULL){
//     return;
//   }
//   freer(node->left);
//   freer(node->right);
//   free(node);
//   return;
// }

void pq_free(struct pq* pq) {
  // freer(pq->root);
  // free(pq);
  dynarray_free(pq->heap);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if (dynarray_size(pq->heap) == 0){
    return 1;
  }
  else
    return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct pq_node* pq_tree = malloc(sizeof(struct pq_node));
  pq_tree->priority = priority;
  pq_tree->value = value;
  struct pq_node* temp;
  

  dynarray_insert(pq->heap, pq_tree);
  int i = dynarray_size(pq->heap)-1;
  int parent;
  int left = 2*i+1;
  int right = 2*i+2;

  while (i > 0){
    parent = (i-1)/ 2;
    temp = dynarray_get(pq->heap, parent);
    if(temp->priority > pq_tree->priority){
      dynarray_set(pq->heap, i, temp);
      dynarray_set(pq->heap, parent, pq_tree);
      i = (i - 1)/ 2;
    }
    else{
      return;
    }
  }
  // free(pq_tree);
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct pq_node*  data = dynarray_get(pq->heap, 0);
  return data->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct pq_node* data = dynarray_get(pq->heap, 0);
  return data->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

void deleter(struct pq* pq, int i) {
  int left = 2*i + 1;
  int right = 2*i + 2;
  if(i >= dynarray_size(pq->heap)){
    return;
  }
  struct pq_node* temp = dynarray_get(pq->heap, i);
  if(left >= dynarray_size(pq->heap)){
    return;
  }
  else if(right >= dynarray_size(pq->heap)){
    struct pq_node* l = dynarray_get(pq->heap, left);
    if(temp->priority > l->priority){
      // temp = head;
      dynarray_set(pq->heap, left, temp);
      dynarray_set(pq->heap, i, l);
      // deleter(pq, l, left);
    }
    else
      return;
  }
  else{
    struct pq_node* l = dynarray_get(pq->heap, left);
    struct pq_node* r = dynarray_get(pq->heap, right);

    if(l->priority > r->priority){
      if(temp->priority > r->priority){
        // temp = head;
        dynarray_set(pq->heap, right, temp);
        dynarray_set(pq->heap, i, r);
        deleter(pq, right);
      }
      else
        return;

    }
    else{
      if(temp->priority > l->priority){
        // temp = head;
        dynarray_set(pq->heap, left, temp);
        dynarray_set(pq->heap, i, l);
        deleter(pq, left);
      }
      else
        return;
    }
  }
  
}

void* pq_remove_first(struct pq* pq) {
  struct pq_node* head = dynarray_get(pq->heap, 0);
  struct pq_node* end = dynarray_get(pq->heap, dynarray_size(pq->heap)-1);
  dynarray_set(pq->heap, 0, end);
  dynarray_remove(pq->heap,dynarray_size(pq->heap)-1);
  // struct pq_node* new_head = dynarray_get(pq->heap, 0);
  deleter(pq, 0);
  void* head2 = head->value;
  free(head);
  return head2;
}
