#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the size of the linked list
#define SIZE 100000

// Create the struct that will represent the linked list's objects
typedef struct snowflake_node {
  int snowflake[6];
  struct snowflake_node *next;
} snowflake_node;

// The hash function of the hash table
int code(int snowflake[]) {
  return (snowflake[0] + snowflake[1] + snowflake[2]
          + snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}

int identical_right(int snow1[], int snow2[],
                    int start) {
  int offset, snow2_index;
  for (offset = 0; offset < 6; offset++) {
    snow2_index = start + offset;
    if (snow2_index >= 6)
      snow2_index = snow2_index - 6;
        if (snow1[offset] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int identical_left(int snow1[], int snow2[], int start) {
  int offset, snow2_index;
  for (offset = 0; offset < 6; offset++) {
    snow2_index = start - offset;
    if (snow2_index < 0)
      snow2_index = snow2_index + 6;
    if (snow1[offset] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int are_identical(int snow1[], int snow2[]) {
  int start;
  for (start = 0; start < 6; start++) {
    if (identical_right(snow1, snow2, start))
      return 1;
    if (identical_left(snow1, snow2, start))
      return 1;
  }
  return 0;
}

void identify_identical(snowflake_node *snowflakes[]) {
  snowflake_node *node1, *node2;
  int i;
  for (i = 0; i < SIZE; i++) {
    node1 = snowflakes[i];
    while (node1 != NULL) {
      node2 = node1->next;
      while (node2 != NULL) {
        if (are_identical(node1->snowflake, node2->snowflake)) {
          printf("Twin snowflakes found.\n");
          return;
        }
        node2 = node2->next;
      }
      node1 = node1->next;
    }
  }
  printf("No two snowflakes are alike.\n");
}

int main(void) {
  static snowflake_node *snowflakes[SIZE] = {NULL};  // One-dimensional array of pointers to snowflake nodes.
  snowflake_node *snow;  // will point to snowflake nodes that we allocate.
  int n, i, j, snowflake_code;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    snow = malloc(sizeof(snowflake_node));
    if (snow == NULL) {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    for (j = 0; j < 6; j++)
      scanf("%d", &snow->snowflake[j]);  // read the six numbers of the snowflake
    snowflake_code = code(snow->snowflake);  // the snowflake's code
    snow->next = snowflakes[snowflake_code];  // the member next of snow will point to the first element on the linked list
    snowflakes[snowflake_code] = snow;  // we set the start of the list to point to the inserted node
  }
  identify_identical(snowflakes);
  
  // deallocate all malloc'd memory, if you want to be good
  // operating system does it anyways!
  return 0;
}
