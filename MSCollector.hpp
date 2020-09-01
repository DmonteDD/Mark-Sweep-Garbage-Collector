#ifndef MS_HEADER  //begin header guard
#define MS_HEADER
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <stack>
#include "Object.hpp"
#include "Heap.hpp"
using namespace std;
class Heap;
class MSCollector
{
public:
float p,t;
std::map<int,Object*> msallocmap;
std::map<int,Object*> msrootset;
std::stack <Object*> worklist;    
void markfromRoots();
void mark(Object* root);
std::map<int,Object*> sweep(Heap* heapobj);
MSCollector(std::map<int,Object*> allocmap,std::map<int,Object*> rootmap);
};
#endif