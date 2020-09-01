#ifndef STRUCT_HEADER  //begin header guard
#define STRUCT_HEADER
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
using namespace std;

class Node
{
    public:
    int addr;
    int size;
    Node* next;
};

#endif