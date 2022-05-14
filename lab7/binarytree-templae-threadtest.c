#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ELEMENT_MAX 100
#define THREAD_MAX 20

struct node
{
  int value;
  struct node *left_child;
  struct node *right_child;
};
typedef struct node node;

struct tree
{
  node *head;
};
typedef struct tree tree;

// creates a new tree with a given root
tree *create_tree(node *head);

// frees up memory used by the given tree
void destroy_tree(tree *t);

// adds a node with the given value into the tree
// doesn’t add it if the value is already in the tree
void insert(tree *tree, int value);

// returns 1 if a node with the given value is in the tree
// returns 0 otherwise
int lookup(tree *tree, int value);

// a sample feeder thread
void *thread_feeder(void *arg)
{
  if (arg)
  {
    // pick a random number to insert
    int rando = rand() % ELEMENT_MAX;
    insert(arg, rando);
    printf("Inserting %d\n", rando);
  }
  return NULL;
}

int main()
{
  tree *t = create_tree(NULL);

  pthread_t threads[THREAD_MAX];
  srand(time(NULL)); // initialise the random number generator
  for (int i = 0; i < THREAD_MAX; i++)
  {
    pthread_create(&threads[i], NULL, thread_feeder, (void *)t);
    pthread_join(threads[i], NULL);
  }

  int in_it = lookup(t, 4);
  printf("Is 4 in it? %s\n", in_it ? "true" : "false");

  in_it = lookup(t, 5);
  printf("Is 5 in it? %s\n", in_it ? "true" : "false");

  destroy_tree(t);
}