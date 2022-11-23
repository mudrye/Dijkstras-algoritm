/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Ella Mudry
 * Email: mudrye@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "pq.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0


struct map{
  int cost;
  int prev;
  int node;
};

void recurse(struct map* node, int i){
  if(node[i].node <= 0){
    printf("%d", node[i].node);
    return;
  }
  printf("%d<-", node[i].node);
  struct map* new_node = node;
  new_node->node = node[i].prev;
  recurse(new_node, new_node->node);
}

int main(int argc, char const *argv[]) {
  /*
   * Write your code here to read the file `airports.dat` and to find the
   * least-cost paths from node 0 to all other nodes in the graph.  Make sure
   * to print out the least-cost paths you find at the end.
   */
  /*for every node N:
  cost[N] = infinity
  prev[N] = undefined

Q = new priority queue
insert N_start into Q with priority 0

while Q is not empty:
  c = Q.first_priority()  // c is the total cost of the path to N
  {N, N_prev} = Q.remove_first()  // N_prev is the previous node on the path to N
  if c < cost[N]:
    cost[N] = c
    prev[N] = N_prev
    for each neighbor N_i of N:  // A neighbor is a node connected to N by an edge
      c_i = cost of edge from N to N_i
      insert {N_i, N} into Q with priority c + c_i  // N is the previous node on the path to N_i*/
  FILE * data;
  data = fopen(DATA_FILE, "r");
  int num_nodes, num_edges;
  fscanf(data, "%d %d", &num_nodes, &num_edges);
  int graph[num_nodes][num_nodes];
  for(int i = 0; i<= num_nodes; i++){
    for(int j = 0; j<= num_nodes; j++){
      graph[i][j] = 0;
    }
  }
  int i, j, coster;
  for(int k = 0; k<= num_edges; k++){
    fscanf(data, "%d %d %d", &i, &j, &coster);
    graph[i][j] = coster;
  }
  fclose(data);
  struct map mapping[num_nodes];

  for(int i = 0; i < num_nodes; i++){
    mapping[i].node = i;
    mapping[i].cost= INT_MAX;
    mapping[i].prev = -1;
  }

  struct pq* Q = pq_create();
  struct map* head = malloc(sizeof(struct map));
  head->node = START_NODE;
  head->prev = -1;
  head->cost = 0;
  pq_insert(Q, head, 0);

  while(pq_isempty(Q) == 0){
    head = pq_remove_first(Q);
    if(mapping[head->node].cost > head->cost){
      mapping[head->node].cost = head->cost;
      mapping[head->node].prev = head->prev;
      for(int h = 0; h < num_nodes; h++){
        if(graph[head->node][h] > 0){
          struct map* new = malloc(sizeof(struct map));
          new->node = h;
          new->prev = head->node;
          new->cost = head->cost + graph[head->node][h];
          pq_insert(Q, new, new->cost);
        }
      }
    }
    free(head);
  }
  printf("Node \t\t\t\tCost \t\t\t\tPath\n");
  for(int h = 0; h < num_nodes; h++){
    printf("%d \t\t\t\t%d \t\t\t\t", mapping[h].node, mapping[h].cost);
    recurse(mapping, h);
    printf("\n");
  }
  pq_free(Q);
  return 0;
}
