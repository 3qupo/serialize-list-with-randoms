#include "Serializer.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

void serializeToBinary(ListNode *head, const std::string &filename)
 {
  if (!head) 
  {
    std::ofstream out(filename, std::ios::binary);
    int32_t n = 0;
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    std::cout << "Empty list, wrote 0 nodes" << std::endl;
    return;
  }

  std::vector<ListNode *> nodes;
  ListNode *current = head;
  while (current) 
  {
    nodes.push_back(current);
    current = current->next;
  }

  std::unordered_map<ListNode*, int32_t> node_to_index;
  for (size_t i = 0; i < nodes.size(); ++i) {
    node_to_index[nodes[i]] = i;
  }

  std::ofstream out(filename, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "Error: Cannot create " << filename << std::endl;
    return;
  }

  int32_t n = nodes.size();
  out.write(reinterpret_cast<const char *>(&n), sizeof(n));

  for (size_t i = 0; i < nodes.size(); ++i) 
  {
    ListNode *node = nodes[i];
    int32_t len = node->data.length();

    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(node->data.c_str(), len);

    int32_t rand_idx = -1;
    if (node->rand) 
    {
      auto it = node_to_index.find(node->rand);
      if (it != node_to_index.end()) {
        rand_idx = it->second;
      }
    }
    out.write(reinterpret_cast<const char *>(&rand_idx), sizeof(rand_idx));
  }

  out.close();
}
