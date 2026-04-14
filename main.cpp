#include "src/ListNode.h"
#include <iostream>

int main() {
  ListNode* node = new ListNode();
  node->data = "test";

  std::cout << "Node data: " << node->data << std::endl;

  delete node;

  return 0;
}

