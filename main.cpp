#include <iostream>
#include "src/Deserializer.h"
#include "src/Serializer.h"

void freeList(ListNode* head) 
{
    while (head) 
    {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

int main(int argc, char* argv[]) 
{
    std::string inputFile = "inlet.in";
    std::string outputFile = "outlet.out";
    
    if (argc == 3) 
    {
        inputFile = argv[1];
        outputFile = argv[2];
    } 
    
    else if (argc != 1) 
    {
        std::cerr << "Usage: " << argv[0] << " [input_file output_file]" << std::endl;
        std::cerr << "Example: " << argv[0] << " inlet.in outlet.out" << std::endl;
        return 1;
    }
    
    try {
        ListNode* head = deserializerFromText(inputFile);
        
        if (!head) {
            std::cerr << "Failed to create list" << std::endl;
            return 1;
        }
        
        serializeToBinary(head, outputFile); 
        freeList(head);
        
        std::cout << "Success!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}