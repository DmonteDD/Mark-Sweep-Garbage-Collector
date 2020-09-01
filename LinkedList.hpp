#ifndef STRUCTO_HEADER  //begin header guard
#define STRUCTO_HEADER
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Node.hpp"
using namespace std;

class LinkedList  
{
    public:
    Node* head;
    LinkedList();
    int find_free(int size);
    void freeNodeLL(int addr);
    void printList();
    int countList();
};
#endif
    