#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <stack>
#include "Object.hpp"
#include "MSCollector.hpp"
using namespace std;

MSCollector :: MSCollector (std::map<int,Object*> allocmap,std::map<int,Object*> rootmap)
{
    msallocmap = allocmap;
    msrootset = rootmap;
}

/*
	* Function Name: markfromRoots()
    * Parameters :  None
    * Return Type : void
    * Description : Traverses the rootset 
    */
void MSCollector :: markfromRoots ()
{
    map<int,Object*>::iterator itr; 
    for (itr = msrootset.begin(); itr != msrootset.end(); ++itr) 
    { 
        if(itr->second->markbit == 1)
        {
            //cout << "\nALREADY MARKED M";
        }
        else
        {
            worklist.push(itr->second);
            mark(itr->second);
        }           
    }
    return;
}


/*
	* Function Name: mark()
    * Parameters :  object
    * Return Type : void
    * Description : Marks the traversed object as 1. 
    */
void  MSCollector :: mark(Object* root)
{
    Object *roote;
    roote=root;
    map<int,Object*>::iterator itr;

    while(!worklist.empty())
    {
        roote=worklist.top();
        roote->markbit=1;
        worklist.pop();
        for(int i=0;i<roote->reffields;i++)
        {
            if(roote->objectRefSlots[i] != -1)
            {
                itr = msallocmap.find(roote->objectRefSlots[i]);
                if(itr == msallocmap.end()) 
                {
                    //cout << "\n Not present in map" ;
                }
       			else
        	    {
                    if(itr->second->markbit != 1)
                    {
                        worklist.push(itr->second);
                    }
                }
            }
            
        }
    }
   
}


/*
	* Function Name: sweep()
    * Parameters :  std::map<int,Object*>
    * Return Type : void
    * Description : sweeps all objects whose markbits are not 1 and returns a sweeped allocmap. 
    */
std::map<int,Object*>  MSCollector :: sweep(Heap* heapobj)
{
    Heap* msheapobj = heapobj;
   
    map<int,Object*>::iterator itr;
    map<int,int>::iterator it;
  
    for (auto itrs = msallocmap.begin(); itrs != msallocmap.end();) 
			{ 
                /* cout << "\n " << itrs->first << " bit " << itrs->second->markbit; */
					if(itrs->second->markbit == 1)
					{
                        itrs->second->markbit = -1;
                        itrs++;  
    		        }
                    else 
                    {
                        msheapobj->free(itrs->second->objectaddr,itrs->second->objectSize); 
                        //cout <<"\n DELETED " << itrs->first << " \n";
                        //delete itrs->second;
                        itrs = msallocmap.erase(itrs);
                    }     
            }
    return msallocmap;
}