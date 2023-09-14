#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define nullptr 0

typedef struct Node Node;

struct Node {
  int value;
  // NOTE: Because Node struct is not implemented yet, we have declared it
  // before so a Node struct can contain a pointer to the next Node struct.
  Node *next;
};

Node *node_create(int t_value) {
  Node *node = malloc(sizeof(Node));
  node->value = t_value;
  node->next = nullptr;

  return node;
}

Node *node_next(Node *t_head, int t_value) {
  // NOTE: `node` is going to hold here a newly created temporary node
  Node *node, *node_next;
  node = node_create(t_value);

  // NOTE: Check if the head node actually is not a nullptr, if it is
  // then return the temporary created node
  if (t_head == nullptr) {
    return node;
  }

  node_next = t_head;
  while (node_next->next != nullptr) {
    node_next = node_next->next;
  }

  node_next->next = node;
  return node;
}

// Remove the next node of the node given as the given parameter
void node_remove_after(Node *t_node) {
  t_node->next = t_node->next->next;
}

int main() {
  Node *node1 = node_create(0);
  Node *node2 = node_next(node1, 1);
  Node *node3 = node_next(node2, 2);

  node_remove_after(node2);

  //assert(false);
}
