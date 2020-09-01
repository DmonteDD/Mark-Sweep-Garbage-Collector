#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Object.hpp"
using namespace std;

Object::Object(){}

Object::Object(int threadId,int objId, int size, int reffields, int classId, int alloc_addr)
{
        this->threadId=threadId;
        this->objectId=objId;
        this->objectSize=size;
        this->classId=classId;
        this->reffields=reffields;
        this->objectRefSlots=new int[reffields];
        this->objectaddr=alloc_addr;
         for(int i=0;i<reffields;i++)
        {
                objectRefSlots[i]=-1;
                //cout << "\n i= " << i;
        } 
        this->k=0;
        this->pid=0;
        this->cid=0;
}
