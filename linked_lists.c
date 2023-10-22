#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define true (uint8_t)1
#define false (uint8_t)0

#define nullptr 0

typedef struct Node Node;
typedef struct List List;

struct Node {
  int m_value;
  Node *m_next;
};

struct List {
  Node *m_head;
};

Node *node_create(int t_value) {
  Node *new_node = malloc(sizeof(Node));
  new_node->m_value = t_value;
  new_node->m_next = nullptr;
  return new_node;
}

Node* node_create_after(Node* t_node_before, int t_value) {
  Node *new_node = node_create(t_value);
  t_node_before->m_next = new_node;
  return new_node;
}

void node_remove(Node *t_node_before, Node **t_node) {
  if (t_node == nullptr || *t_node == nullptr) {
    fprintf(stderr, "No valid node provided to remove\n");
    exit(1);
  }

  Node *new_node = (*t_node)->m_next;
  t_node_before->m_next = new_node;
  free(*t_node);
  *t_node = nullptr;
}

List *list_create(int t_value) {
  List *new_list = malloc(sizeof(List));
  new_list->m_head = node_create(t_value);
  return new_list;
}

void list_node_create_at_head(List **t_list, int t_value) { 
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to create a node at it's head\n");
    exit(1);
  }

  Node *new_node = node_create(t_value);
  new_node->m_next = (*t_list)->m_head;

  (*t_list)->m_head = new_node;
}

void list_node_create_at_end(List **t_list, int t_value) {
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to create a node at it's end\n");   
    exit(1);
  }

  Node *new_node = node_create(t_value);
  Node *current_node = (*t_list)->m_head;

  while (current_node->m_next != nullptr) {
    current_node = current_node->m_next;
  }
  current_node->m_next = new_node;
}

void list_node_create_at_pos(List **t_list, int t_value, size_t t_pos) {
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to create a node at it's end\n");
    exit(1);
  }
}

void list_remove_head(List **t_list) {
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to remove it's head\n");   
    exit(1);
  }

  (*t_list)->m_head = (*t_list)->m_head->m_next;
}

void list_node_remove_at_end(List** t_list) { 
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to remove from end\n");
    exit(1);
  }

  Node *current_node = (*t_list)->m_head;

  while (current_node->m_next->m_next != nullptr) {
    current_node = current_node->m_next;
  }
  node_remove(current_node, &(current_node->m_next));
}

Node *list_search_by_value(List **t_list, int t_value) {
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to search in\n");   
    exit(1);
  }

  Node *result_node = (*t_list)->m_head;
  while (result_node != nullptr) {
    if (result_node->m_value == t_value) {
      return result_node;
    }
    result_node = result_node->m_next;
  }

  printf("Provided value %d was not found in the provided list\n", t_value);   
  return nullptr;
}

size_t list_get_length(List** t_list) {
  if (t_list == nullptr || *t_list == nullptr || (*t_list)->m_head == nullptr) {
    fprintf(stderr, "No valid list provided to get it's length\n");
    exit(1);
  }

  Node *current_node = (*t_list)->m_head;
  int length = 1;

  while (current_node->m_next != nullptr) {
    current_node = current_node->m_next;
    ++length;
  }

  return length;
}

int main() {
  Node *node1 = node_create(1);
  Node *node2 = node_create_after(node1, 2);
  Node **node2_addr = &node2;
  Node *node3 = node_create_after(node2, 3);
  
  List *list = list_create(1);
  list_node_create_at_head(&list, 0);
  list_node_create_at_end(&list, 2);
  list_node_create_at_end(&list, 3);
  list_remove_head(&list);
  list_node_remove_at_end(&list);

  Node *node_found_with_val_2 = list_search_by_value(&list, 2);

  node_remove(node1, &node2);

  size_t list_length = list_get_length(&list);

  List *null_list = nullptr;
  list_node_create_at_head(&null_list, 0);

  return 0;
}