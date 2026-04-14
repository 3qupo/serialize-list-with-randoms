#include <fstream>
#include <iostream>
#include "Deserializer.h"
#include <vector>

struct NodeInfo
{
  std::string data;
  int rand_index;
};

ListNode* deserializerFromText(const std::string& filename) 
{
  std::ifstream file(filename);
    if(!file.is_open()) 
    {
      std::cerr << "file didn't open" << filename << std::endl;
      return nullptr;
    }

  std::vector<NodeInfo> nodes_info;
  std::string line;

  while (std::getline(file, line))
  {
    if(line.empty()) continue;

    size_t pos = line.find(';');
    if(pos == std::string::npos)
    {
      std::cerr << "Invalid line: " << line << std::endl;
      continue;
    }

    NodeInfo info;
    info.data = line.substr(0, pos);
    info.rand_index = std::stoi(line.substr(pos + 1));
    nodes_info.push_back(info);

    std::cout << "Read: data='" << info.data << "', rand=" << info.rand_index << std::endl;
  }
  
  file.close();

  if(nodes_info.empty()) return nullptr;

  std::vector<ListNode*> nodes;
  for(const auto& info : nodes_info)
  {
    ListNode* node = new ListNode();
    node->data = info.data;
    nodes.push_back(node);
  }

  for(size_t i = 0; i < nodes.size(); ++i)
  {
    if(i > 0) nodes[i]->prev = nodes[i - 1];
    if(i < nodes.size() - 1) nodes[i]->next = nodes[i + 1];
  }

  for(size_t i = 0; i < nodes.size(); ++i)
  {
    int rand_idx = nodes_info[i].rand_index;
    if(rand_idx >= 0 && rand_idx < (int)nodes.size()) nodes[i]->rand = nodes[rand_idx]; 
  }

  return nodes[0];
}

