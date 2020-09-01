#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Heap.hpp"

using namespace std;

	/*
	* Constructor Name: Heap()
    * Parameters : MaxHeapSize
    * Description : constructor to initialse the size of the memory block.
    */

    Heap::Heap(int heapsize)
    {
        size=heapsize;
        FreeList = new LinkedList();
    }

    /*
	* Function Name: allocate()
    * Parameters :  NodeSize
    * Return Type : Returns -1 if unable to allocate or else returns the 
    *               allocated start address to the main.
    * Description : Allocates the node of the size mentioned in parameters
    *               and allocates the remaining size to the freelist.
    */
	
    int Heap::allocate(int numBytes)
	{
        
        int NodeSize=0,address=0;
        NodeSize=numBytes;  
        //FreeList->printList();
        if(NodeSize > size  )
        {
            //FreeList->printList();
            return -1;
        }         
        if(liveNodes > 0 && FreeList->countList() == 0)  
        {
            //FreeList->printList();
            return -1;
        }
        if (FreeList->head == NULL) 
        {    
            if(size-NodeSize == 0)
            {
                address=0;
                liveNodes += 1;
            } 
            else
            {  
                Node* newnodes = new Node();
                newnodes->addr = NodeSize;
                newnodes->size = (size-NodeSize);
                newnodes->next = NULL;
                FreeList->head = newnodes;
                address=0;
                liveNodes += 1;
            }
        }
        else 
        {
            address = FreeList->find_free(NodeSize);
            int c= FreeList->countList();
            if(address == -1)
            { 
                //FreeList->printList();
                return -1;
            }
            liveNodes += 1; 
            Node* temp = FreeList->head;    
            while (temp->addr != address) 
            { 
                temp = temp->next; 
            }
            if(temp->size == NodeSize && c >= 1)
            {
                FreeList->freeNodeLL(temp->addr);
            } 
            if(temp->size > NodeSize && c >= 1)
            {
                temp->addr = (temp->addr + NodeSize);
                temp->size = (temp->size - NodeSize);
            }      
        }  
       // FreeList->printList();  
        return address;
    }

    /*
	* Function Name: free()
    * Parameters :  address,NodeSize
    * Return Type : Returns 0 once freeing is done.
    * Description : Frees up the allocated node and adds it to the free list.
    */

    int Heap :: free (int addrs,int sizef)
    {
        Node* newnode = new Node();
        int i=1;
        newnode->size = sizef;
        newnode->addr = addrs;
        int c = FreeList->countList();
        if(c == 0)
        {
            newnode->next=NULL;
            FreeList->head = newnode;
            //FreeList->printList();
            liveNodes -= 1;
            return 0;
        }
        Node* temp = FreeList->head;
        Node* prev = FreeList->head;
        liveNodes -= 1;
        while(addrs > temp->addr)
        { 	
            if(c==i)
            {
                break;
            }
            else
            {
                prev=temp;
                temp=temp->next;
            }   
            i++; 
        }        
            if(prev == temp)  // Count is one 
            {
                if (temp->addr+temp->size == addrs)  // new node to be merged with the lone node.
                {
                    temp->size += sizef;
                }
                else if(addrs > temp->addr) // new node added after lone node
                { 
                    temp->next=newnode;                 
                } 
                else if((addrs+sizef) == temp->addr )
                {
                    temp->addr=addrs;
                    temp->size += sizef;
                }
                else                   // new node added before the lone node
                {
                    newnode->next=FreeList->head;
                    FreeList->head=newnode;
                }  
            }
            else
            {
                if((prev->addr+prev->size) == addrs && c != 1) // Merging previous and new
                {   
	                prev->size += sizef;
	                if((prev->addr+prev->size) == temp->addr) //Merging previous+new+temp(next)
	                {
		                prev->size += temp->size;
		                prev->next=temp->next;
	                }
                }
                else if((addrs+sizef) == temp->addr && c != 1)
                {   
	                temp->size += sizef;
                    temp->addr = addrs;
                }
                else if(temp->addr+temp->size == addrs && c==i)
                {
                    temp->size += sizef;
                }      
                else
                {
                    if(temp->next == nullptr && temp->addr < addrs)
                    {
                        temp->next = newnode;
                    }
                    else
                    {
                        newnode->next = prev->next;
                        prev->next = newnode;
                    } 
                }   
            }         
        //FreeList->printList();
        return 0;
    }
/*
	* Function Name: stats()
    * Parameters :  None
    * Return Type : void
    * Description : Prints the current stats after failure or success
    */
    int Heap::stats()
    {
        int FreeSize=0,usedSize=0;
		float used=0,avg=0;
		std::ofstream outfile;
        Node *findcount = FreeList->head;
        while(findcount != nullptr)
        {
            FreeSize += findcount->size;
            findcount=findcount->next;
        }
        long int c=FreeList->countList();
        if(FreeList->countList() != 0)
        {
            usedSize = size - FreeSize;
        }
        else if (liveNodes > 0 and c==0)
        {
            usedSize=size;
            FreeSize=0;
            avg=0;
        }
        else
        {
            usedSize = 0;
            c=1;
            FreeSize=size;
        }
        //cout << " UsedSize= " << usedSize << " size= " << size << " FreeSize = " << FreeSize << "\n";  
        if(usedSize==0)
            used=0;   
        else
            used = (usedSize*100)/size;
        //cout << " used = " << used << endl; 
        //used = (usedSize/size)*100;
		cout << "\nheap_size = " << size ;
		cout << " live = " << liveNodes;
		cout << " used = " << used << "%" ;
		cout << " nodes = " << c;
        if (liveNodes > 0 and c==0)
        {
		    cout << " avg size = " << avg << std::endl ;
        }
        else
        {
            cout << " avg size = " << FreeSize/c << std::endl ;
        }
        //cout << "OUT OF STATS\n";
       // cout << "ud\n";
		//outfile.close();
		return used;	
    }

    /*
	* Function Name: collector
    * Parameters :  allocmap(Map of all object), rootmap(map of rootset), heap pointer
    * Return Type : std::map<int,Object*> Heap
    * Description : Calls the Mark and Sweep functions to collect dead heap objects. 
    */

std::map<int,Object*> Heap::collector(std::map<int,Object*> allocmap,std::map<int,Object*> rootmap,Heap* hobj)
{
    Heap* heap_obj = hobj;
    std::map<int,Object*> hallocmap = allocmap;
    std::map<int,Object*> hrootmap = rootmap;
    std::map<int,Object*>::iterator itr;
    MSCollector ms(hallocmap,hrootmap);
	ms.markfromRoots();
	hallocmap=ms.sweep(heap_obj);
   /*  cout << " \n Object Print After Heap Returned : \n";
    for (itr = hallocmap.begin(); itr != hallocmap.end(); ++itr) 
	{ 
        cout << "\n " << itr->first << " bit " << itr->second->markbit;            
    } */
    return hallocmap;
}

